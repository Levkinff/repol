#pragma once
#include <string>
#include <Windows.h>


struct Globals
{
    // System(Base
    bool Run = false;
    bool ShowMenu = false;

    // GameData
    HWND GameHwnd = NULL;
    RECT GameRect{};
    POINT GamePoint{};
    std::string ProcName;

    // Aim
    bool AimBot = true;
    bool DrawFovCircle = false;  
    float AimFov = 100.f;
    bool Triggerbot = false; 

    //Bones (very bad)
    int AimBone = 0; 
    bool MultiBoneSelection = false;
    bool AimBones[9] = { true, false, false, false, false, false, false, false, false }; 

    // Bone names
    static const char* BoneNames[];

    //Smoothing
    bool UseLogAccel = true;       
    float LogAccelFactor = 0.15f;      


    // Visual
    bool ESP = false;
    bool ESP_Box = false;
    bool ESP_Line = false;
    bool ESP_Distance = false;
    bool ESP_HealthBar = true;
    bool ESP_Skeleton = false;
    float ESP_MaxDistance = 1000.f;
    bool ESP_HoldKey = false; 
    int ESP_HoldKeyCode = 0;  


    // Misc
    bool GodMode = false;
    bool NoRecoil = false;
    bool NoSpread = false;
    bool RangeBypass = false;

//Crosshair
    bool Crosshair = false;
    enum CrosshairType { DOT, CROSS, CIRCLE };
    CrosshairType CrosshairStyle = DOT;
    float CrosshairSize = 5.0f;
    float CrosshairThickness = 1.0f;
    float CrosshairGap = 2.0f; 
    float CrosshairOutline = 0.0f; 
    float CrosshairRotation = 0.0f; 

    bool Txyrone = false;
     
    bool StreamProof = true;

    // Key
    int MenuKey = VK_RSHIFT;
    int AimKey0 = VK_XBUTTON1;
    int AimKey1 = VK_XBUTTON2;
};

struct Color {
    float r, g, b, a;
};


extern Globals g;
extern bool IsKeyDown(int VK);
extern const char* KeyNames[];