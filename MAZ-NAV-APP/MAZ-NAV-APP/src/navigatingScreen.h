#pragma once

std::string roverResponse() {

    return "MOVE DONE";
}

void navigatingScreen() {
    dotLimit = 0;
    std::string dots;
    while (!(GetKeyPressed() == KEY_A))
    {

        dotLimit++;
        if (dotLimit > FPS / 2 && dots.size() < 3)
        {
            dots.push_back('.');
            dotLimit = 0;
        }
        else if (dotLimit > FPS / 2 && dots.size() == 3){
            dots.clear();
            dotLimit = 0;
        }
        BeginDrawing();
        ClearBackground(TERMINALBROWN);
        DrawTextEx(consolasFont, TextFormat("NAVIGATING%s", dots.c_str()), Vector2{45, 30}, 100, 0.5, TERMINALTEXTGOLD);
        drawBlinkingCursor(30, (float)screenHeight - 90);

        drawConsoleOverlay();
        EndDrawing();
    }
    previousLayer = layer;
    layer = COMPLETE_SCREEN;
}