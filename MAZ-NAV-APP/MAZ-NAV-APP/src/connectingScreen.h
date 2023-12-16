#pragma once

bool connectDevice() {
	std::unique_ptr<DeviceINQ> inq(DeviceINQ::Create());
	std::vector<device> devices = inq->Inquire();

    for (const auto d : devices)
    {
        if (d.name == "MAZ-NAV") {
            try
            {
                mazNavRover = BTSerialPortBinding::Create(d.address, 1);
                mazNavRover->Connect();
                return true;
            }
            catch (BluetoothException e)
            {
                return false;
            }
        }
    }
    return false;
}

void connectingScreen() {
    using namespace std::chrono_literals;
    std::future<bool> f = std::async(std::launch::async, connectDevice);
    dotLimit = 0;
    std::string loadingDots = "";
    while (f.wait_for(1us) != std::future_status::ready)
    {
        BeginDrawing();
        ClearBackground(TERMINALBROWN);
        apertureLogoRotaion += GetFrameTime() * 100; // To make logo go faster
        if (apertureLogoRotaion > 360)
        {
            apertureLogoRotaion = 0;
        }

        dotLimit++;
        if (dotLimit > FPS / 2)
        {
            if (loadingDots.size() > 30) {
                loadingDots.clear();
            }
            else {
                loadingDots.push_back('.');
                dotLimit = 0;
            }
        }

        // Enable if you want aperture logo
        // DrawTexturePro(apertureLogo, apertureScienceLogoRectangle, Rectangle{screenWidth / 2.0f + apertureLogoGoToCorner.x, screenHeight / 2.0f - apertureLogoGoToCorner.y, apertureScienceLogoOrigin.x * 4, apertureScienceLogoOrigin.y * 4}, Vector2{apertureScienceLogoOrigin.x * 2, apertureScienceLogoOrigin.y * 2}, apertureLogoRotaion, WHITE);
        DrawTextEx(consolasFont, TextFormat("Connecting%s", loadingDots.c_str()), Vector2{ 45, (float)screenHeight - 140 }, 35, 0.5, TERMINALTEXTGOLD);
        drawConsoleOverlay();
        EndDrawing();
    }

    f.wait();
    bool isSuccess = f.get();

    if (isSuccess)
    {
        layer = CONNECTED_SCREEN;
    }
    else { 
        layer = CONNECTION_ISSUE; 
    }
    
}