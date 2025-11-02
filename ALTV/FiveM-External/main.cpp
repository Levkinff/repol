// main.cpp
#include "Overlay/Overlay.h"
#include "Cheat/Cheat.h"
#include "Utils/Memory/Memory.h"
#include "Cheat/SDK/offset.h"
#include "Utils/Globals/Globals.h"
#include <thread>
#include <iostream>
#include <DirectXMath.h>  // Для SimpleMath::Matrix

using namespace DirectX::SimpleMath;

Cheat* five = nullptr;
Overlay* ov = nullptr;

// === ИНИЦИАЛИЗАЦИЯ REPLAY INTERFACE И CAMERA ===
void InitializeReplayInterface() {
    if (globals::bInitialized) return;

    // ReplayInterface
    const char* pattern = "\x48\x8B\x05\x00\x00\x00\x00\x45\x33\xED\x48\x8B\xF1\x48\x8B\x48\x08\x48\x85\xC9\x74\x0A";
    const char* mask = "xxx????xxxxxxxxxxxx";
    uintptr_t addr = m.FindPattern(pattern, mask);
    if (!addr) {
        printf("[ERROR] ReplayInterface pattern not found!\n");
        return;
    }
    int32_t rel = *(int32_t*)(addr + 3);
    globals::ReplayInterface = addr + 7 + rel;
    printf("[+] ReplayInterface: 0x%llX\n", globals::ReplayInterface);

    // Camera
    const char* camPattern = "\x48\x8B\x05\x00\x00\x00\x00\x48\x8B\x98\x00\x00\x00\x00\xEB";
    const char* camMask = "xxx????xxx????x";
    uintptr_t camAddr = m.FindPattern(camPattern, camMask);
    if (camAddr) {
        int32_t camRel = *(int32_t*)(camAddr + 3);
        globals::Camera = camAddr + 7 + camRel;
        printf("[+] Camera: 0x%llX\n", globals::Camera);
    }
    else {
        printf("[ERROR] Camera pattern not found!\n");
    }

    globals::bInitialized = true;
}

// === РИСОВАНИЕ ESP ===
void DrawESP() {
    if (!globals::bInitialized || !globals::ReplayInterface || !globals::Camera) return;

    uintptr_t ped_int = m.Read<uintptr_t>(globals::ReplayInterface + offset::CObjectNav);
    if (!ped_int) return;

    uintptr_t list = m.Read<uintptr_t>(ped_int + offset::ObjectList);
    int count = m.Read<int>(ped_int + offset::NumObjects);
    if (!list || count <= 0 || count > 512) return;

    uintptr_t world = m.Read<uintptr_t>(globals::ReplayInterface);
    uintptr_t local = m.Read<uintptr_t>(world + offset::LocalPlayer);

    // === ЧТЕНИЕ VIEW MATRIX В float[16] ===
    float rawMatrix[16];
    for (int k = 0; k < 16; ++k) {
        rawMatrix[k] = m.Read<float>(globals::Camera + offset::m_bMatrix + k * sizeof(float));
    }

    // === ПРОВЕРКА НА НУЛЕВУЮ MATRIX ===
    bool isIdentity = (rawMatrix[0] == 1.0f && rawMatrix[5] == 1.0f && rawMatrix[10] == 1.0f && rawMatrix[15] == 1.0f &&
        rawMatrix[1] == 0.0f && rawMatrix[2] == 0.0f && rawMatrix[4] == 0.0f && rawMatrix[6] == 0.0f &&
        rawMatrix[8] == 0.0f && rawMatrix[9] == 0.0f && rawMatrix[12] == 0.0f && rawMatrix[13] == 0.0f);
    if (isIdentity) return;

    // === КОНВЕРТАЦИЯ float[16] → SimpleMath::Matrix ===
    Matrix viewMatrix;
    viewMatrix._11 = rawMatrix[0]; viewMatrix._12 = rawMatrix[1]; viewMatrix._13 = rawMatrix[2]; viewMatrix._14 = rawMatrix[3];
    viewMatrix._21 = rawMatrix[4]; viewMatrix._22 = rawMatrix[5]; viewMatrix._23 = rawMatrix[6]; viewMatrix._24 = rawMatrix[7];
    viewMatrix._31 = rawMatrix[8]; viewMatrix._32 = rawMatrix[9]; viewMatrix._33 = rawMatrix[10]; viewMatrix._34 = rawMatrix[11];
    viewMatrix._41 = rawMatrix[12]; viewMatrix._42 = rawMatrix[13]; viewMatrix._43 = rawMatrix[14]; viewMatrix._44 = rawMatrix[15];

    for (int i = 0; i < count; i++) {
        uintptr_t ped = m.Read<uintptr_t>(list + i * 0x10);
        if (!ped || ped == local) continue;

        Vector3 pos = m.Read<Vector3>(ped + offset::m_pLocation);
        if (pos.x == 0.0f && pos.y == 0.0f && pos.z == 0.0f) continue;

        float hp = m.Read<float>(ped + offset::m_pHealth);
        if (hp <= 0 || hp > 200) continue;

        char name[32] = "Player";
        auto info = m.Read<uintptr_t>(ped + offset::m_pInfo);
        if (info) {
            for (int j = 0; j < 31; j++) {
                name[j] = m.Read<char>(info + offset::Name + j);
                if (name[j] == 0) break;
            }
            name[31] = 0;
        }

        Vector2 screen;
        if (WorldToScreen(viewMatrix, pos, screen)) {
            auto draw = ImGui::GetBackgroundDrawList();
            draw->AddText(ImVec2(screen.x - 30, screen.y - 65), IM_COL32(255, 255, 255, 255), name);
            draw->AddRect(
                ImVec2(screen.x - 30, screen.y - 50),
                ImVec2(screen.x + 30, screen.y + 50),
                IM_COL32(0, 255, 0, 255), 0.0f, 0, 2.0f
            );
        }
    }
}

// === ОСНОВНАЯ ФУНКЦИЯ ===
#if _DEBUG
int main()
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);

    if (!m.Init()) {
        MessageBoxA(nullptr, "Failed to find GTA5.exe (ALTV must be running)", "ERROR", MB_ICONERROR);
        return 1;
    }

    const char* worldPattern = "\x48\x8B\x05\x00\x00\x00\x00\x48\x8B\x48\x08\x48\x85\xC9\x74\x52\x8B\x81";
    const char* worldMask = "xxx????xxxxxxxxxx";
    uintptr_t worldAddr = m.FindPattern(worldPattern, worldMask);
    if (worldAddr) {
        offset::GameWorld = worldAddr - m.BaseAddress;
        printf("[+] World: 0x%llX (offset: 0x%X)\n", worldAddr, offset::GameWorld);
    }
    else {
        MessageBoxA(nullptr, "Failed to find World signature!", "ERROR", MB_ICONERROR);
        return 1;
    }

    InitializeReplayInterface();

    five = new Cheat;
    ov = new Overlay;

    if (!ov->CreateOverlay()) return 2;

    g.Run = true;
    std::thread([&]() { ov->OverlayManager(); }).detach();
    std::thread([&]() { five->AimBot(); }).detach();
    std::thread([&]() { five->Misc(); }).detach();
    std::thread([&]() { five->UpdateList(); }).detach();
    std::thread([&]() { five->TriggerBot(); }).detach();

    ov->OverlayLoop();

    g.Run = false;
    ov->DestroyOverlay();
    if (m.pHandle) CloseHandle(m.pHandle);
    delete five; delete ov;
    return 0;
}

void Overlay::OverlayLoop() {
    while (g.Run) {
        MSG msg;
        while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        five->RenderInfo();
        if (g.ShowMenu) five->RenderMenu();
        if (g.ESP) {
            five->RenderESP();
            DrawESP();
        }

        ImGui::Render();
        const float clear_color_with_alpha[4] = { 0.f, 0.f, 0.f, 0.f };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        g_pSwapChain->Present(1, 0);
    }
}