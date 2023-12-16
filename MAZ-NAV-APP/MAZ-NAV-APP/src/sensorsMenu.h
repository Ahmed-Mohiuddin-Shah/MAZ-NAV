#pragma once

void sensorsMenu() {

    BeginDrawing();
    ClearBackground(TERMINALBROWN);
    DrawTextEx(consolasFont, "Back", Vector2{ 45, (float)screenHeight - 140 }, 50, 0.5, CheckCollisionPointRec(GetMousePosition(), Rectangle{ 45, (float)screenHeight - 140, 120, 50 }) ? TERMINALOUTLINEYELLOW : TERMINALTEXTGOLD);
    drawBlinkingCursor(160, (float)screenHeight - 140);

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