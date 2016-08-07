 #ifndef __GTAVMENU_H_
#define __GTAVMENU_H_



#pragma once

#include <xtl.h>
#include <vector>
#include <stack>
using namespace std;

int itemfont = 6;
int titlefont = 4;
int titlefont1 = 1;

int tShaderR = 60;
int tShaderG = 60;
int tShaderB = 60;

int tShaderR1 = 0;
int tShaderG2 = 0;
int tShaderB3 = 0;

int mShaderR = 0;
int mShaderG = 0;
int mShaderB = 0;

int mShaderR2 = 0;
int mShaderG2 = 0;
int mShaderB2 = 0;

int HostR = 68;
int HostG = 0;
int HostB = 132;
int HostA = 250;

int BShaderR = 68;
int BShaderG = 0;
int BShaderB = 132;

int tR = 255;
int tG = 0;
int tB = 0;

int iR = 255;
int iG = 255;
int iB = 255;

int sR1 = 0;
int sG1 = 0;
int sB1 = 0;

int sR = 0;
int sG = 0;
int sB = 0;

int TitleTextR = 255;
int TitleTextG = 255;
int TitleTextB = 255;
int TitleTextA = 255;
int SpriteAlpha = 250;

int SpriteR = 68;
int SpriteG = 0;
int SpriteB = 132;
int SpriteA = 250;

int MenuTitleTextR = 255;
int MenuTitleTextG= 255;
int MenuTitleTextB= 255;
int	MenuTitleTextA =233;

int BorderR = 68;
int BorderG = 0;
int BorderB = 132;

char* marqueeText = "Release";
int BAlpha = 255;
int mainAlpha = 100;
int mainAlpha2 = 255;
int titleAlpha = 161;
int titleAlpha2 = 210;
int scrollAlpha = 155;
int scrollAlpha1 = 155;
int BorderA = 120;

float x1 = 0.81f;
float staticItemX = 0.7000f;
float staticItemY = 0.2f;
float menuTitlef = 0.8650f;

float marqueeY = 0.955f;
float marqueeShaderY = 0.98f;



class GTAVMenu;

// Our callback function, when called by the menu it will give the selected index and text for you to use if you need it
typedef int (__cdecl *GTAVMenuCallback)(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters);

typedef enum _GTAVMenuType {
MENU_TYPE_STATIC,
MENU_TYPE_STATIC_SUBMENU,
MENU_TYPE_DYNAMIC,
MENU_TYPE_DYNAMIC_SUBMENU
} GTAVMenuType;

typedef struct _GTAVMenuItem {
GTAVMenuType menuItemType;
char itemText[32];
GTAVMenuCallback functionCallback;
GTAVMenuCallback displayCallback;
GTAVMenu *subMenu;
void *functionParameters;
bool itemToggleable;
bool Scrollable;
bool Scrolled;
bool itemToggled;
int *var;
} GTAVMenuItem;

class GTAVMenu {

public:
char menuTitle[32];
vector<GTAVMenuItem> *menuItems;
GTAVMenu *rootMenu;
GTAVMenu *currentMenu;
stack<GTAVMenu*> *menuStack;
vector<int> *menuIndexStack;
int selectedMenuItem;

GTAVMenu();
~GTAVMenu();

// Set the menu title
void SetMenuTitle(char *displayText);

// Add a submenu, returns the index
void AddSubMenu(char *displayText, GTAVMenu *subMenu);

// Add a static item to the menu
void AddStaticItem(char *displayText, bool itemToggleable, GTAVMenuCallback functionCallback, void *functionParameters);


void addIntOption(char *displayText,bool Scrollable, int *var, int min, int max, GTAVMenuCallback functionCallback, void *functionParameters);

// Added this so we can do a list of gamertags
void AddDynamicList(GTAVMenuCallback displayCallback, GTAVMenuCallback functionCallback);

// Have a dynamic menu with subitems
void AddDynamicSubMenu(GTAVMenuCallback displayCallback, GTAVMenu *subMenu);

// Our update/display function
void DisplayMenu();
};

#endif
