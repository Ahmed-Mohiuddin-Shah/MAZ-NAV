#pragma once

void connectionIssue() {
    bool restartConnecting = false;
    while (!restartConnecting && !(layer == EXIT))
    {

        if (CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 190, 200, 50 }))
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                PlaySound(buttonPressSound);
                layer = CONNECTING_SCREEN;
                restartConnecting = true;
            }
        }

        if (CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 140, 170, 50 }))
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                PlaySound(buttonPressSound);
                layer = EXIT;
            }
        }

        BeginDrawing();
        ClearBackground(TERMINALBROWN);
        DrawTextEx(consolasFont, "CONNECTION ISSUE :(", Vector2{ 45, 30 }, 100, 0.5, TERMINALTEXTGOLD);

        DrawTextEx(consolasFont, TextFormat("Check if your Bluetooth Adapter is ON  %s", mazNavRover.name.c_str()), Vector2{45, (float)screenHeight - 390}, 50, 0.5, TERMINALTEXTGOLD);
        DrawTextEx(consolasFont, "Check if Rover is Turned ON", Vector2{ 45, (float)screenHeight - 340 }, 50, 0.5, TERMINALTEXTGOLD);
        DrawTextEx(consolasFont, "<Retry>", Vector2{ 45, (float)screenHeight - 190 }, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 190, 200, 50 }) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);
        DrawTextEx(consolasFont, "<Exit>", Vector2{ 45, (float)screenHeight - 140 }, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 140, 170, 50 }) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);

        drawBlinkingCursor(200, (float)screenHeight - 140);

        drawConsoleOverlay();
        EndDrawing();
    }

}