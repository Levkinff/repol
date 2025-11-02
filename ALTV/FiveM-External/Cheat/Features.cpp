// Features.cpp
#include "Cheat.h"
#include <float.h>
#include <Windows.h>

void mouse_event(DWORD dwFlags, DWORD dx, DWORD dy, DWORD dwData, ULONG_PTR dwExtraInfo)
{
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = dwFlags;
    SendInput(1, &input, sizeof(INPUT));
}

void Cheat::TriggerBot()
{
    TriggerAddress = m.BaseAddress + offset::TriggerState;
    static bool isHoldingMouse = false;
    while (g.Run)
    {
        if (g.Triggerbot)
        {
            int triggerState = m.Read<int>(TriggerAddress);
            if (triggerState == 1 || triggerState == 2)
            {
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                isHoldingMouse = true;
            }
            else if (isHoldingMouse)
            {
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                isHoldingMouse = false;
            }
        }
        else if (isHoldingMouse)
        {
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            isHoldingMouse = false;
        }
        Sleep(10);
    }
}

Vector3 Cheat::LerpWithLogarithmicAcceleration(Vector3 start, Vector3 end, float t)
{
    float smoothT = log(t + 1);
    return start + (end - start) * smoothT;
}

Vector3 Cheat::FindBestBone(CPed& ped)
{
    Vector2 Center = Vector2(g.GameRect.right / 2.f, g.GameRect.bottom / 2.f);
    Matrix ViewMatrix = m.Read<Matrix>(this->ViewPort + 0x24C);
    float MinFov = FLT_MAX;
    Vector3 bestBonePos = Vector3(0, 0, 0);
    if (g.MultiBoneSelection)
    {
        for (int i = 0; i < 9; i++)
        {
            if (g.AimBones[i])
            {
                Vector2 pScreen;
                if (WorldToScreen(ViewMatrix, ped.BoneList[i], pScreen))
                {
                    float FOV = abs((Center - pScreen).Length());
                    if (FOV < MinFov)
                    {
                        MinFov = FOV;
                        bestBonePos = ped.BoneList[i];
                    }
                }
            }
        }
    }
    else
    {
        bestBonePos = ped.BoneList[g.AimBone];
    }
    return bestBonePos;
}

CPed Cheat::FindBestTarget()
{
    CPed target{};
    CPed* pLocal = &local;
    Matrix ViewMatrix = m.Read<Matrix>(this->ViewPort + 0x24C);
    float MinFov = FLT_MAX;
    Vector2 Center = Vector2(g.GameRect.right / 2.f, g.GameRect.bottom / 2.f);
    for (auto& ped : EntityList)
    {
        CPed* pEntity = &ped;
        if (!pLocal->Update())
            break;
        else if (!pEntity->Update())
            continue;
        Vector3 bonePos = FindBestBone(ped);
        if (Vec3_Empty(bonePos))
            continue;
        Vector2 pScreen;
        if (!WorldToScreen(ViewMatrix, bonePos, pScreen))
            continue;
        float FOV = abs((Center - pScreen).Length());
        if (FOV < g.AimFov && FOV < MinFov)
        {
            target = ped;
            MinFov = FOV;
        }
    }
    return target;
}

void Cheat::AimBot()
{
    float smoothingFactor = 0.05f;
    float maxSpeed = 1.0f;
    while (g.Run)
    {
        CPed target = FindBestTarget();
        if (IsKeyDown(g.AimKey0) || IsKeyDown(g.AimKey1))
        {
            if (!Vec3_Empty(target.BoneList[HEAD]))
            {
                uintptr_t camera = m.Read<uintptr_t>(m.BaseAddress + offset::Camera);
                Vector3 ViewAngle = m.Read<Vector3>(camera + 0x3D0);
                Vector3 CameraPos = m.Read<Vector3>(camera + 0x60);
                Vector3 targetPos = FindBestBone(target);
                if (Vec3_Empty(targetPos))
                    continue;
                Vector3 TargetAngle = CalcAngle(CameraPos, targetPos);
                NormalizeAngles(TargetAngle);
                if (g.UseLogAccel)
                {
                    TargetAngle = LerpWithLogarithmicAcceleration(ViewAngle, TargetAngle, g.LogAccelFactor);
                }
                if (!Vec3_Empty(TargetAngle))
                {
                    m.Write<Vector3>(camera + 0x3D0, TargetAngle);
                }
                currentTargetPos = targetPos;
                hasValidTarget = true;
            }
        }
        Sleep(1);
    }
}

void Cheat::Misc()
{
    while (g.Run)
    {
        // GodMode
        if (g.GodMode && m.Read<bool>(local.ptr + offset::m_pGodMode) == false)
            m.Write<bool>(local.ptr + offset::m_pGodMode, true);
        else if (!g.GodMode && m.Read<bool>(local.ptr + offset::m_pGodMode) == true)
            m.Write<bool>(local.ptr + offset::m_pGodMode, false);
        if (g.NoRecoil)
            m.Write<float>(local.current_weapon + offset::m_WepRecoil, 0.f);
        if (g.NoSpread)
            m.Write<float>(local.current_weapon + offset::m_WepSpread, 0.f);
        if (g.RangeBypass)
            m.Write<float>(local.current_weapon + offset::m_WepRange, 999.f);
        Sleep(100);
    }
}

void Cheat::UpdateList()
{
    while (g.Run)
    {
        std::vector<CPed> list;
        GWorld = m.Read<uintptr_t>(m.BaseAddress + offset::GameWorld);
        local.ptr = m.Read<uintptr_t>(GWorld + 0x8);
        ViewPort = m.Read<uintptr_t>(m.BaseAddress + offset::ViewPort);
        uintptr_t ReplayInterface = m.Read<uintptr_t>(m.BaseAddress + offset::ReplayInterface);
        uintptr_t EntityListPtr = m.Read<uintptr_t>(ReplayInterface + 0x18);
        uintptr_t EntityList = m.Read<uintptr_t>(EntityListPtr + 0x100);
        for (int i = 0; i < 256; i++)
        {
            CPed ped = CPed{};
            uintptr_t player = m.Read<uintptr_t>(EntityList + (i * 0x10));

            if (player == local.ptr)
                continue;
            else if (!ped.get_player(player))
                continue;
            else if (!ped.Update())
                continue;
            list.push_back(ped);
        }
        this->EntityList = list;
        Sleep(500);
    }
}