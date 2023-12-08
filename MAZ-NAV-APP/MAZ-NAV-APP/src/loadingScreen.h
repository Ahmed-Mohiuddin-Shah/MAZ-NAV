#pragma once
#include<chrono>
#include<thread>

inline void initStuff() {
    InitWindow(screenWidth, screenHeight, titleText);
    InitAudioDevice();
    // ToggleFullscreen(); Enable Afterwards
    SetRandomSeed((unsigned int)time(NULL));
    apertureLogo = LoadTexture("resources/ap_logo.png");
    apertureScienceLogoRectangle = Rectangle{ 0.0f, 0.0f, (float)apertureLogo.width, (float)apertureLogo.height };
    apertureScienceLogoOrigin = Vector2{ (float)apertureLogo.width / 4, (float)apertureLogo.height / 4 };
    windowIcon = LoadImageFromTexture(apertureLogo);
    SetWindowIcon(windowIcon);
    CRTOnOffSound = LoadSound("resources/CRTEffect.wav");
    consolasFont = LoadFontEx("resources/consolas.ttf", 96, 0, 0);
    target = LoadRenderTexture(screenWidth, screenHeight);
    scanlineShader = LoadShader(0, "resources/scanlines.fs");
    CRTBuzzMusic = LoadMusicStream("resources/CRTBuzz.wav");
    SetTargetFPS(FPS);
}

void initializaingStuff() {
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
    splitFlapSound = LoadSound("resources/SplitFlap.mp3");
    buttonPressSound = LoadSound("resources/ButtonPress.mp3");
    PlaySound(splitFlapSound);
    SetExitKey(KEY_F4 && KEY_LEFT_ALT);
    PlayMusicStream(CRTBuzzMusic);
    sleep_for(seconds(2));
}

inline void loadingScreen()
{   
    using namespace std::chrono_literals;
    std::future<void> f = std::async(std::launch::async, initializaingStuff);
    std::string loadingText = getRandomString(true);
    while (f.wait_for(1us) != std::future_status::ready)
    {
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
            loadingText = getRandomString(true);
        }

        // Enable if you want aperture logo
        // DrawTexturePro(apertureLogo, apertureScienceLogoRectangle, Rectangle{screenWidth / 2.0f + apertureLogoGoToCorner.x, screenHeight / 2.0f - apertureLogoGoToCorner.y, apertureScienceLogoOrigin.x * 4, apertureScienceLogoOrigin.y * 4}, Vector2{apertureScienceLogoOrigin.x * 2, apertureScienceLogoOrigin.y * 2}, apertureLogoRotaion, WHITE);
        DrawTextEx(consolasFont, TextFormat("%s", loadingText.c_str()), Vector2{ 45, (float)screenHeight - 140 }, 35, 0.5, TERMINALTEXTGOLD);
        drawConsoleOverlay();
        EndDrawing();
    }
    layer = CONNECTING_SCREEN;
}