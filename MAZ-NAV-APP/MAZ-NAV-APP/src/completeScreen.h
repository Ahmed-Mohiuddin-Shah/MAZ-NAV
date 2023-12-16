#pragma once

void completeScreen() {

    dotLimit = 0;
    std::string dots;

    while (true)
    {

        dotLimit++;
        if (dotLimit > FPS && dots.size() < 3)
        {
            dots.push_back('.');
            dotLimit = 0;
        }
        else if (dotLimit > FPS / 2 && dots.size() == 3) {
            break;
        }

        BeginDrawing();
        ClearBackground(TERMINALBROWN);
        DrawTextEx(consolasFont, TextFormat("COMPLETE %s", dots.c_str()), Vector2{ 45, 30 }, 100, 0.5, TERMINALTEXTGOLD);
        drawBlinkingCursor(30, (float)screenHeight - 90);
        drawConsoleOverlay();
        EndDrawing();

    }

    previousLayer = layer;
    layer = OPTIONS_MENU;

}