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
#include <BTSerialPortBinding.h>
#include <BluetoothException.h>

#include "flavortext.h"
#include "variabledefinitions.h"
#include "functions.h"
#include "loadingScreen.h"
#include "connectingScreen.h"
#include "connectionIssue.h"
#include "connectedScreen.h"
#include "options.h"
#include "placeRover.h"
#include "sensorsMenu.h"
#include "predefinedMazesMenu.h"
#include "navigatingScreen.h"
#include "completeScreen.h"
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
			optionMenu();
			break;
		case PREDEFINED_MAZES:
			predefinedMazesMenu();
			break;
		case PLACE_ROVER:
			placeRoverMenu();
			break;
		case NAVIGATING_SCREEN:
			navigatingScreen();
			break;
		case COMPLETE_SCREEN:
			completeScreen();
			break;
		case SENSORS_MENU:
			break;
		case SETTINGS:
			settingsMenu();
			break;
		case EXIT:
			exitScreen();
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
	CloseWindow();

	return 0;
}