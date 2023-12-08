enum LAYERS
{
    LOADING_SCREEN,
    CONNECTING_SCREEN,
    CONNECTION_ISSUE,
    CONNECTED_SCREEN,
    OPTIONS_MENU,
    SETTINGS,
    EXIT
};

int screenWidth = 1920;
int screenHeight = 1080;

const int constScreenWidth = 1920;
const int constScreenHeight = 1080;

unsigned int FPS = 120;
unsigned int layer = LOADING_SCREEN;
unsigned int previousLayer = 0;
unsigned int currentLevel = 0;
unsigned int cursorBlinkCounter = 0;
unsigned int randomLinePosition = 0;

int crtEffectRectangleHeight = -constScreenHeight;

bool cursorVisible = true;

float elapsedTime = 0.0f;
float blinkInterval = 0.5f;

char titleText[] = "Aperture Science Maze Testing Initiative";
char titleTextASCII[] = "MAZ-NAV\n\n\n\n\n\n\nCompanion App";

float Radius = 1.0;
float apertureLogoRotaion = 0;

unsigned int dotLimit = 0;

bool shouldDrawFPS = false;
bool shouldExit = false;
bool shouldDrawMap = true;
bool shouldDrawCRTEffect = false;  // TODO
bool shouldDisplayHelp = false;

Texture2D apertureLogo;
Image windowIcon;

RenderTexture2D target;

Shader scanlineShader;

Vector2 newPosOrigin;
Vector2 apertureScienceLogoOrigin;
Vector2 apertureLogoGoToCorner = { 0, 0 };

Rectangle apertureScienceLogoRectangle;

Font consolasFont;

Color TERMINALBROWN = { 99, 59, 7, 255 };
Color TERMINALOUTLINEYELLOW = { 159, 121, 25, 255 };
Color TERMINALTEXTGOLD = { 255, 185, 9, 255 };
Color TERMINALTEXTGOLD_CRT_ALPHA = { 255, 185, 9, 15 };

Music creditsMusic, CRTBuzzMusic;

Sound splitFlapSound, buttonPressSound, CRTOnOffSound;

device mazNavRover;