#include "GTAVMenu.h"
#include "GTAVNatives.h"
#include "Input.h"
#include "base64.h"
//#include "globals.h"

//#define x_startup //Enables CPU Verification, need to uncomment in globals.h
#define printf


Input *inputHandler;
char *scroll_1;
#ifdef x_startup
char *cputocheck;
#endif
bool leftBumperPressed = false;
bool rightBumperPressed = false;
bool aButtonPressed = false;
bool bButtonPressed = false;
bool DupButtonPressed = false;
bool DdownButtonPressed = false;
int font = 3;
//int titlefont = 6; //Original Font = 1 (Cursive)
//int itemfont = 5;
bool text_secure = true;
#ifdef x_startup
bool cpu_verified = false;
bool cpu_realcheck = false;
#endif


// Constructor
GTAVMenu::GTAVMenu() {
	inputHandler = new Input;
	menuItems = new vector<GTAVMenuItem>;
	menuStack = new stack<GTAVMenu*>;
	menuIndexStack = new vector<int>;
	rootMenu = this;
	currentMenu = rootMenu;
}

// Destructor
GTAVMenu::~GTAVMenu() {
}

// Set the menu title
void GTAVMenu::SetMenuTitle(char *displayText) {

	/*std::string TextToDecrypt = base64_decode(displayText);
	const char * DecryptedText = TextToDecrypt.c_str();*/
	// Clear out the title memory
	memset(menuTitle, 0, 32);

	// Copy the display text in, safely
	strcpy_s(menuTitle, 32, displayText);
}

// Add a submenu
void GTAVMenu::AddSubMenu(char *displayText, GTAVMenu *subMenu) {
	GTAVMenuItem menuItem;


	// Set menu type
	menuItem.menuItemType = MENU_TYPE_STATIC_SUBMENU;

	// Copy menu item text
	strcpy_s(menuItem.itemText, 32, displayText);

	// No function callback
	menuItem.functionCallback = NULL;

	// No display callback
	menuItem.displayCallback = NULL;

	// Sub menu
	menuItem.subMenu = subMenu;

	// Function params
	menuItem.functionParameters = NULL;

	// Menu item toggling
	menuItem.itemToggleable = false;
	menuItem.itemToggled = false;

	// Add our menu item
	menuItems->push_back(menuItem);
}

// Add a static item to the menu
void GTAVMenu::AddStaticItem(char *displayText, bool itemToggleable, GTAVMenuCallback functionCallback, void *functionParameters) {



	GTAVMenuItem menuItem;

	// Set menu type
	menuItem.menuItemType = MENU_TYPE_STATIC;

	// Copy menu item text
	strcpy_s(menuItem.itemText, 32, displayText);

	// Function callback
	menuItem.functionCallback = functionCallback;

	// No display callback
	menuItem.displayCallback = NULL;

	// Sub menu
	menuItem.subMenu = NULL;

	// Function params
	menuItem.functionParameters = functionParameters;

	// Menu item toggling
	menuItem.itemToggleable = itemToggleable;
	menuItem.itemToggled = false;

	// Add our menu item
	menuItems->push_back(menuItem);
}

// Added this so we can do a list of gamertags
void GTAVMenu::AddDynamicList(GTAVMenuCallback displayCallback, GTAVMenuCallback functionCallback) {
	GTAVMenuItem menuItem;

	// Set menu type
	menuItem.menuItemType = MENU_TYPE_DYNAMIC;

	// No item text
	memset(menuItem.itemText, 0, 32);

	// Function callback
	menuItem.functionCallback = functionCallback;

	// Display callback
	menuItem.displayCallback = displayCallback;

	// No sub menu
	menuItem.subMenu = NULL;

	// Function params
	menuItem.functionParameters = NULL;

	// Menu item toggling
	menuItem.itemToggleable = false;
	menuItem.itemToggled = false;

	// Add our menu item
	menuItems->push_back(menuItem);
}

// Have a dynamic menu with subitems
void GTAVMenu::AddDynamicSubMenu(GTAVMenuCallback displayCallback, GTAVMenu *subMenu) {
	GTAVMenuItem menuItem;

	// Set menu type
	menuItem.menuItemType = MENU_TYPE_DYNAMIC_SUBMENU;

	// No item text
	memset(menuItem.itemText, 0, 32);

	// No function callback
	menuItem.functionCallback = NULL;

	// Display callback
	menuItem.displayCallback = displayCallback;

	// Sub menu
	menuItem.subMenu = subMenu;

	// Function params
	menuItem.functionParameters = NULL;

	// Menu item toggling
	menuItem.itemToggleable = false;
	menuItem.itemToggled = false;

	// Add our menu item
	menuItems->push_back(menuItem);
}

void DisableControls()
{
	hide_help_text_this_frame();
	set_cinematic_button_active( 0 );
    unk_0x4E8E29E6( 2, 176);
    unk_0x4E8E29E6( 2, 161); 
    unk_0x4E8E29E6( 2, 165);
    unk_0x4E8E29E6( 2, 163);
    unk_0x4E8E29E6( 2, 164);
    unk_0x4E8E29E6( 2, 193);
    unk_0x4E8E29E6( 2, 194);
    unk_0x4E8E29E6( 2, 195);
    unk_0x4E8E29E6( 0, 195);
    unk_0x4E8E29E6( 2, 203);
}
int alpha = 0, alpha2 = 0, alpha3 = 0;
float fade = 0, zoom = 0.40;
int playerid = 0;
int weapon = 0;
bool t = false;
int closest = -1;
float staticRecY = 0.1050f;
float inc = 0.037f;
float xscrolllen = 0.05;
float yscrolllen = 0.037;
float xscroll = 0.05;


void helper()
{
	if (!has_streamed_texture_dict_loaded("policecomputer"))
            {
                request_streamed_texture_dict("policecomputer", 0);
            }
	draw_sprite("policecomputer", "badge", 0.78f, 0.86f, 0.15f, 0.15f, 0, 255, 255, 255, 255);
}

void title_rec()
{
  //draw_rect(0.81f, 0.075f, 0.33f, 0.062f, 0, 128, 192, 255); //Original was 200.
  draw_rect(x1, 0.075f, 0.25f, 0.062f, tShaderR, tShaderG, tShaderB, titleAlpha); //Original was 200.
}
void menu_rec()
{
  //draw_rect(0.81f, 0.56f, 0.33f, 0.92f, 0, 0, 0, 200);
  draw_rect(x1, 0.52f, 0.25f, 0.83f, mShaderR, mShaderG, mShaderB, mainAlpha);
}

int getHost()
 {
  return NETWORK_GET_HOST_OF_SCRIPT("Freemode", 4294967295, 0);
 }

 char* getHostName()
 {
  return GetPlayerName(getHost());
 }

 void showHost()
{
  PrintToScreen("HOST:", 0.76f, 0.01f, 255, 255, 255, 255, 0.6050f, 0.6050f, 0, 6);
  PrintToScreen(getHostName(), 0.83f, 0.01f, 255, 255, 255, 255, 0.6050f, 0.6050f, 0, 6);
}

/*void scroll_rec()
{
//draw_rect(0.5f, 0.95f, 1.0f, 0.04f, 0, 0, 0, 255);
  draw_rect(0.5f, 0.98f, 1.0f, 0.05f, 0, 0, 0, 255);
}*/
// Our update/display function
void GTAVMenu::DisplayMenu() {

#ifdef x_startup
	if(cpu_verified && cpu_realcheck)
	{
#endif

	if (text_secure) {
	// Check our pointers
	if (!inputHandler || !currentMenu) {
		// If we hit a null pointer we will just go back to the root menu
		currentMenu = rootMenu;
		return;
	}
	//showHost();
	//helper();
	DisableControls(); // added this to disable phone and cinematic cam!
	title_rec();
	menu_rec();
	//scroll_rec();
	// Update our input
	inputHandler->UpdateInput();

	// Handle a input
	if (inputHandler->AButtonDown() && !aButtonPressed) {
		// Get our current selected menu item
		GTAVMenuItem *menuItem = &currentMenu->menuItems->operator[](selectedMenuItem);

		printf("menuItem = %s\n", menuItem->itemText);

		// Handle our a pressed event
		switch(menuItem->menuItemType) {
		case MENU_TYPE_STATIC:
			{
				printf("Attempting to call function\n");

				// Checking to see if we added a callback
				if (menuItem->functionCallback) {
					// Toggle our menu item if its toggleable
					if (menuItem->itemToggleable) {
						menuItem->itemToggled = !menuItem->itemToggled;
					}

					play_sound_frontend(0, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET");

					printf("Calling function\n");

					menuItem->functionCallback(selectedMenuItem, menuIndexStack, menuItem->itemText, menuItem->functionParameters);
				}
				break;
			}
		case MENU_TYPE_STATIC_SUBMENU:
			{
				printf("Changing menu\n");

				// Checking if submenu is null
				if (menuItem->subMenu) {
					// Checking if its null
					if (menuStack) {
						// Save our current place
						menuStack->push(currentMenu);
					}

					currentMenu = menuItem->subMenu;

					// Set our sub menu index so we can read it
					printf("Pushing index stack\n");
					menuIndexStack->push_back(selectedMenuItem);

					// change the menu title to what we selected
					strcpy_s(currentMenu->menuTitle, 32, menuItem->itemText);

					// reset our item number
					selectedMenuItem = 0;

					play_sound_frontend(0, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET");

					printf("currentMenu = %s\n", currentMenu->menuTitle);
				}

				break;
			}
		case MENU_TYPE_DYNAMIC:
			{
				break;
			}
		case MENU_TYPE_DYNAMIC_SUBMENU:
			{
				break;
			}
		default:
			{
				break;
			}
		}
		
		aButtonPressed = true;
	}
	else if (!inputHandler->AButtonDown()) {
		aButtonPressed = false;
	}

	// Handle b input
	if (inputHandler->BButtonDown() && !bButtonPressed) {
		printf("Going back a menu\n");

		// Checking if its null
		if (menuStack) {
			printf("Menu stack ok\n", menuStack);
			// Check if we are at the root menu and make sure the menu stack is not empty
			if (currentMenu != rootMenu && !menuStack->empty()) {
				// Pop it off the stack and set it to the current menu
				printf("Getting top of menu stack\n");
				currentMenu = menuStack->top();
				selectedMenuItem = 0;

				printf("Popping menu stack\n");
				menuStack->pop();

				printf("Popping index stack\n");
				menuIndexStack->pop_back();

				play_sound_frontend(0, "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET");

				printf("currentMenu = %s\n", currentMenu->menuTitle);
			}
		}

		bButtonPressed = true;
	}
	else if (!inputHandler->BButtonDown()) {
		bButtonPressed = false;
	}

	// Handle lb input
	if (inputHandler->DpadUp() && !DupButtonPressed) {
		
		// Subtract from our item
		selectedMenuItem--;

		// make sure it does not go negative
		if (selectedMenuItem < 0) {
			selectedMenuItem = currentMenu->menuItems->size() - 1;
		}
		
		play_sound_frontend(0, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET");

		printf("selectedMenuItem = %d\n", selectedMenuItem);

		DupButtonPressed = true;
	}
	else if (!inputHandler->DpadUp()) {
		DupButtonPressed = false;
	}

	// Handle rb input
	if (inputHandler->DpadDown() && !DdownButtonPressed) {

		selectedMenuItem = (selectedMenuItem + 1) % currentMenu->menuItems->size();

		play_sound_frontend(0, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET");

		printf("selectedMenuItem = %d\n", selectedMenuItem);

		DdownButtonPressed = true;
	}
	else if (!inputHandler->DpadDown()) {
		DdownButtonPressed = false;
	}

	// Display our title
	float TitlestaticItemX = 0.50f; // 0.34 og = 0.81
	float TitlestaticItemY = 0.05f; // 0.15       0.05 og = 0.045
	float staticRecY = 0.126f;
    float inc = 0.037f;
    //0.13
	set_text_font(font);
	//PrintToScreen(currentMenu->menuTitle, 0.05000000f, 0.05000000f, 0, 255, 9, 255, 0.65f, 0.65f, 0, titlefont); old menu setup
	PrintToScreen(currentMenu->menuTitle, menuTitlef, 0.0450f, tR, tG, tB, 255, 0.95f, 0.95f, 1, titlefont);// Main Title
	// Display offsets
	//float staticItemX = 0.65f; // 0.41 og = 0.65
	//float staticItemX = 0.69f; // 0.41 og = 0.65
	float staticItemY = 0.1f; // 0.2 // 0.08 0.1 og = 0.1
	//if (x_f<1.0) x_f+= 0.003; else x_f=0;

	// Display our menu
	for (int i = 0; i < currentMenu->menuItems->size(); i++) {
		GTAVMenuItem *menuItem = &currentMenu->menuItems->operator[](i);

		switch(menuItem->menuItemType) {
		case MENU_TYPE_STATIC:
		case MENU_TYPE_STATIC_SUBMENU:
			{
				char textToPrint[32];

				if (menuItem->itemToggleable) {
					sprintf_s(textToPrint, 32, "%s: %s", menuItem->itemText, menuItem->itemToggled ? "~g~ON" : "~r~OFF");
				}
				else {
					sprintf_s(textToPrint, 32, "%s", menuItem->itemText);
				}

				// Print our string
				if (i == selectedMenuItem) {
					//Highlights the selected option cyan blue.
				    PrintToScreen(textToPrint, staticItemX, staticItemY, iR, iG, iB, 255, 0.80f, 0.80f, 0, itemfont); //Highlighted Text
					draw_rect(x1, staticRecY, 0.25f, 0.037f, sR, sG, sB, scrollAlpha); // Scroll Bar Shader
				}
				else {
					//Prints it white otherwise.
					PrintToScreen(textToPrint, staticItemX, staticItemY, 255, 255, 255, 255, 0.80f, 0.80f, 0, itemfont);// Main Text
				}

				// Increment screen offset
				staticItemY += 0.037f;
				staticRecY += inc;
				break;
			}
		case MENU_TYPE_DYNAMIC:
		case MENU_TYPE_DYNAMIC_SUBMENU:
			{
				break;
			}
		default:
			{
				break;
			}
		}
	}
}
#ifdef x_startup
}
else{
	DisableControls();
}
#endif
}
