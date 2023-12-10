void drawBlinkingCursor(float x, float y)
{
    elapsedTime += GetFrameTime();
    if (elapsedTime > blinkInterval)
    {
        elapsedTime = 0.0f;
        cursorVisible = !cursorVisible;
    }
    if (cursorVisible)
    {
        DrawTextEx(consolasFont, "_", Vector2{x, y}, 50, 0.5, TERMINALTEXTGOLD);
    }
}

void drawConsoleOverlay()
{
    DrawRectangleLinesEx(Rectangle{30, 20, (float)screenWidth - 60, (float)screenHeight - 40}, 5.0f, TERMINALOUTLINEYELLOW);
    DrawRectangleLinesEx(Rectangle{0, 0, (float)screenWidth, (float)screenHeight}, 20.0f, TERMINALBROWN);
    DrawRectangleRec(Rectangle{0, 0, 30, (float)screenHeight}, TERMINALBROWN);
    DrawRectangleRec(Rectangle{ (float)screenWidth - 30, 0, 30, (float)screenHeight}, TERMINALBROWN);
    DrawRectangleRec(Rectangle{ (float)screenWidth - 210, 12, 160, 160}, TERMINALBROWN);
    DrawRectangleLinesEx(Rectangle{ (float)screenWidth - 210, 12, 160, 160}, 5.0f, TERMINALOUTLINEYELLOW);
    DrawRectangleRec(Rectangle{ (float)screenWidth - 300, 12, 80, 160}, TERMINALBROWN);
    DrawRectangleLinesEx(Rectangle{ (float)screenWidth - 300, 12, 80, 160}, 5.0f, TERMINALOUTLINEYELLOW);
    if (shouldDrawFPS)
    {
        DrawRectangleRec(Rectangle{ (float)screenWidth - 580, 12, 100, 45}, TERMINALBROWN);
        DrawRectangleLinesEx(Rectangle{ (float)screenWidth - 580, 12, 100, 45}, 5.0f, TERMINALOUTLINEYELLOW);
        DrawTextEx(consolasFont, TextFormat("%d", GetFPS()), Vector2{ (float)screenWidth - 560, 25}, 25, 0.5, TERMINALTEXTGOLD);
    }
    apertureLogoRotaion += GetFrameTime() * 100; // Ignore Warning
    if (apertureLogoRotaion > 360)
    {
        apertureLogoRotaion = 0;
    }
    DrawTextEx(consolasFont, TextFormat("%d.\n\n%d.\n\n%d.\n\n0%d", GetRandomValue(100, 200), GetRandomValue(120, 170), GetRandomValue(10, 50), GetRandomValue(0, 9)), Vector2{ (float)screenWidth - 290, 25}, 25, 0.5, TERMINALTEXTGOLD);

    DrawTexturePro(apertureLogo, apertureScienceLogoRectangle, Rectangle{ (float)screenWidth - 130, 92, apertureScienceLogoOrigin.x * 2, apertureScienceLogoOrigin.y * 2}, apertureScienceLogoOrigin, apertureLogoRotaion, WHITE);

    if (shouldDrawCRTEffect)
    {
        // UpdateMusicStream(CRTBuzzMusic);
        if (crtEffectRectangleHeight > screenHeight)
        {
            crtEffectRectangleHeight = -screenHeight;
        }
        crtEffectRectangleHeight += (int)GetFrameTime() * 1000;
        DrawRectangleGradientV(0, crtEffectRectangleHeight, screenWidth, screenHeight / 2, Color{TERMINALTEXTGOLD_CRT_ALPHA.r, TERMINALTEXTGOLD_CRT_ALPHA.g, TERMINALTEXTGOLD_CRT_ALPHA.b, 0}, TERMINALTEXTGOLD_CRT_ALPHA);

        randomLinePosition = GetRandomValue(0, screenHeight);

        DrawRectangle(0, randomLinePosition, screenWidth, 5, TERMINALTEXTGOLD_CRT_ALPHA);

        BeginShaderMode(scanlineShader);
        // NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
        DrawTextureRec(target.texture, Rectangle{0, 0, (float)target.texture.width, (float)-target.texture.height}, Vector2{0, 0}, WHITE);
        EndShaderMode();
    }
}

void settingsMenu()
{
    BeginDrawing();
    ClearBackground(TERMINALBROWN);
    DrawTextEx(consolasFont, "Settings", Vector2{45, 30}, 100, 0.5, TERMINALTEXTGOLD);

    DrawTextEx(consolasFont, "Window Mode: ", Vector2{45, (float)screenHeight - 490}, 50, 0.5, TERMINALTEXTGOLD);
    DrawTextEx(consolasFont, TextFormat("             %s", IsWindowFullscreen() ? "<FULLSCREEN>" : "<WINDOWED>"), Vector2{45, (float)screenHeight - 490}, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), IsWindowFullscreen() ? Rectangle{400, (float)screenHeight - 490, 330, 50} : Rectangle{400, (float)screenHeight - 490, 350, 50}) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);
    /// @brief ///////////
    DrawTextEx(consolasFont, "CRT Effect: ", Vector2{45, (float)screenHeight - 420}, 50, 0.5, TERMINALTEXTGOLD);
    DrawTextEx(consolasFont, TextFormat("            %s", shouldDrawCRTEffect ? "<ON>" : "<OFF>"), Vector2{45, (float)screenHeight - 420}, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), shouldDrawCRTEffect ? Rectangle{375, (float)screenHeight - 420, 115, 50} : Rectangle{375, (float)screenHeight - 420, 135, 50}) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);
    /// @brief //////////////
    DrawTextEx(consolasFont, "Draw Map: ", Vector2{45, (float)screenHeight - 350}, 50, 0.5, TERMINALTEXTGOLD);
    DrawTextEx(consolasFont, TextFormat("          %s", shouldDrawMap ? "<ON>" : "<OFF>"), Vector2{45, (float)screenHeight - 350}, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), shouldDrawMap ? Rectangle{315,(float)screenHeight - 350, 115, 50} : Rectangle{315, (float)screenHeight - 350, 135, 50}) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);

    DrawTextEx(consolasFont, "Target FPS: ", Vector2{45, (float)screenHeight - 280}, 50, 0.5, TERMINALTEXTGOLD);
    DrawTextEx(consolasFont, TextFormat("            <%d>", FPS), Vector2{45, (float)screenHeight - 280}, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), FPS < 100 ? Rectangle{380, (float)screenHeight - 280, 100, 50} : Rectangle{380, (float)screenHeight - 280, 130, 50}) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);

    DrawTextEx(consolasFont, "FPS Counter:", Vector2{45, (float)screenHeight - 210}, 50, 0.5, TERMINALTEXTGOLD);
    DrawTextEx(consolasFont, TextFormat("             %s", shouldDrawFPS ? "<ON>" : "<OFF>"), Vector2{45, (float)screenHeight - 210}, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), shouldDrawFPS ? Rectangle{400, (float)screenHeight - 210, 115, 50} : Rectangle{400, (float)screenHeight - 210, 135, 50}) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);

    DrawTextEx(consolasFont, "Back", Vector2{45, (float)screenHeight - 140}, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), Rectangle{45, (float)screenHeight - 140, 120, 50}) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);
    drawBlinkingCursor(160, (float)screenHeight - 140);

    if (CheckCollisionPointRec(GetMousePosition(), IsWindowFullscreen() ? Rectangle{400, (float)screenHeight - 490, 330, 50} : Rectangle{400, (float)screenHeight - 490, 280, 50}))
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
    if (CheckCollisionPointRec(GetMousePosition(), shouldDrawCRTEffect ? Rectangle{375, (float)screenHeight - 420, 115, 50} : Rectangle{375, (float)screenHeight - 420, 135, 50}))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            PlaySound(CRTOnOffSound);
            shouldDrawCRTEffect = shouldDrawCRTEffect ? false : true;
        }
    }
    /////////////

    if (CheckCollisionPointRec(GetMousePosition(), shouldDrawMap ? Rectangle{315, (float)screenHeight - 350, 115, 50} : Rectangle{315, (float)screenHeight - 350, 135, 50}))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            PlaySound(buttonPressSound);
            shouldDrawMap = shouldDrawMap ? false : true;
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), FPS < 100 ? Rectangle{380, (float)screenHeight - 280, 100, 50} : Rectangle{380, (float)screenHeight - 280, 130, 50}))
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

    if (CheckCollisionPointRec(GetMousePosition(), shouldDrawFPS ? Rectangle{400, (float)screenHeight - 210, 115, 50} : Rectangle{400, (float)screenHeight - 210, 135, 50}))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            PlaySound(buttonPressSound);
            shouldDrawFPS = shouldDrawFPS ? false : true;
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{45, (float)screenHeight - 140, 120, 50}))
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