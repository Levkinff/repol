#include "Cheat.h"
#include "..\Overlay\Overlay.h"

std::vector<std::string> MenuTitleList = { "AimBot", "Visual", "Misc"};

void Cheat::RenderInfo()
{
    // ウォーターマーク的な？
    std::string text = "Levkin.rust | " + std::to_string((int)ImGui::GetIO().Framerate) + "FPS";
    String(ImVec2(8.f, 8.f), ImColor(1.f, 1.f, 1.f, 1.f), text.c_str());
    /*
    // クロスヘア
    if (g.Crosshair)
    {
        ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2((float)g.GameRect.right / 2.f, (float)g.GameRect.bottom / 2.f), 3, ImColor(0.f, 0.f, 0.f, 1.f));
        ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2((float)g.GameRect.right / 2.f, (float)g.GameRect.bottom / 2.f), 2, ImColor(1.f, 1.f, 1.f, 1.f));
    }
    */

    if (g.Crosshair) {
        ImVec2 center = ImVec2(g.GameRect.right / 2.f, g.GameRect.bottom / 2.f);
        ImDrawList* drawList = ImGui::GetBackgroundDrawList();
        ImColor crosshairColor = ImColor(1.f, 1.f, 1.f, 1.f); 

        switch (g.CrosshairStyle) {
        case Globals::DOT:
            drawList->AddCircleFilled(center, g.CrosshairSize, crosshairColor);
            break;

        case Globals::CROSS:
            drawList->AddLine(
                ImVec2(center.x - g.CrosshairSize, center.y),
                ImVec2(center.x + g.CrosshairSize, center.y),
                crosshairColor,
                g.CrosshairThickness
            );
            drawList->AddLine(
                ImVec2(center.x, center.y - g.CrosshairSize),
                ImVec2(center.x, center.y + g.CrosshairSize),
                crosshairColor,
                g.CrosshairThickness
            );
            break;

        case Globals::CIRCLE:
            drawList->AddCircle(
                center,
                g.CrosshairSize,
                crosshairColor,
                0, 
                g.CrosshairThickness
            );
            break;
        }
    }

    if (g.AimBot && g.DrawFovCircle)
    {
        ImVec2 center = ImVec2(g.GameRect.right / 2.f, g.GameRect.bottom / 2.f);
        ImColor fovColor = FOV_User;  // Color of the FOV Circle
        ImGui::GetBackgroundDrawList()->AddCircle(center, g.AimFov, fovColor, 100, 1.0f);
    }
}

void Cheat::RenderMenu()
{


    ImGuiStyle& style = ImGui::GetStyle();

    style.Alpha = 1.0f;
    style.DisabledAlpha = 0.5f;
    style.WindowPadding = ImVec2(8.0f, 8.0f);
    style.WindowRounding = 6.699999809265137f;
    style.WindowBorderSize = 1.0f;
    style.WindowMinSize = ImVec2(32.0f, 32.0f);
    style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_Left;
    style.ChildRounding = 10.60000038146973f;
    style.ChildBorderSize = 1.0f;
    style.PopupRounding = 16.79999923706055f;
    style.PopupBorderSize = 1.0f;
    style.FramePadding = ImVec2(4.0f, 3.0f);
    style.FrameRounding = 6.699999809265137f;
    style.FrameBorderSize = 0.0f;
    style.ItemSpacing = ImVec2(8.0f, 4.0f);
    style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
    style.CellPadding = ImVec2(4.0f, 2.0f);
    style.IndentSpacing = 21.0f;
    style.ColumnsMinSpacing = 6.0f;
    style.ScrollbarSize = 14.0f;
    style.ScrollbarRounding = 20.0f;
    style.GrabMinSize = 10.0f;
    style.GrabRounding = 5.300000190734863f;
    style.TabRounding = 5.199999809265137f;
    style.TabBorderSize = 0.0f;
    style.TabMinWidthForCloseButton = 0.0f;
    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.4980392158031464f, 0.4980392158031464f, 0.4980392158031464f, 1.0f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.03921568766236305f, 0.03921568766236305f, 0.03921568766236305f, 1.0f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.05490196123719215f, 0.05490196123719215f, 0.05490196123719215f, 1.0f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.0784313753247261f, 0.8583691120147705f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.6995707750320435f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.05490196123719215f, 0.05490196123719215f, 0.05490196123719215f, 1.0f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.06666667014360428f, 0.06666667014360428f, 0.06666667014360428f, 1.0f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.05490196123719215f, 0.05490196123719215f, 0.05490196123719215f, 0.05490196123719215f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.1843137294054031f, 0.1921568661928177f, 0.2117647081613541f, 1.0f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.03921568766236305f, 0.03921568766236305f, 0.03921568766236305f, 1.0f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.05490196123719215f, 0.05490196123719215f, 0.05490196123719215f, 1.0f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.0784313753247261f, 0.9399999976158142f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.01960784383118153f, 0.01960784383118153f, 0.01960784383118153f, 0.5299999713897705f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3098039329051971f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.407843142747879f, 0.407843142747879f, 0.407843142747879f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5098039507865906f, 0.5098039507865906f, 0.5098039507865906f, 1.0f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.6470588445663452f, 0.2313725501298904f, 0.2313725501298904f, 1.0f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.05490196123719215f, 0.05490196123719215f, 0.05490196123719215f, 1.0f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.06666667014360428f, 0.06666667014360428f, 0.06666667014360428f, 1.0f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.0784313753247261f, 1.0f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.05490196123719215f, 0.05490196123719215f, 0.05490196123719215f, 1.0f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.06666667014360428f, 0.06666667014360428f, 0.06666667014360428f, 1.0f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.0784313753247261f, 1.0f);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.0784313753247261f, 0.501960813999176f);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.0784313753247261f, 0.6695278882980347f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.0784313753247261f, 0.9570815563201904f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.1019607856869698f, 0.1137254908680916f, 0.1294117718935013f, 0.2000000029802322f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.2039215713739395f, 0.2078431397676468f, 0.2156862765550613f, 0.2000000029802322f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.3019607961177826f, 0.3019607961177826f, 0.3019607961177826f, 0.2000000029802322f);
    style.Colors[ImGuiCol_Tab] = ImVec4(0.1843137294054031f, 0.1921568661928177f, 0.2117647081613541f, 1.0f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.2352941185235977f, 0.2470588237047195f, 0.2705882489681244f, 1.0f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.2588235437870026f, 0.2745098173618317f, 0.3019607961177826f, 1.0f);
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.06666667014360428f, 0.06666667014360428f, 0.06666667014360428f, 0.9725490212440491f);
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.06666667014360428f, 0.06666667014360428f, 0.06666667014360428f, 1.0f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.6078431606292725f, 0.6078431606292725f, 0.6078431606292725f, 1.0f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.9490196108818054f, 0.3450980484485626f, 0.3450980484485626f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.9490196108818054f, 0.3450980484485626f, 0.3450980484485626f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.4274509847164154f, 0.3607843220233917f, 0.3607843220233917f, 1.0f);
    style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
    style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f);
    style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
    style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(1.0f, 0.8784313797950745f, 0.8784313797950745f, 1.0f);
    style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.2588235437870026f, 0.2705882489681244f, 0.3803921639919281f, 1.0f);
    style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.1803921610116959f, 0.2274509817361832f, 0.2784313857555389f, 1.0f);
    style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
    style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);


    static int Index = 0;
    static bool waitingForKey0 = false; 
    static bool waitingForKey1 = false; 

    ImGui::SetNextWindowBgAlpha(0.975f);
    ImGui::SetNextWindowSize(ImVec2(600.f, 450.f));
    ImGui::Begin("Levkin ", &g.ShowMenu, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    // SelectButton
    for (int i = 0; i < MenuTitleList.size(); i++)
    {
        static float width = (ImGui::GetContentRegionAvail().x / 3.f) - 6.f;
        if (ImGui::Button(MenuTitleList[i].c_str(), ImVec2(width, 35.f)))
            Index = i;

        if (i != MenuTitleList.size() - 1)
            ImGui::SameLine();
    }

    ImGui::Separator();
    ImGui::Spacing();

    //---// Left //--------------------------------------//
    ImGui::BeginChild("##LeftChild", ImVec2(ImGui::GetContentRegionAvail().x / 2.f, ImGui::GetContentRegionAvail().y), false);

    switch (Index)
    {
    case 0: // aim
        ImGui::Text("AimBot");
        ImGui::Separator();
        ImGui::Spacing();

        // Left side - AimBot options
        ImGui::Checkbox("AimBot", &g.AimBot);
        ImGui::Checkbox("Draw FOV", &g.DrawFovCircle);
        ImGui::SliderFloat("FOV Size", &g.AimFov, 30.f, 500.f);
        ImGui::ColorEdit4("fov col", &FOV_User.Value.x);




        ImGui::NewLine();


        ImGui::NewLine();
        ImGui::Spacing();


        ImGui::Text("Smoothing");

        ImGui::Separator();
        ImGui::Spacing();




        ImGui::Checkbox("Use Smoothing", &g.UseLogAccel);
        ImGui::SliderFloat("Smoothing Factor", &g.LogAccelFactor, 0.001f, 1.0f);
        ImGui::Text("Aim Bone");
        ImGui::Separator();
        ImGui::Spacing();


        ImGui::Checkbox("Multi-Bone Selection", &g.MultiBoneSelection);
        ImGui::Spacing();

        if (g.MultiBoneSelection)
        {
            ImGui::Text("Select Bones:");
            for (int i = 0; i < 9; i++)
            {
                ImGui::Checkbox(g.BoneNames[i], &g.AimBones[i]);
                if (i < 8 && (i + 1) % 3 != 0) ImGui::SameLine();
            }
        }
        else
        {
            ImGui::Combo("Aim Bone", &g.AimBone, g.BoneNames, 9);
        }
        ImGui::Spacing();

        break;
    case 1: // visual
        ImGui::Text("Visual");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox("ESP", &g.ESP);
        ImGui::Checkbox("Hold Key ESP", &g.ESP_HoldKey);


        ImGui::NewLine();
        ImGui::Spacing();

        ImGui::Text("ESP Options");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox("Box", &g.ESP_Box);
        ImGui::Checkbox("Line", &g.ESP_Line);
        ImGui::Checkbox("Skeleton", &g.ESP_Skeleton);
        ImGui::Checkbox("Distance", &g.ESP_Distance);
        ImGui::Checkbox("HealthBar", &g.ESP_HealthBar);
        break;
    
    case 2: // misc
        ImGui::Text("Player");
        ImGui::Separator();
        ImGui::Checkbox("GodMode", &g.GodMode);

        ImGui::NewLine();
        ImGui::Text("Weapon");
        ImGui::Separator();
        ImGui::Checkbox("NoRecoil", &g.NoRecoil);
        ImGui::Checkbox("NoSpread", &g.NoSpread);
        ImGui::Checkbox("RangeBypass", &g.RangeBypass);
        break;
    default:
        break;
    }

    ImGui::EndChild();
    //---------------------------------------------------//
    ImGui::SameLine();
    //---// Right //--------------------------------------//
    ImGui::BeginChild("##RightChild", ImVec2(ImGui::GetContentRegionAvail()), false);

    switch (Index)
    {
    case 0: // aim


        ImGui::Text("Triggerbot");
        ImGui::Separator();
        ImGui::Spacing();


        ImGui::Checkbox("Enable Triggerbot", &g.Triggerbot);
        ImGui::Spacing();




        
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();



        ImGui::Text("Keys: %s", KeyNames[g.AimKey0]);
        ImGui::SameLine();
        ImGui::Text("%s", KeyNames[g.AimKey1]);

        if (waitingForKey0)
        {
            ImGui::Text("Press any key for AimKey0...");
            if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape))) 
            {
                waitingForKey0 = false;
            }
            else
            {
                for (int key = 0; key < 256; key++)
                {
                    if (GetAsyncKeyState(key) & 0x8000) 
                    {
                        g.AimKey0 = key; 
                        waitingForKey0 = false; 
                        break;
                    }
                }
            }
        }
        else
        {

            if (ImGui::Button("Set AimKey 0"))
            {
                waitingForKey0 = true;
            }
        }

        ImGui::SameLine();

        if (waitingForKey1)
        {
            ImGui::Text("Press any key for AimKey1...");
            if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape))) 
            {
                waitingForKey1 = false;
            }
            else
            {
                for (int key = 0; key < 256; key++)
                {
                    if (GetAsyncKeyState(key) & 0x8000) 
                    {
                        g.AimKey1 = key;
                        waitingForKey1 = false; 
                        break;
                    }
                }
            }
        }
        else
        {

            if (ImGui::Button("Set AimKey 1"))
            {
                waitingForKey1 = true; 
            }
        }

        break;
    case 1: // visual
        {
        ImGui::Text("ESP Setting");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::SliderFloat("Distance", &g.ESP_MaxDistance, 50.f, 1000.f);
        ImGui::Spacing();





        static bool waitingForESPHoldKey = false;

        ImGui::Text("ESP Hold Key:");
        ImGui::SameLine();
        if (waitingForESPHoldKey) {
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "Press any key...");
            if (ImGui::IsKeyPressed(ImGuiKey_Escape)) {
                waitingForESPHoldKey = false;
            }
            else {
                for (int key = 0; key < 256; key++) {
                    if (GetAsyncKeyState(key) & 0x8000) {
                        g.ESP_HoldKeyCode = key;
                        waitingForESPHoldKey = false;
                        break;
                    }
                }
            }
        }
        else {
            if (ImGui::Button("Set ESP Hold Key")) {
                waitingForESPHoldKey = true;
            }
            ImGui::SameLine();
            ImGui::Text("%s", KeyNames[g.ESP_HoldKeyCode]);
        }




        ImGui::NewLine();
        ImGui::Spacing();

        ImGui::Text("ESP Colors");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::ColorEdit4("NPC", &ESP_NPC.Value.x);
        ImGui::ColorEdit4("Player", &ESP_Player.Value.x);
        ImGui::ColorEdit4("Skeleton", &ESP_Skeleton.Value.x);
        break;
    }
    case 2: // misc
        
        ImGui::Text("System");
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Checkbox("StreamProof", &g.StreamProof);
        ImGui::Checkbox("Crosshair", &g.Crosshair);
        if (g.Crosshair) {
            const char* crosshairTypes[] = { "Dot", "Cross", "Circle", "T-Cross", "+" };
            ImGui::Combo("Crosshair Type", (int*)&g.CrosshairStyle, crosshairTypes, IM_ARRAYSIZE(crosshairTypes));


            ImGui::SliderFloat("Size", &g.CrosshairSize, 1.0f, 30.0f);
            ImGui::SliderFloat("Thickness", &g.CrosshairThickness, 1.0f, 5.0f);
            ImGui::SliderFloat("Gap", &g.CrosshairGap, 0.0f, 10.0f);
            ImGui::SliderFloat("Rotation", &g.CrosshairRotation, 0.0f, 360.0f);


            ImGui::SliderFloat("Outline", &g.CrosshairOutline, 0.0f, 3.0f);
        }

        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::NewLine();

        // Exit
        if (ImGui::Button("Exit", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
            g.Run = false;
        break;
    default:
        break;
    }

    ImGui::EndChild();
    //---------------------------------------------------//

    ImGui::End();
}



void Cheat::RenderESP()
{


    if (g.ESP_HoldKey && !IsKeyDown(g.ESP_HoldKeyCode)) {
        return;
    }

    CPed* pLocal = &local;
    Matrix ViewMatrix = m.Read<Matrix>(ViewPort + 0x24C);

    if (!pLocal->Update())
        return;



    for (auto& ped : EntityList)
    {
        CPed* pEntity = &ped;

        if (!pEntity->Update())
            continue;

        float pDistance = GetDistance(pEntity->m_pVecPosition, pLocal->m_pVecPosition);

        if (pDistance >= g.ESP_MaxDistance)
            continue;

        // Box
        Vector2 pBase{}, pHead{}, pNeck{}, pLeftFoot{}, pRightFoot{};
        if (!WorldToScreen(ViewMatrix, pEntity->m_pVecPosition, pBase) || !WorldToScreen(ViewMatrix, pEntity->BoneList[HEAD], pHead) || !WorldToScreen(ViewMatrix, pEntity->BoneList[NECK], pNeck) || !WorldToScreen(ViewMatrix, pEntity->BoneList[LEFTFOOT], pLeftFoot) || !WorldToScreen(ViewMatrix, pEntity->BoneList[RIGHTFOOT], pRightFoot))
            continue;

        // ESP用にいくつかサイズを出しておく
        float HeadToNeck = pNeck.y - pHead.y;
        float pTop = pHead.y - (HeadToNeck * 2.5f);
        float pBottom = (pLeftFoot.y > pRightFoot.y ? pLeftFoot.y : pRightFoot.y) * 1.001f;
        float pHeight = pBottom - pTop;
        float pWidth = pHeight / 3.5f;
        float bScale = pWidth / 1.5f;
        ImColor color = pEntity->isPlayer() ? ESP_Player : ESP_NPC;

        // Line
        if (g.ESP_Line)
            DrawLine(ImVec2(g.GameRect.right / 2.f, g.GameRect.bottom), ImVec2(pBase.x, pBottom), color, 1.f);

        // Box
        if (g.ESP_Box)
        {
            DrawLine(ImVec2(pBase.x - pWidth, pTop), ImVec2(pBase.x + pWidth, pTop), color, 1.f);
            DrawLine(ImVec2(pBase.x - pWidth, pTop), ImVec2(pBase.x - pWidth, pBottom), color, 1.f);
            DrawLine(ImVec2(pBase.x + pWidth, pTop), ImVec2(pBase.x + pWidth, pBottom), color, 1.f);
            DrawLine(ImVec2(pBase.x - pWidth, pBottom), ImVec2(pBase.x + pWidth, pBottom), color, 1.f);
        }

        // Skeleton
        if (g.ESP_Skeleton)
        {
            // Body
            for (int j = 0; j < 5; j++)
            {
                Vector3 skList[][2] = { { pEntity->BoneList[NECK], pEntity->BoneList[HIP] }, { pEntity->BoneList[NECK], pEntity->BoneList[LEFTHAND] },
                    { pEntity->BoneList[NECK], pEntity->BoneList[RIGHTHAND] }, { pEntity->BoneList[HIP], pEntity->BoneList[LEFTFOOT] }, { pEntity->BoneList[HIP], pEntity->BoneList[RIGHTFOOT] } };

                Vector2 ScreenB1{}, ScreenB2{};
                if (Vec3_Empty(skList[j][0]) || Vec3_Empty(skList[j][1]))
                    break;
                else if (!WorldToScreen(ViewMatrix, skList[j][0], ScreenB1) || !WorldToScreen(ViewMatrix, skList[j][1], ScreenB2))
                    break;

                DrawLine(ImVec2(ScreenB1.x, ScreenB1.y), ImVec2(ScreenB2.x, ScreenB2.y), ESP_Skeleton, 1.f);
            }
        }

        // Healthbar
        if (g.ESP_HealthBar)
        {
            HealthBar((pBase.x - pWidth) - 4.f, pBottom, 2.f, -pHeight, pEntity->m_fHealth, pEntity->m_fMaxHealth);

            if (pEntity->m_fArmor > 0.f)
                ArmorBar((pBase.x + pWidth) + 3.f, pBottom, 2.f, -pHeight, pEntity->m_fArmor, 100);
        }

        // Distance
        if (g.ESP_Distance)
        {
            std::string dist = std::to_string((int)pDistance) + "m";
            String(ImVec2(pBase.x - ImGui::CalcTextSize(dist.c_str()).x / 2.f, pBottom), ImColor(1.f, 1.f, 1.f, 1.f), dist.c_str());
        }
    }
} 

