#pragma once

void placeRoverMenu() {
    while (!(layer == OPTIONS_MENU) && !(layer == NAVIGATING_SCREEN))
    {

        if (CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 140, 240, 50 }))
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                previousLayer = layer;
                PlaySound(buttonPressSound);
                layer = NAVIGATING_SCREEN;
            }
        }

        if (CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 90, 240, 50 }))
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                previousLayer = layer;
                PlaySound(buttonPressSound);
                layer = OPTIONS_MENU;
            }
        }

        BeginDrawing();
        ClearBackground(TERMINALBROWN);

        DrawTextEx(consolasFont, TextFormat("PLACE ROVER ON GREEN"), Vector2{ 45, 30 }, 50, 0.5, TERMINALTEXTGOLD);
        DrawTextEx(consolasFont, "START POINT AS SHOWN: ", Vector2{ 45, 80 }, 50, 0.5, TERMINALTEXTGOLD);
        DrawTextEx(consolasFont, "<Placed>", Vector2{ 45, (float)screenHeight - 140 }, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 140, 240, 50 }) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);
        DrawTextEx(consolasFont, "<Cancel>", Vector2{ 45, (float)screenHeight - 90 }, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 90, 240, 50 }) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);

        drawBlinkingCursor(240, (float)screenHeight - 90);

        drawConsoleOverlay();
        EndDrawing();
    }
}