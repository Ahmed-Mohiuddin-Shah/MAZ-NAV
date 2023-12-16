void drawBlinkingCursor(float x, float y)
{
    elapsedTime += GetFrameTime();
    if (elapsedTime > blinkInterval)
    {
        elapsedTime = 0.0f;
        cursorVisible = !cursorVisible;
    }
    if (cursorVisible)
    {
        DrawTextEx(consolasFont, "_", Vector2{x, y}, 50, 0.5, TERMINALTEXTGOLD);
    }
}

void drawConsoleOverlay()
{
    DrawRectangleLinesEx(Rectangle{30, 20, (float)screenWidth - 60, (float)screenHeight - 40}, 5.0f, TERMINALOUTLINEYELLOW);
    DrawRectangleLinesEx(Rectangle{0, 0, (float)screenWidth, (float)screenHeight}, 20.0f, TERMINALBROWN);
    DrawRectangleRec(Rectangle{0, 0, 30, (float)screenHeight}, TERMINALBROWN);
    DrawRectangleRec(Rectangle{ (float)screenWidth - 30, 0, 30, (float)screenHeight}, TERMINALBROWN);
    DrawRectangleRec(Rectangle{ (float)screenWidth - 210, 12, 160, 160}, TERMINALBROWN);
    DrawRectangleLinesEx(Rectangle{ (float)screenWidth - 210, 12, 160, 160}, 5.0f, TERMINALOUTLINEYELLOW);
    DrawRectangleRec(Rectangle{ (float)screenWidth - 300, 12, 80, 160}, TERMINALBROWN);
    DrawRectangleLinesEx(Rectangle{ (float)screenWidth - 300, 12, 80, 160}, 5.0f, TERMINALOUTLINEYELLOW);
    if (shouldDrawFPS)
    {
        DrawRectangleRec(Rectangle{ (float)screenWidth - 580, 12, 100, 45}, TERMINALBROWN);
        DrawRectangleLinesEx(Rectangle{ (float)screenWidth - 580, 12, 100, 45}, 5.0f, TERMINALOUTLINEYELLOW);
        DrawTextEx(consolasFont, TextFormat("%d", GetFPS()), Vector2{ (float)screenWidth - 560, 25}, 25, 0.5, TERMINALTEXTGOLD);
    }
    apertureLogoRotaion += GetFrameTime() * 100; // Ignore Warning
    if (apertureLogoRotaion > 360)
    {
        apertureLogoRotaion = 0;
    }
    DrawTextEx(consolasFont, TextFormat("%d.\n\n%d.\n\n%d.\n\n0%d", GetRandomValue(100, 200), GetRandomValue(120, 170), GetRandomValue(10, 50), GetRandomValue(0, 9)), Vector2{ (float)screenWidth - 290, 25}, 25, 0.5, TERMINALTEXTGOLD);

    DrawTexturePro(apertureLogo, apertureScienceLogoRectangle, Rectangle{ (float)screenWidth - 130, 92, apertureScienceLogoOrigin.x * 2, apertureScienceLogoOrigin.y * 2}, apertureScienceLogoOrigin, apertureLogoRotaion, WHITE);

    if (shouldDrawCRTEffect)
    {
        // UpdateMusicStream(CRTBuzzMusic);
        if (crtEffectRectangleHeight > screenHeight)
        {
            crtEffectRectangleHeight = -screenHeight;
        }
        crtEffectRectangleHeight += (int)GetFrameTime() * 1000;
        DrawRectangleGradientV(0, crtEffectRectangleHeight, screenWidth, screenHeight / 2, Color{TERMINALTEXTGOLD_CRT_ALPHA.r, TERMINALTEXTGOLD_CRT_ALPHA.g, TERMINALTEXTGOLD_CRT_ALPHA.b, 0}, TERMINALTEXTGOLD_CRT_ALPHA);

        randomLinePosition = GetRandomValue(0, screenHeight);

        DrawRectangle(0, randomLinePosition, screenWidth, 5, TERMINALTEXTGOLD_CRT_ALPHA);

        BeginShaderMode(scanlineShader);
        // NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
        DrawTextureRec(target.texture, Rectangle{0, 0, (float)target.texture.width, (float)-target.texture.height}, Vector2{0, 0}, WHITE);
        EndShaderMode();
    }
}

Texture2D loadTexture2DFromOpenCVMatrix(cv::Mat openCVMatrixImage) {

    cv::Mat tempImage;
    openCVMatrixImage.copyTo(tempImage);
    cv::cvtColor(tempImage, tempImage, cv::COLOR_BGR2RGB);

    Image image;
    image.width =tempImage.cols;
    image.height = tempImage.rows;
    image.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8;
    image.mipmaps = 1;
    image.data = (void*)(tempImage.data);

    Texture2D imageTexture = LoadTextureFromImage(image);

    return imageTexture;
}