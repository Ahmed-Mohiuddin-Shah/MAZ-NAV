#pragma once

void connectedScreen() {
    unsigned int loopCounter = 0;
    PlaySound(buttonPressSound);
    while (loopCounter < (FPS * 5))
    {
        loopCounter++;
        BeginDrawing();
        ClearBackground(TERMINALBROWN);
        DrawTextEx(consolasFont, "ROVER CONNECTED :)", Vector2{ 45, 30 }, 100, 0.5, TERMINALTEXTGOLD);
        drawConsoleOverlay();
        EndDrawing();
    }
    layer = OPTIONS_MENU;
}