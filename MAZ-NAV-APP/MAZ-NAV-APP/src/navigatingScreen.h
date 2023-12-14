#pragma once

void sendSolution(std::string solution) {

    solution = std::string("move move left move move");
    try
    {
        mazNavRover->Write(solution.c_str(), solution.length());
    }
    catch (BluetoothException e)
    {
    }
    

}

std::string roverResponse() {
    char c[12];
    try
    {
        mazNavRover->Read(c, 12);
    }
    catch (BluetoothException e)
    {
    }
    std::string s(c);
    return s;
}

void navigatingScreen() {
    using namespace std::chrono_literals;
    dotLimit = 0;
    std::string dots;
    std::future<void> sendFuture = std::async(std::launch::async, sendSolution, solution);
    std::future<std::string> receiveFuture = std::async(std::launch::async, roverResponse);
    while (receiveFuture.wait_for(1us) != std::future_status::ready)
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