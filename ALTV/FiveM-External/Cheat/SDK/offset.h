#pragma once
#include <cstdint>
namespace offset
{
    // Base (runtime resolved) — эти резолвь на рантайме, как в твоём (паттерны типа "48 8B 05 ? ? ? ? 45 ..." для World и т.д.)
    inline uintptr_t GameWorld = 0;  // World base, resolve
    inline uintptr_t ViewPort = 0;
    inline uintptr_t Camera = 0;
    inline uintptr_t ReplayInterface = 0;  // ReplayInterface base, resolve (e.g., pattern for replay)

    // Local Player
    inline uintptr_t LocalPlayer = 0x08;  // OFFSET_PLAYER

    // CPed
    inline uintptr_t m_pLocation = 0x90;  // OFFSET_ENTITY_POS
    inline uintptr_t m_pHealth = 0x280;   // OFFSET_ENTITY_HEALTH
    inline uintptr_t m_pMaxHealth = 0x2A0;  // OFFSET_ENTITY_HEALTH_MAX (обновлено, было 0x284 в старых)
    inline uintptr_t m_pGodMode = 0x189;  // OFFSET_ENTITY_GOD
    inline uintptr_t m_pArmor = 0x14E0;   // OFFSET_PLAYER_ARMOR (обновлено, было 0x150C)
    inline uintptr_t m_bMatrix = 0x60;    // Оставил твой, но в сорсах видел 0x30 для pos base, проверь
    inline uintptr_t m_pBoneList = 0x410; // Оставил, но в новых может быть 0x430 или что-то, потести

    // PlayerInfo
    inline uintptr_t m_pInfo = 0x10C8;    // OFFSET_PLAYER_INFO (обновлено +0x20 от твоего 0x10A8)
    inline uintptr_t Name = 0xA4;         // OFFSET_PLAYER_INFO_NAME (обновил из сорса)

    // Weapon
    inline uintptr_t m_pWeaponManager = 0x10D8;  // OFFSET_WEAPON_MANAGER (обновлено +0x20 от 0x10B8)
    inline uintptr_t CurrentWeapon = 0x20;       // OFFSET_WEAPON_CURRENT
    inline uintptr_t m_WepSpread = 0x74;         // OFFSET_WEAPON_SPREAD
    inline uintptr_t m_WepRecoil = 0x2F4;        // OFFSET_WEAPON_RECOIL
    inline uintptr_t m_WepRange = 0x28C;         // OFFSET_WEAPON_RANGE

    // TriggerBot
    inline uintptr_t TriggerState = 0x1A50;  // Оставил твой, не нашёл в сорсах, если не работает — подкорректируй

    // Pools (для ESP — педы/объекты из ReplayInterface)
    inline uintptr_t CObjectNav = 0x18;      // OFFSET_REPLAY_PED_INTERFACE (для педов, обновлено)
    inline uintptr_t ObjectList = 0x100;     // OFFSET_INTERFACE_LIST (список объектов/педов)
    inline uintptr_t MaxObjects = 0x110;     // OFFSET_INTERFACE_CUR_NUMS (макс/текущее кол-во, обновлено)
    inline uintptr_t NumObjects = 0x110;     // То же для nums
    inline uintptr_t LocalPed = 0x48;        // Оставил твой
}