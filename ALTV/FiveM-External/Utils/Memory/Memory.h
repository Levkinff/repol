// Memory.h
#pragma once
#include <Windows.h>
#include <string>
#include <cstdint>


class Memory
{
private:
    char TargetClass[32] = "grcWindow";
    char TargetWindow[32] = "Grand Theft Auto V";

    uintptr_t GetModuleBase(const std::string& moduleName) const;

public:
    DWORD    PID = 0;
    HANDLE   pHandle = nullptr;
    uint64_t BaseAddress = 0;

    bool Init(const char* procName = "GTA5.exe");

    template <typename T>
    constexpr T Read(const uintptr_t& address) const noexcept
    {
        T value{};
        ReadProcessMemory(pHandle, (LPCVOID)address, &value, sizeof(T), nullptr);
        return value;
    }

    template <typename T>
    constexpr void Write(const uintptr_t& address, const T& value) const noexcept
    {
        WriteProcessMemory(pHandle, (LPVOID)address, &value, sizeof(T), nullptr);
    }

    bool ReadString(uintptr_t address, char* buffer, SIZE_T maxSize) const noexcept;

    template <typename T = uintptr_t>
    constexpr T Ptr(uintptr_t offset) const noexcept { return static_cast<T>(BaseAddress + offset); }

    uintptr_t FindPattern(const char* pattern, const char* mask = nullptr) const;
};

extern Memory m;