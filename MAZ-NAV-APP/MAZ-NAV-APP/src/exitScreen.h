#pragma once

void exitScreen() {
    unsigned int loopCounter = 0;
    PlaySound(buttonPressSound);
    std::string loadingText = getRandomString(false);
    while (loopCounter < (FPS * 5))
    {
        loopCounter++;
        BeginDrawing();
        ClearBackground(TERMINALBROWN);
        DrawTextEx(consolasFont, titleTextASCII, Vector2{ 45, 30 }, 100, 0.5, TERMINALTEXTGOLD);

        apertureLogoRotaion += GetFrameTime() * 100; // To make logo go faster
        if (apertureLogoRotaion > 360)
        {
            apertureLogoRotaion = 0;
        }

        dotLimit++;
        if (dotLimit > FPS / 2)
        {
            loadingText = getRandomString(false);
        }

        // Enable if you want aperture logo
        // DrawTexturePro(apertureLogo, apertureScienceLogoRectangle, Rectangle{screenWidth / 2.0f + apertureLogoGoToCorner.x, screenHeight / 2.0f - apertureLogoGoToCorner.y, apertureScienceLogoOrigin.x * 4, apertureScienceLogoOrigin.y * 4}, Vector2{apertureScienceLogoOrigin.x * 2, apertureScienceLogoOrigin.y * 2}, apertureLogoRotaion, WHITE);
        DrawTextEx(consolasFont, TextFormat("%s", loadingText.c_str()), Vector2{ 45, (float)screenHeight - 140 }, 35, 0.5, TERMINALTEXTGOLD);
        drawConsoleOverlay();
        EndDrawing();
    }
    layer = CONNECTING_SCREEN;
}