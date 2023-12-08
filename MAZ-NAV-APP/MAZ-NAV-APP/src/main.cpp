#include <iostream>
#include <raylib.h>
#include <rlgl.h>
#include <time.h>
#include <string>
#include <future>
#include <vector>
#include <memory>
#include <cstdlib>

#include <DeviceINQ.h>

#include "flavortext.h"
#include "variabledefinitions.h"
#include "functions.h"
#include "loadingScreen.h"
#include "connectingScreen.h"
#include "connectionIssue.h"
#include "connectedScreen.h"
#include "options.h"

#include "exitScreen.h"

int main(void)
{
	initStuff();
	loadingScreen();
	
	while (!shouldExit && !WindowShouldClose())
	{
		switch (layer)
		{
		case LOADING_SCREEN:
			loadingScreen();
			exitScreen();
			exitScreen();
			break;
		case CONNECTING_SCREEN:
			connectingScreen();
			break;
		case CONNECTION_ISSUE:
			connectionIssue();
			break;
		case CONNECTED_SCREEN:
			connectedScreen();
			break;
		case OPTIONS_MENU:
			mainMenu();
			break;
		case SETTINGS:
			settingsMenu();
			break;
		case EXIT:
			shouldExit = true;
			break;
		}
	}


	// TODO MUltithreaded unload
	UnloadShader(scanlineShader);
	UnloadMusicStream(CRTBuzzMusic);
	UnloadSound(splitFlapSound);
	UnloadSound(CRTOnOffSound);
	UnloadSound(buttonPressSound);
	exitScreen();
	CloseWindow();

	return 0;
}