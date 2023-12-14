#pragma once

void mazeTest() {

    cv::Mat imageMatrix = cv::imread("./resources/mazes/maze01.jpg", 0);
    cv::resize(imageMatrix, imageMatrix, cv::Size(100, 100), 0, 0, 1);
    cv::Mat imageBinary;
    cv::threshold(imageMatrix, imageBinary,  127, 255, cv::THRESH_BINARY);

    Texture2D imageTexture = loadTexture2DFromOpenCVMatrix(imageBinary);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(TERMINALBROWN);
        DrawTextEx(consolasFont, "ROVER CONNECTED :)", Vector2{ 45, 30 }, 100, 0.5, TERMINALTEXTGOLD);
        DrawTexture(imageTexture, (screenWidth / 2) - imageTexture.width / 2, (screenHeight / 2) - imageTexture.height / 2, TERMINALBROWN);
        drawConsoleOverlay();
        EndDrawing();
    }
}