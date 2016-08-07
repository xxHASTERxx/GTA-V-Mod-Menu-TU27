]#include <xtl.h>
#include <xkelib.h>
#include <xbdm.h>

#include "Tools.h"
#include "GTAVMenu.h"

extern "C" const TCHAR szModuleName[] = TEXT("GTAVMenu.dll");

DWORD GetTrayStatus() {
	unsigned char msg[0x10];
	unsigned char resp[0x10];
	memset(msg, 0x0, 0x10);
	msg[0] = 0xa;
	HalSendSMCMessage(msg, resp);

	return resp[1];
}

VOID PatchInJumpDev(DWORD addr, DWORD dest, BOOL linked) {
	DWORD Data[4];
	// Devkits dont like to be violated in thier code sections directly,
	// this is a workaround.
	PatchInJump(Data, dest, linked);

	DWORD cbRet = 0;
	HRESULT hr = DmSetMemory((LPVOID)addr, 16, Data, &cbRet);

	if (hr != XBDM_NOERR || cbRet != 16) {
		printf("DmSetMemory failed. HRESULT = %08X cbRet = %d\n", hr, cbRet);
	}
}

// keep this for when the time comes it will dump all our hashes and the corresponding hashes
// 8348CEA8
VOID GtaPtrHookThing(unsigned int r3, unsigned int r4) {
	int (__cdecl *func)(unsigned int, unsigned int, unsigned int) = (int (__cdecl *)(unsigned int, unsigned int, unsigned int))0x8348C528;
	
	printf("r3 = %08X r4 = %08X\n", r3, r4);

	unsigned int r11 = r3;
	unsigned int r5 = r4;

	if (r3 < 2) {
		r11 += 2;
	}

	r4 = r11;
	
	func(0x83CF1BE8, r4, r5);
}

// stuff for when a new xex gets loaded
VOID LpThreadNotificationRoutine(PEX_THREAD_REGISTRATION pxThreadReg, PKTHREAD pThread, BOOL Creating) {
        if(Creating && ( pThread->CreateOptions & 0x100 ))
        {
			printf("Xbox Kernel Version %d.%d.%d\n", XboxKrnlVersion->Major, XboxKrnlVersion->Minor, XboxKrnlVersion->Build);

			DWORD dwGameTitleId = XamGetCurrentTitleId();

            wprintf(L"Loaded game executable. Path = %s Title ID = %d\n", (*XexExecutableModuleHandle)->FullDllName.Buffer, dwGameTitleId);

			if (dwGameTitleId == 0x545408A7)
			{
				printf("Doing GTAV patches\n");

				// TU11
				*(DWORD*)0x8298DFA0 = 0x60000000;
			}

			if (dwGameTitleId == 0x4B4E083C) {
				//printf("MGS Hooks\n");

				//printf("CreateFileHook\n");
				//PatchInJumpDev(0x82F445F0, (DWORD)CreateFileHook, FALSE);

				//printf("Debug Print Hook\n");
				//PatchInJumpDev(0x88322E234, (DWORD)DbgPrintHook, FALSE);

				//printf("Debug MSG Hook\n");
				//*(DWORD*)(0x82DCB0E0) = 0x48463154;
			}
		}
}

// thread notification routine
EX_THREAD_REGISTRATION xThreadReg = { 
        LpThreadNotificationRoutine, 
        0, 
        0, 
        0 
};

// idk how many arguments can be passed, sureley we wont need 100 arguments....
DWORD VMPassed[100];
DWORD VMReturned[1];
DWORD *VMArgs[3] = {
	VMReturned, // our return value
	0,
	VMPassed
};

char *GetPlayerName(int index) {
	VMArgs[2][0] = index;

	int (__cdecl *get_player_name)(void *) = (int (__cdecl *)(void *))0x82DC31C8;

	get_player_name(VMArgs);

	return (char*)(*VMArgs[0]);
}

int NetworkIsPlayerActive(int index) {
}

void SetPlayerInvincible(int index, bool active) {
	VMArgs[2][0] = index;
	VMArgs[2][1] = active;

	int (__cdecl *set_player_invincible)(void *) = (int (__cdecl *)(void *))0x82DC4920;
	set_player_invincible(VMArgs);
}

int PlayerId() {
	int (__cdecl *player_id)(void *) = (int (__cdecl *)(void *))0x82DC4358;

	player_id(VMArgs);

	return (int)(*VMArgs[0]);
}

unsigned int GetPlayerPed(int index) {
	VMArgs[2][0] = index;

	int (__cdecl *set_player_ped)(void *) = (int (__cdecl *)(void *))0x82DC2F98;
	set_player_ped(VMArgs);
}

void GetEntityCoords(unsigned int entity, float *x, float *y, float *z) {
	//DWORD *argv[3];
	//argv[0] = (DWORD*)malloc(4); // return value ptr
	//argv[1] = 0; // ?
	//argv[2] = (DWORD*)malloc(4); // 1 argument

	//argv[2][0] = index;

	//int (__cdecl *get_entity_coords)(void *) = (int (__cdecl *)(void *))0x82D7C220;
	//get_entity_coords(argv);

	//free(argv[0]);
	//free(argv[1]);
}

void SetTextFont(int font) {
	VMArgs[2][0] = font;

	int (__cdecl *set_text_font)(void *) = (int (__cdecl *)(void *))0x82D65438;
	set_text_font(VMArgs);
}

void SetTextScale(float x, float y) {
	VMArgs[2][0] = *(DWORD*)(&x);
	VMArgs[2][1] = *(DWORD*)(&y);

	int (__cdecl *set_text_scale)(void *) = (int (__cdecl *)(void *))0x82D65368;
	set_text_scale(VMArgs);
}

void SetTextColor(int a, int r, int g, int b) {
	VMArgs[2][0] = a;
	VMArgs[2][1] = r;
	VMArgs[2][2] = g;
	VMArgs[2][3] = b;

	int (__cdecl *set_text_color)(void *) = (int (__cdecl *)(void *))0x82D826F8;
	set_text_color(VMArgs);
}

void SetTextWrap(float x, float y) {
	VMArgs[2][0] = *(DWORD*)(&x);
	VMArgs[2][1] = *(DWORD*)(&y);

	int (__cdecl *set_text_wrap)(void *) = (int (__cdecl *)(void *))0x82D65400;
	set_text_wrap(VMArgs);
}

void SetTextCenter(int value) {
	VMArgs[2][0] = value;

	int (__cdecl *set_text_center)(void *) = (int (__cdecl *)(void *))0x82D65388;
	set_text_center(VMArgs);
}

void unk_0x3E35563E(char *str) {
	VMArgs[2][0] = (DWORD)str;

	int (__cdecl *unk)(void *) = (int (__cdecl *)(void *))0x82D64830;
	unk(VMArgs);
}

// Suppose to be the original print but all it did was print ints
void unk_0x12929BDF(DWORD a, DWORD b) {
	VMArgs[2][0] = a;
	VMArgs[2][1] = b;

	int (__cdecl *unk)(void *) = (int (__cdecl *)(void *))0x82D64A80;
	unk(VMArgs);
}

void unk_0x6F8350CE(float x, float y) {
	VMArgs[2][0] = *(DWORD*)(&x);
	VMArgs[2][1] = *(DWORD*)(&y);

	int (__cdecl *unk)(void *) = (int (__cdecl *)(void *))0x82D64840;
	unk(VMArgs);
}

void PrintToScreen(char *str, float x, float y, int r, int g, int b, int a, float scaleX, float scaleY) {
	SetTextFont(0);
	SetTextColor(r, g, b, a);
	SetTextScale(scaleX, scaleY);
	//SetTextWrap(0.0f, 1.0f);
	SetTextCenter(0);

	unk_0x3E35563E("STRING");
	//unk_0x12929BDF((DWORD)str, true);
	//82A8B998
	int (__cdecl *unk)(void *) = (int (__cdecl *)(void *))0x82A8B998;
	unk(str);

	unk_0x6F8350CE(x, y);
}

bool HasModelLoaded(DWORD hash) {
	VMArgs[2][0] = hash;

	int (__cdecl *has_model_loaded)(void *) = (int (__cdecl *)(void *))0x82DC8FD0;
	has_model_loaded(VMArgs);

	return VMArgs[0][0];
}

void RequestModel(DWORD hash) {
	VMArgs[2][0] = hash;

	int (__cdecl *request_model)(void *) = (int (__cdecl *)(void *))0x82DC9210;
	request_model(VMArgs);
}

void SetPlayerModel(int playerId, DWORD hash) {
	VMArgs[2][0] = playerId;
	VMArgs[2][1] = hash;

	int (__cdecl *set_player_model)(void *) = (int (__cdecl *)(void *))0x82DC3090;
	set_player_model(VMArgs);
}

bool IsModelInCdImage(DWORD hash) {
	VMArgs[2][0] = hash;

	int (__cdecl *is_model_in_cdimage)(void *) = (int (__cdecl *)(void *))0x82DC9090;
	is_model_in_cdimage(VMArgs);

	return VMArgs[0][0];
}

// menu stuff
typedef enum _MainMenuOtions {
	MENU_MAIN,
	MENU_PLAYER_OPTIONS,
	MENU_VEHICLE_OPTIONS,
	MENU_WEAPON_OPTIONS,
	MENU_ONLINE_PLAYER_MENU
};

typedef enum _PlayerMenuOptions {
	PLAYER_MENU_INVINCIBILITY,
	PLAYER_MENU_STRIPPER
};

int currentMenuOption = MENU_MAIN;

bool menuActive = false;
bool buttonComboPressed = false;
bool rightBumperDown = false;
bool leftBumperDown = false;
bool xButtonDown = false;
bool dPadLeftDown = false;
bool aButtonDown = false;
bool bButtonDown = false;

bool rightBumperUsedOnce = false;
bool leftBumperUsedOnce = false;
bool aButtonUsedOnce = false;
bool bButtonUsedOnce = false;

char playerNameFormat[512];
int selectedMainMenuItem = 0;
int mainMenuItemsCount = 4;

char *mainMenuItems[4] = {
	"Player Options",
	"Vehicle Options",
	"Weapon Options",
	"Online Player Menu",
};

int selectedPlayerOption = 0;
int playerOptionsCount = 2;

char *playerOptionsItems[2] = {
	"Toggle Invincibility: true",
	"Make me a stripper baby!"
};

int selectedOnlinePlayer = 0;

bool playerInvincibilityActive = false;

void HandleMainMenu() {
	float x = 0.05000000f;
	float y = 0.10000000f;

	if (rightBumperDown && !rightBumperUsedOnce) {
		selectedMainMenuItem = (selectedMainMenuItem + 1) % mainMenuItemsCount;
		rightBumperUsedOnce = true;
	}
	else if (!rightBumperDown) {
		rightBumperUsedOnce = false;
	}

	if (leftBumperDown && !leftBumperUsedOnce) {
		selectedMainMenuItem--;

		if (selectedMainMenuItem < 0) {
			// if we went negative we go here and put it to the bottom of the list
			selectedMainMenuItem = mainMenuItemsCount - 1;
		}

		leftBumperUsedOnce = true;
	}
	else if (!leftBumperDown) {
		leftBumperUsedOnce = false;
	}

	// select an item
	if (aButtonDown && !aButtonUsedOnce) {
		printf("Selected Menu Item = %d\n", selectedMainMenuItem);

		switch(selectedMainMenuItem) {
		case 0:
			currentMenuOption = MENU_PLAYER_OPTIONS;
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			currentMenuOption = MENU_ONLINE_PLAYER_MENU;
			break;
		default:
			break;
		}

		aButtonUsedOnce = true;
	}
	else if (!aButtonDown) {
		aButtonUsedOnce = false;
	}

	// go back one
	if (bButtonDown && !bButtonUsedOnce) {
		if (currentMenuOption > 0) {
			currentMenuOption--;
		}
		bButtonUsedOnce = true;
	}
	else if (!bButtonDown) {
		bButtonUsedOnce = false;
	}

	// draw everything
	PrintToScreen("Main Menu", 0.05000000f, 0.05000000f, 0, 255, 9, 255, 0.65f, 0.65f);

	for (int i = 0; i < mainMenuItemsCount; i++) {
		if (i == selectedMainMenuItem) {
			PrintToScreen(mainMenuItems[i], x, y, 255, 0, 0, 255, 0.35f, 0.35f);
		}
		else {
			PrintToScreen(mainMenuItems[i], x, y, 255, 255, 255, 255, 0.35f, 0.35f);
		}

		y += 0.03f;
	}
}

void HandlePlayerOptions() {
	float x = 0.05000000f;
	float y = 0.10000000f;

	if (rightBumperDown && !rightBumperUsedOnce) {
		selectedPlayerOption = (selectedPlayerOption + 1) % playerOptionsCount;
		rightBumperUsedOnce = true;
	}
	else if (!rightBumperDown) {
		rightBumperUsedOnce = false;
	}

	if (leftBumperDown && !leftBumperUsedOnce) {
		selectedPlayerOption--;

		if (selectedPlayerOption < 0) {
			// if we went negative we go here and put it to the bottom of the list
			selectedPlayerOption = playerOptionsCount - 1;
		}

		leftBumperUsedOnce = true;
	}
	else if (!leftBumperDown) {
		leftBumperUsedOnce = false;
	}

	// select an item
	if (aButtonDown && !aButtonUsedOnce) {
		printf("Selected Player Option = %d\n", selectedPlayerOption);

		switch (selectedPlayerOption) {
		case PLAYER_MENU_INVINCIBILITY:
			playerInvincibilityActive = !playerInvincibilityActive;

			printf("Invincibility = %d\n", playerInvincibilityActive);

			SetPlayerInvincible(PlayerId(), playerInvincibilityActive);

			if (playerInvincibilityActive) {
				playerOptionsItems[0] = "Toggle Invincibility: true";
			}
			else {
				playerOptionsItems[0] = "Toggle Invincibility: false";
			}

			break;
		case PLAYER_MENU_STRIPPER:
			printf("IsModelInCdImage\n");
			if (IsModelInCdImage(0x9CF26183)) {
				printf("RequestModel\n");
				RequestModel(0x9CF26183);

				printf("HasModelLoaded\n");
				while (!HasModelLoaded(0x9CF26183)) {
					Sleep(10);
				}

				printf("SetPlayerModel\n");
				SetPlayerModel(PlayerId(), 0x9CF26183);
			}
			break;
		default:
			break;
		}

		aButtonUsedOnce = true;
	}
	else if (!aButtonDown) {
		aButtonUsedOnce = false;
	}

	// go back one
	if (bButtonDown && !bButtonUsedOnce) {
		currentMenuOption--;
		bButtonUsedOnce = true;
	}
	else if (!bButtonDown) {
		bButtonUsedOnce = false;
	}

	// draw everything
	PrintToScreen("Player Options", 0.05000000f, 0.05000000f, 0, 255, 9, 255, 0.65f, 0.65f);

	for (int i = 0; i < playerOptionsCount; i++) {
		if (i == selectedPlayerOption) {
			PrintToScreen(playerOptionsItems[i], x, y, 255, 0, 0, 255, 0.35f, 0.35f);
		}
		else {
			PrintToScreen(playerOptionsItems[i], x, y, 255, 255, 255, 255, 0.35f, 0.35f);
		}

		y += 0.03f;
	}
}

void HandleOnlinePlayerMenu() {
	float x = 0.05000000f;
	float y = 0.10000000f;

	if (rightBumperDown && !rightBumperUsedOnce) {
		selectedOnlinePlayer = (selectedOnlinePlayer + 1) % 16;
		rightBumperUsedOnce = true;
	}
	else if (!rightBumperDown) {
		rightBumperUsedOnce = false;
	}

	if (leftBumperDown && !leftBumperUsedOnce) {
		selectedOnlinePlayer--;

		if (selectedOnlinePlayer < 0) {
			// if we went negative we go here and put it to the bottom of the list
			selectedOnlinePlayer = 15;
		}

		leftBumperUsedOnce = true;
	}
	else if (!leftBumperDown) {
		leftBumperUsedOnce = false;
	}

	// select an item
	if (aButtonDown && !aButtonUsedOnce) {
		// do something with the player later
		printf("Selected Online Player = %d\n", selectedOnlinePlayer);

		aButtonUsedOnce = true;
	}
	else if (!aButtonDown) {
		aButtonUsedOnce = false;
	}

	// go back one
	if (bButtonDown && !bButtonUsedOnce) {
		currentMenuOption--;
		bButtonUsedOnce = true;
	}
	else if (!bButtonDown) {
		bButtonUsedOnce = false;
	}

	// draw everything
	PrintToScreen("Online Players", 0.05000000f, 0.05000000f, 0, 255, 9, 255, 0.65f, 0.65f);

	for (int i = 0; i < 16; i++) {
		if (i == selectedOnlinePlayer) {
			PrintToScreen(GetPlayerName(i), x, y, 255, 0, 0, 255, 0.35f, 0.35f);
		}
		else {
			PrintToScreen(GetPlayerName(i), x, y, 255, 255, 255, 255, 0.35f, 0.35f);
		}

		y += 0.03f;
	}
}

DWORD __stdcall TestGTAStuff(LPVOID lpParam)
{
	ExRegisterThreadNotification(&xThreadReg, TRUE);

	XINPUT_STATE xstate;

	while (TRUE)
	{
		// Get our title ID
		DWORD dwGameTitleId = XamGetCurrentTitleId();

		// making sure we are in the right game
		if (dwGameTitleId == 0x545408A7)
		{
			// handle input
			if (XInputGetState(0, &xstate) == ERROR_SUCCESS)
			{
				dPadLeftDown = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) > 0;
				xButtonDown = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_X) > 0;
				rightBumperDown = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) > 0;
				leftBumperDown = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) > 0;
				aButtonDown = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_A) > 0;
				bButtonDown = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_B) > 0;

				if((dPadLeftDown && xButtonDown) && !buttonComboPressed)
				{
					menuActive = !menuActive;

					// reset our menu states when we close
					if (!menuActive) {
						currentMenuOption = MENU_MAIN;
						selectedMainMenuItem = 0;
						selectedPlayerOption = 0;
					}

					buttonComboPressed = true;
				}
				if (!(dPadLeftDown && xButtonDown)) {
					buttonComboPressed = false;
				}
			}

			// draw menu
			if (menuActive) {
				switch (currentMenuOption) {
				case MENU_MAIN:
					HandleMainMenu();
					break;
				case MENU_PLAYER_OPTIONS:
					HandlePlayerOptions();
					break;
				case MENU_ONLINE_PLAYER_MENU:
					HandleOnlinePlayerMenu();
					break;
				default:
					currentMenuOption = MENU_MAIN;
					break;
				}
			}
		}

		// this is a pretty cheap way of doing it, it makes it all flashy
		// TODO hook into the game loop and do it a better way
		Sleep(1);
	}
}

BOOL APIENTRY DllMain( HANDLE hModule, DWORD dwReason, LPVOID lpReserved)  {
	if (dwReason == DLL_PROCESS_ATTACH)  {

		printf("GTA Fucker: Tray Staus\n");

		// for launching as a plugin
		if (GetTrayStatus() == 0x60) {
			return FALSE;
		}

		printf("GTA Fucker: Thread\n");

		HANDLE hThread; 
		DWORD threadId;

		ExCreateThread(&hThread, 0, &threadId, (VOID*)XapiThreadStartup, TestGTAStuff, NULL, 0x2 | CREATE_SUSPENDED);
		XSetThreadProcessor(hThread, 4);
		SetThreadPriority(hThread, THREAD_PRIORITY_HIGHEST);

		ResumeThread(hThread);
	}

	return TRUE;
}
