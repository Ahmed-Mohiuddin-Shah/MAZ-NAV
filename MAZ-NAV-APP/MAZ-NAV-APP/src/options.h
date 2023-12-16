#pragma once

void optionMenu()
{
    BeginDrawing();
    ClearBackground(TERMINALBROWN);
    DrawTextEx(consolasFont, "Options", Vector2{ 45, 30 }, 100, 0.5, TERMINALTEXTGOLD);

    DrawTextEx(consolasFont, "xx Scan Mazes xx", Vector2{ 45, (float)screenHeight - 340 }, 50, 0.5, TERMINALTEXTGOLD);
    DrawTextEx(consolasFont, "Predefined Mazes", Vector2{ 45, (float)screenHeight - 290 }, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 290, 440, 50 }) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);
    DrawTextEx(consolasFont, "xx Auto Mode xx", Vector2{45, (float)screenHeight - 240}, 50, 0.5, TERMINALTEXTGOLD);
    DrawTextEx(consolasFont, "Sensors", Vector2{ 45, (float)screenHeight - 190 }, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 190, 190, 50 }) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);
    DrawTextEx(consolasFont, "Settings", Vector2{ 45, (float)screenHeight - 140 }, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 140, 215, 50 }) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);
    DrawTextEx(consolasFont, "Exit", Vector2{ 45, (float)screenHeight - 90 }, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 90, 120, 50 }) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);
    drawBlinkingCursor(160, (float)screenHeight - 90);

    // TODO Scan Mazes

    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 290, 210, 50 })) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            previousLayer = layer;
            PlaySound(buttonPressSound);
            layer = PLACE_ROVER;
        }
    }

    // TODO AutoMODE

    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 190, 200, 50 })) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            previousLayer = layer;
            PlaySound(buttonPressSound);
            layer = SENSORS_MENU;
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 140, 210, 50 }))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            previousLayer = layer;
            PlaySound(buttonPressSound);
            layer = SETTINGS;
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 90, 120, 50 }))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            PlaySound(buttonPressSound);
            layer = EXIT;
        }
    }

    drawConsoleOverlay();
    EndDrawing();
}