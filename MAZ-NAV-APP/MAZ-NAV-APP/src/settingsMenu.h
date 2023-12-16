#pragma once

void settingsMenu()
{
    BeginDrawing();
    ClearBackground(TERMINALBROWN);
    DrawTextEx(consolasFont, "Settings", Vector2{ 45, 30 }, 100, 0.5, TERMINALTEXTGOLD);

    DrawTextEx(consolasFont, "Window Mode: ", Vector2{ 45, (float)screenHeight - 490 }, 50, 0.5, TERMINALTEXTGOLD);
    DrawTextEx(consolasFont, TextFormat("             %s", IsWindowFullscreen() ? "<FULLSCREEN>" : "<WINDOWED>"), Vector2{ 45, (float)screenHeight - 490 }, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), IsWindowFullscreen() ? Rectangle{ 400, (float)screenHeight - 490, 330, 50 } : Rectangle{ 400, (float)screenHeight - 490, 350, 50 }) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);
    /// @brief ///////////
    DrawTextEx(consolasFont, "CRT Effect: ", Vector2{ 45, (float)screenHeight - 420 }, 50, 0.5, TERMINALTEXTGOLD);
    DrawTextEx(consolasFont, TextFormat("            %s", shouldDrawCRTEffect ? "<ON>" : "<OFF>"), Vector2{ 45, (float)screenHeight - 420 }, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), shouldDrawCRTEffect ? Rectangle{ 375, (float)screenHeight - 420, 115, 50 } : Rectangle{ 375, (float)screenHeight - 420, 135, 50 }) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);
    /// @brief //////////////
    DrawTextEx(consolasFont, "Draw Map: ", Vector2{ 45, (float)screenHeight - 350 }, 50, 0.5, TERMINALTEXTGOLD);
    DrawTextEx(consolasFont, TextFormat("          %s", shouldDrawMap ? "<ON>" : "<OFF>"), Vector2{ 45, (float)screenHeight - 350 }, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), shouldDrawMap ? Rectangle{ 315,(float)screenHeight - 350, 115, 50 } : Rectangle{ 315, (float)screenHeight - 350, 135, 50 }) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);

    DrawTextEx(consolasFont, "Target FPS: ", Vector2{ 45, (float)screenHeight - 280 }, 50, 0.5, TERMINALTEXTGOLD);
    DrawTextEx(consolasFont, TextFormat("            <%d>", FPS), Vector2{ 45, (float)screenHeight - 280 }, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), FPS < 100 ? Rectangle{ 380, (float)screenHeight - 280, 100, 50 } : Rectangle{ 380, (float)screenHeight - 280, 130, 50 }) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);

    DrawTextEx(consolasFont, "FPS Counter:", Vector2{ 45, (float)screenHeight - 210 }, 50, 0.5, TERMINALTEXTGOLD);
    DrawTextEx(consolasFont, TextFormat("             %s", shouldDrawFPS ? "<ON>" : "<OFF>"), Vector2{ 45, (float)screenHeight - 210 }, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), shouldDrawFPS ? Rectangle{ 400, (float)screenHeight - 210, 115, 50 } : Rectangle{ 400, (float)screenHeight - 210, 135, 50 }) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);

    DrawTextEx(consolasFont, "Back", Vector2{ 45, (float)screenHeight - 140 }, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 140, 120, 50 }) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);
    drawBlinkingCursor(160, (float)screenHeight - 140);

    if (CheckCollisionPointRec(GetMousePosition(), IsWindowFullscreen() ? Rectangle{ 400, (float)screenHeight - 490, 330, 50 } : Rectangle{ 400, (float)screenHeight - 490, 280, 50 }))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            PlaySound(buttonPressSound);
            ToggleFullscreen();
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight(); // Enable Afterwards
            // SetWindowSize(screenWidth, screenHeight);
        }
    }
    ////////////////////////////
    if (CheckCollisionPointRec(GetMousePosition(), shouldDrawCRTEffect ? Rectangle{ 375, (float)screenHeight - 420, 115, 50 } : Rectangle{ 375, (float)screenHeight - 420, 135, 50 }))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            PlaySound(CRTOnOffSound);
            shouldDrawCRTEffect = shouldDrawCRTEffect ? false : true;
        }
    }
    /////////////

    if (CheckCollisionPointRec(GetMousePosition(), shouldDrawMap ? Rectangle{ 315, (float)screenHeight - 350, 115, 50 } : Rectangle{ 315, (float)screenHeight - 350, 135, 50 }))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            PlaySound(buttonPressSound);
            shouldDrawMap = shouldDrawMap ? false : true;
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), FPS < 100 ? Rectangle{ 380, (float)screenHeight - 280, 100, 50 } : Rectangle{ 380, (float)screenHeight - 280, 130, 50 }))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            PlaySound(buttonPressSound);

            FPS = FPS + 30;
            if (FPS > 240)
                FPS = 60;

            SetTargetFPS(FPS);
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), shouldDrawFPS ? Rectangle{ 400, (float)screenHeight - 210, 115, 50 } : Rectangle{ 400, (float)screenHeight - 210, 135, 50 }))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            PlaySound(buttonPressSound);
            shouldDrawFPS = shouldDrawFPS ? false : true;
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 140, 120, 50 }))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            PlaySound(buttonPressSound);
            layer = previousLayer;
        }
    }
    drawConsoleOverlay();
    EndDrawing();
}