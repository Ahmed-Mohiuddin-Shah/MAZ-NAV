#pragma once

void mainMenu()
{
    BeginDrawing();
    ClearBackground(TERMINALBROWN);
    DrawTextEx(consolasFont, "Options", Vector2{ 45, 30 }, 100, 0.5, TERMINALTEXTGOLD);

    DrawTextEx(consolasFont, TextFormat("%s", currentLevel == 0 ? "Play" : "Continue"), Vector2{ 45, (float)screenHeight - 350 }, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), currentLevel == 0 ? Rectangle{ 45, (float)screenHeight - 350, 120, 50 } : Rectangle{ 45, (float)screenHeight - 350, 210, 50 }) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);
    DrawTextEx(consolasFont, "Credits", Vector2{ 45, (float)screenHeight - 280 }, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 280, 200, 50 }) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);
    DrawTextEx(consolasFont, "Settings", Vector2{ 45, (float)screenHeight - 210 }, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 210, 215, 50 }) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);
    DrawTextEx(consolasFont, "Exit", Vector2{ 45, (float)screenHeight - 140 }, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 140, 120, 50 }) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);
    drawBlinkingCursor(160, (float)screenHeight - 140);

    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 215, 210, 50 }))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            previousLayer = layer;
            PlaySound(buttonPressSound);
            layer = SETTINGS;
        }
    }
    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 140, 120, 50 }))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            PlaySound(buttonPressSound);
            shouldExit = true;
        }
    }

    drawConsoleOverlay();
    EndDrawing();
}