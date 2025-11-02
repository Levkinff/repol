// Memory.cpp
#include "Memory.h"
#include <psapi.h>
#include <TlHelp32.h>          // <-- THIS WAS MISSING
#include "../Globals/Globals.h"

Memory m;   // global instance

// ---------------------------------------------------------------------
// Init – finds GTA5.exe via window class "grcWindow"
// ---------------------------------------------------------------------
bool Memory::Init(const char* procName)
{
    // 1. Find window
    g.GameHwnd = FindWindowA(TargetClass, nullptr);
    if (!g.GameHwnd)
    {
        printf("[+] Waiting for ALTV (GTA5.exe)...\n");
        while (!g.GameHwnd)
        {
            g.GameHwnd = FindWindowA(TargetClass, nullptr);
            Sleep(500);
        }
    }

    // 2. Get PID
    GetWindowThreadProcessId(g.GameHwnd, &PID);
    if (!PID)
    {
        printf("[!] Failed to get PID\n");
        return false;
    }

    // 3. Open process
    pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
    if (!pHandle)
    {
        printf("[!] OpenProcess failed (Run as Admin!)\n");
        return false;
    }

    // 4. Get module name
    char moduleName[128] = { 0 };
    if (!GetModuleBaseNameA(pHandle, nullptr, moduleName, sizeof(moduleName)))
    {
        printf("[!] GetModuleBaseNameA failed\n");
        CloseHandle(pHandle); pHandle = nullptr;
        return false;
    }

    g.ProcName = moduleName;
    BaseAddress = GetModuleBase(moduleName);
    if (!BaseAddress)
    {
        printf("[!] GetModuleBase failed\n");
        CloseHandle(pHandle); pHandle = nullptr;
        return false;
    }

    printf("[+] GTA5.exe: 0x%llX | PID: %d\n", BaseAddress, PID);
    return true;
}

// ---------------------------------------------------------------------
// Get remote module base
// ---------------------------------------------------------------------
uintptr_t Memory::GetModuleBase(const std::string& moduleName) const
{
    MODULEENTRY32 entry{};
    entry.dwSize = sizeof(MODULEENTRY32);

    // <-- Fixed: parentheses + correct flag
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, PID);
    if (snap == INVALID_HANDLE_VALUE)
        return 0;

    uintptr_t result = 0;
    if (Module32First(snap, &entry))
    {
        do
        {
            if (!_stricmp(entry.szModule, moduleName.c_str()))
            {
                result = reinterpret_cast<uintptr_t>(entry.modBaseAddr);
                break;
            }
        } while (Module32Next(snap, &entry));
    }

    CloseHandle(snap);
    return result;
}

// ---------------------------------------------------------------------
// External pattern scanner (scans remote memory)
// ---------------------------------------------------------------------
uintptr_t Memory::FindPattern(const char* pattern, const char* mask) const
{
    if (!mask) mask = pattern;
    size_t patLen = strlen(mask);
    if (patLen == 0) return 0;

    const SIZE_T chunk = 0x1000000; // 16 MB chunks
    BYTE* buffer = new BYTE[chunk];
    SIZE_T bytesRead;
    uintptr_t address = BaseAddress;

    while (ReadProcessMemory(pHandle, (LPCVOID)address, buffer, chunk, &bytesRead))
    {
        for (SIZE_T i = 0; i < bytesRead - patLen; ++i)
        {
            bool found = true;
            for (SIZE_T j = 0; j < patLen; ++j)
            {
                if (mask[j] != '?' && buffer[i + j] != (BYTE)pattern[j])
                {
                    found = false;
                    break;
                }
            }
            if (found)
            {
                delete[] buffer;
                return address + i;
            }
        }
        if (bytesRead < chunk) break;
        address += chunk;
    }

    delete[] buffer;
    return 0;
}