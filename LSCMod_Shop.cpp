#pragma region Includes

#include <xtl.h>
#include <xhttp.h>
#include <xkelib.h>
#include <xauth.h>
#include "HvPeekPoke.h"

#include "globals.h" 
#include "Tools.h"
#include "GTAVMenu.h"
#include "Input.h"
#include "GTAVNatives.h"
#include "DataManager.h"
#include "ServerCommunicator.h"
#include "MenuSecurity.h"
#include "EncryptedDWORD.h"
#include "base64.h"
#include "natives.h"
#include "types.h"
#include <cfloat>
#include <string>

#pragma endregion

#pragma region Variables

bool wheelsmodded = false;
int wheel = 0;
bool custom_plate = false;
int PlateThreadValue = -1;
int rainbowcar;
bool custom_per = false;
bool rainbow = false;
EncryptedDWORD *printToScreen_LSC;

unsigned int get_hash_key_LSC(char *key)
{
	size_t len = strlen(key);
	unsigned int hash, i;
	for (hash = i = 0; i < len; ++i) 
	{
		hash += tolower(key[i]);
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}

void ShowMessageOnScreen_LSC(char* Text, ...) 
{
	SET_NOTIFICATION_TEXT_ENTRY("STRING");
	ADD_TEXT_COMPONENT_STRING(Text);
	_SET_NOTIFICATION_MESSAGE_CLAN_TAG("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", false, 2, "~HUD_COLOUR_BLUE~BlackLegion Mod Menu", "~HUD_COLOUR_RADAR_DAMAGE~TU 1.27", 0.5, "___XeX");
	UI::_DRAW_NOTIFICATIONv2(0, 1, 0, 255, 0, 190);
	AUDIO::PLAY_SOUND_FRONTEND(-1, "Hack_Success", "DLC_HEIST_BIOLAB_PREP_HACKING_SOUNDS");
}

#pragma endregion

////////////// Mod Shop Stuff goes here //////////////////

#pragma region [Los Stantos Customs Mod Shop]

XOVERLAPPED Overlapped_LSC;
XOVERLAPPED Overlapped2_LSC;
WCHAR Username_LSC[512];
WCHAR Username2_LSC[15];
WCHAR Username3_LSC[15];
WCHAR Username4_LSC[14];

DWORD WINAPI KeyboardThread(LPVOID Value)
{
	int Index = (int)Value;
	switch(Index)
	{
	case 0:
	if (custom_per) 
	{
	ZeroMemory(&Overlapped2_LSC, sizeof(Overlapped2_LSC));
	XShowKeyboardUI(0, VKBD_LATIN_NUMERIC, L"", L"Custom Performance", L"Please enter your desired performance 0 - 999", Username2_LSC, 4, &Overlapped2_LSC );
	while(!XHasOverlappedIoCompleted(&Overlapped2_LSC))
	Sleep(100);
	float result = _wtof(Username2_LSC);
	printf("Entered Float = %f \n", result);
	set_vehicle_rpm(GetCarCharIsIn(PlayerPedId(), 0), result);
	custom_per = false;
	}
	break;

	case 1:
	if (custom_plate)
	{
	ZeroMemory(&Overlapped2_LSC, sizeof(Overlapped2_LSC));
	XShowKeyboardUI(0, VKBD_DEFAULT, L"", L"Custom Plate Shop", L"Please enter your desired plate", Username2_LSC, 9, &Overlapped2_LSC );
	while(!XHasOverlappedIoCompleted(&Overlapped2_LSC))	
	Sleep(100);
	char str[9];
    wcstombs(str, Username2_LSC, 9);
	set_number_plate(GetCarCharIsIn(PlayerPedId(), 0), str);
	custom_plate = false;
	}
	break;
		/*case 10:
		 if (custom_marquee) {
		ZeroMemory(&Overlapped2, sizeof(Overlapped2));
	    XShowKeyboardUI(0, VKBD_DEFAULT, L"", L"Custom Marquee", L"Please enter desired text. I would suggest max of 50 characters including spaces.", Username2, 9, &Overlapped2 );
	    while(!XHasOverlappedIoCompleted(&Overlapped2))
		Sleep(100);
		char str[50];
        wcstombs(str, Username2, 9);
		marqueeText = str;
		custom_marquee = false;
		}
	break;*/
	}
	return 0;
}

bool RequestNetworkControl_LSC(int playerHandle, int carHandle) 
{
	int Vehicle = GetCarCharIsIn(playerHandle, 0);
	if (DoesEntityExist(carHandle) && IsEntityVehicle(carHandle))
	{
	if(network_request_control_of_entity(carHandle))
	{
	if (network_has_control_of_entity(carHandle))
	{
	return true;
			}
		}
	}
return false;
}

void supercar() {}

void enablevehmods() 
{
int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
set_vehicle_mod_kit(vehicle, 0);
}


#pragma region [Max Upgrades]

int MaxLSCUpgrades(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod_kit(vehicle, 0);
	// PaintCar(vehicle, 120, 120);
	// PaintCarExtra(vehicle, 120, 120);
	set_number_plate(vehicle, " STELIO ");
	SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle, 1);
	toggle_vehicle_mod(vehicle, 18, 1);
	toggle_vehicle_mod(vehicle, 22, 1);
	set_vehicle_mod(vehicle, 16, 5, 0);
	set_vehicle_mod(vehicle, 12, 2, 0);
	set_vehicle_mod(vehicle, 11, 3, 0);
	set_vehicle_mod(vehicle, 14, 14, 0);
	set_vehicle_mod(vehicle, 15, 3, 0);
	set_vehicle_mod(vehicle, 13, 2, 0);
	set_vehicle_wheel_type(vehicle, 6);
	set_vehicle_window_tint(vehicle, 5);
	set_vehicle_mod(vehicle, 23, 19, 1);
	set_vehicle_mod(vehicle, 0, 1, 0);
	set_vehicle_mod(vehicle, 1, 1, 0);
	set_vehicle_mod(vehicle, 2, 1, 0);
	set_vehicle_mod(vehicle, 3, 1, 0);
	set_vehicle_mod(vehicle, 4, 1, 0);
	set_vehicle_mod(vehicle, 5, 1, 0);
	set_vehicle_mod(vehicle, 6, 1, 0);
	set_vehicle_mod(vehicle, 7, 1, 0);
	set_vehicle_mod(vehicle, 8, 1, 0);
	set_vehicle_mod(vehicle, 9, 1, 0);
	set_vehicle_mod(vehicle, 10, 1, 0);

	ShowMessageOnScreen_LSC("~p~ Vehicle given the Stelio Special!");
	return 0;
}

#pragma endregion

#pragma region [Custom Plate Change]

int ChangePlate1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	custom_plate = true;
	CreateThread(0, 0, KeyboardThread, (LPVOID)1, 0, 0);
	return 0;
}

#pragma endregion

#pragma region [Custom Performence]

int TogglePerf(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	custom_per = true;
	CreateThread(0, 0, KeyboardThread, 0, 0, 0);
	return 0;
}

#pragma endregion

#pragma region [Custom Turbo]

bool turbo_check = false;
int TurboToggle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	if (!turbo_check) 
	{
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    toggle_vehicle_mod(vehicle, 18, 1);
	ShowMessageOnScreen_LSC("~p~ Turbo installed");
	turbo_check = true;
	}
	else if (turbo_check) 
	{
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	toggle_vehicle_mod(vehicle, 18, 0);
	ShowMessageOnScreen_LSC("~p~ Turbo uninstalled");
	turbo_check = false;
	}
	return 0;
}

#pragma endregion

#pragma region [Xenon Lights]

bool light_check = false;
int LightToggle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	if (!light_check)
	{
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    toggle_vehicle_mod(vehicle, 22, 1);
	ShowMessageOnScreen_LSC("~p~ Xenon Lights installed");
	light_check = true;
	}
	else if (light_check)
	{
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	toggle_vehicle_mod(vehicle, 22, 0);
	ShowMessageOnScreen_LSC("~p~ Xenon Lights uninstalled");
	light_check = false;
	}
	return 0;
}

#pragma endregion

#pragma region [Paints]

#pragma region [Rainbow Car]

int irand(int min, int max, int Add = 0) 
{
	srand(GetTickCount() + Add);
	return min + (rand() % (int)(max - min + 1));
}

int ToggleRainbow(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	if(rainbow) 
	{
		//printf("\nrainbow = false!\n\n");
		rainbow = false;
		return 0;
	}
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	rainbowcar = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(rainbowcar) && IsEntityVehicle(rainbowcar))
	{
		//printf("Attempted to paint vehicle");
		rainbow = true;
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}

void rainbow_car() 
{
	if (DoesEntityExist(rainbowcar) && IsEntityVehicle(rainbowcar))
	{
		int col1 = irand(0, 255, 200);
		int col2 = irand(0, 255, -40);
		int col3 = irand(0, 255, 30);
		int col4 = irand(0, 255, 400);
		set_vehicle_dirt_level(rainbowcar, 0.0f);
		PaintCar(rainbowcar, col1, col2);
		PaintCarExtra(rainbowcar, col3, col4);
	}
}

int RandomPaint(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
	set_vehicle_dirt_level(vehicle, 0.0f);
	PaintCar(vehicle, irand(0, 255, 200), irand(0, 255, -40));
	PaintCarExtra(vehicle, irand(0, 255, 30), irand(0, 255, 400));
	}
	}
	else
	{
	ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}

#pragma endregion

int GetColour2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	int vehicle;
	char PColour[256];
	char SColour[256];
	char Mod1Colour[256];
	char Mod2Colour[256];
	char EXColour[256];

	int primary_r, primary_g, primary_b;
	int secondary_r, secondary_g, secondary_b;
	
	int carmod_r, carmod_g, carmod_b;
	int carmod2_r, carmod2_g, carmod2_b;

	int extra_r, extra_g;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
	GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, &primary_r, &primary_g, &primary_b);
	sprintf(PColour, "~p~ PRIMARY COLOUR: = RGB( %d, %d, %d )", primary_r, primary_g, primary_b, vehicle);
	ShowMessageOnScreen_LSC(PColour); 

	GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, &secondary_r, &secondary_g, &secondary_b);
    sprintf(SColour, "~p~ Secondary COLOUR: = RGB( %d, %d, %d )", secondary_r, secondary_g, secondary_b, vehicle);
	ShowMessageOnScreen_LSC(SColour); 
	


	GET_VEHICLE_MOD_COLOR_1(vehicle, &carmod_r, &carmod_g, &carmod_b);
	sprintf(Mod1Colour, "~p~ Mod1: = Values( %d, %d, %d )", carmod_r, carmod_g, carmod_b, vehicle);
	ShowMessageOnScreen_LSC(Mod1Colour); 

	GET_VEHICLE_MOD_COLOR_2(vehicle, &carmod2_r, &carmod2_g, &carmod2_b);
	sprintf(Mod2Colour, "~p~  Mod2: = Values( %d, %d, %d )", carmod2_r, carmod2_g, carmod2_b, vehicle);
	ShowMessageOnScreen_LSC(Mod2Colour); 

	GET_VEHICLE_EXTRA_COLOURS(vehicle, &extra_r ,&extra_g);
	sprintf(EXColour, "~p~  Extra colours: = Values( %d, %d )", extra_r, extra_g, vehicle);
	ShowMessageOnScreen_LSC(EXColour);

	//print(VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(lastv,0,0,0));
		}
	}
return 0;
}

#pragma region [Basic Colours]

int PaintRed(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 29, 29);
		PaintCarExtra(vehicle, 29, 29);
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}

int PaintOrange(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle))
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 41, 41);
		PaintCarExtra(vehicle, 41, 41);
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}

int PaintPurple(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 145, 145);
		PaintCarExtra(vehicle, 145, 145);
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}

int PaintBlack(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle))
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 0, 0);
		PaintCarExtra(vehicle, 0, 0);
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("~p~ You aren't in a vehicle");
	}
	return 0;
}

int PaintLimeGreen(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle))
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 92, 92);
		PaintCarExtra(vehicle, 92, 92);
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}

int PaintHotPink(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle))
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 135, 135);
		PaintCarExtra(vehicle, 135, 135);
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}

#pragma endregion

#pragma region [Combo Paints]

int PaintCombo01(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 0, 120);
		PaintCarExtra(vehicle, 0, 0);
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}

int PaintCombo02(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle))
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 121, 120);
		PaintCarExtra(vehicle, 0, 0);
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}

int PaintCombo03(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 112, 0);
		PaintCarExtra(vehicle, 0, 0);
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}

int PaintCombo04(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 154, 0);
		PaintCarExtra(vehicle, 0, 0);
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("~p~ You aren't in a vehicle");
	}
	return 0;
}

int PaintCombo05(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 140, 120);
		PaintCarExtra(vehicle, 0, 140);
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}

int PaintCombo06(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 92, 120);
		PaintCarExtra(vehicle, 0, 92);
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}

int PaintCombo07(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle))
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 135, 120);
		PaintCarExtra(vehicle, 0, 135);
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}

int PaintCombo08(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle))
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 0, 112);
		PaintCarExtra(vehicle, 0, 112);
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}

int PaintCombo09(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 29, 0);
		PaintCarExtra(vehicle, 0, 0);
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}

#pragma endregion

#pragma region [Custom Paints]

////////[Custom Paints]///

#pragma region [Potant Algy]

void PotantAlgy()
{

#pragma region Function

	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 6, -1, -1); //Matallic
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 0,16,41);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 8,8,8);

		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 6, -1, 0); // Pearl
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, 91, 0); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
#pragma endregion

}	

int PaintPotantAlgy(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
PotantAlgy();
return 0;
}

#pragma endregion

#pragma region [Blue Monday]

void BlueMonday()
{

#pragma region Function

	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 0, 0, 0); //Metallic
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 28,47,79);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 28,47,79);

		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 2, 0, 0); // Pearl
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, 111, 0); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
#pragma endregion

}	

int PaintBlueMonday(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
BlueMonday();
return 0;
}

#pragma endregion

#pragma region [Doppler Effect]

#pragma region Function

void DopplerEffect()
{
	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 0, 0, 0); //Metallic
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 88,0,132);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 88,0,132);

		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 2, 0, 0); // Pearl
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, (Any)135, (Any)0); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
}

#pragma endregion


int PaintDopplerEffect(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
DopplerEffect();
return 0;
}


#pragma endregion

#pragma region [Stay Fly]

#pragma region Function

void StayFly()
{
	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 3, 0, 0); //Matte
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 91,0,114);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 91,0,114);

		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 2, 0, 0); // Pearl
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, (Any)70, (Any)0); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
}

#pragma endregion

int PaintStayFly(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
StayFly();
return 0;
}


#pragma endregion

#pragma region [Polar Night]

#pragma region Function

void PolarNight()
{
	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 0, 0, 0); //Metallic
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 0,72,242);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 0,72,242);

		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 2, 0, 0); // Pearl
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, (Any)55, (Any)0); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
}



#pragma endregion

int PaintPolarNight(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
PolarNight();
return 0;
}


#pragma endregion

#pragma region [ArticQ]

#pragma region Function

void ArticQ()
{
	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 3, 0, 0); //Matte
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 74,126,239);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 74,126,239);

		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 2, 0, 0); // Pearl
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, (Any)140, (Any)0); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
}



#pragma endregion

int PaintArticQ(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
ArticQ();
return 0;
}

#pragma endregion

#pragma region [Green]

#pragma region Function

void Green()
{
	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 3, 0, 0); //Matte
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 3,102,17);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 3,102,17);

		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 2, 0, 0); // Pearl
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, (Any)89, (Any)0); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
}


#pragma endregion

int PaintGreen(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
Green();
return 0;
}

#pragma endregion

#pragma region [Blue Diamond]

#pragma region Function

void BlueDiamond()
{
	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 3, 0, 0); //Matte
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 74,167,214);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 74,167,214);

		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 2, 0, 0); // Pearl
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, (Any)131, (Any)0); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
}


#pragma endregion

int PaintBlueDiamond(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
BlueDiamond();
return 0;
}

#pragma endregion

#pragma region [Chrome Gold]

#pragma region Function

void ChromeGold()
{
	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 5, 0, 0); //Chrome
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 252,184,41);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 252,184,41);

		//VEHICLE::SET_VEHICLE_MOD_COLOR_2((Any)5, (Any)0, (Any)0); // Chrome
		//VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, EX_Paint, 0); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
}


#pragma endregion

int PaintChromeGold(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
ChromeGold();
return 0;
}

#pragma endregion

#pragma region [Galaxy]

#pragma region Function

void Galaxy()
{
	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 0, 0, 0); //Metallic
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 0,8,15);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 0,8,15);

		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 2, 0, 0); // Pearl
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, 35, 156); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
}


#pragma endregion

int PaintGalaxy(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
Galaxy();
return 0;
}

#pragma endregion

#pragma region [Fade]

#pragma region Function

void Fade()
{
	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int P_Paint = (16,0,41);
	int S_Paint = (16,0,41);
	int EX_Paint =((Any)89, (Any)0);

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 3, 0, 0); //Matte
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 16,0,41);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 16,0,41);

		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 2, 0, 0); // Pearl
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, (Any)89, (Any)0); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
}


#pragma endregion

int PaintFade(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
Fade();
return 0;
}

#pragma endregion

#pragma region [GlowGreen]

#pragma region Function

void GlowGreen()
{
	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int P_Paint = (3,255,7);
	int S_Paint = (3,255,7);
	int EX_Paint =((Any)112, (Any)0);

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 3, 0, 0); //Matte
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 121,255,33);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 121,255,33);

		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 2, 0, 0); // Pearl
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, (Any)112, (Any)112); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
}


#pragma endregion

int PaintGlowGreen(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
GlowGreen();
return 0;
}

#pragma endregion

#pragma region [Marble]

#pragma region Function

void Marble()
{
	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 3, 0, 0); //Matte
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 16,0,41);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 16,0,41);

		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 2, 0, 0); // Pearl
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, (Any)70, (Any)0); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
}


#pragma endregion

int PaintMarble(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
Marble();
return 0;
}

#pragma endregion

// Page 2
#pragma region [Fire]

#pragma region Function

void Fire()
{
	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 3, 0, 0); //Matte
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 255,0,0);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 255,0,0);

		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 2, 0, 0); // Pearl
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, (Any)89, (Any)0); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
}


#pragma endregion

int PaintFire(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
Fire();
return 0;
}

#pragma endregion

#pragma region [Demon Purple]

#pragma region Function

void DemonPurple()
{
	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/
		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 0, 0, 0); //Metallic
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 0,8,15);
		
		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 1, 0, 8); //Pearl
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 8,8,8);
		
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
}


#pragma endregion

int PaintDemonPurple(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
DemonPurple();
return 0;
}

#pragma endregion

#pragma region [Demon Purple V2]

#pragma region Function

void DemonPurpleV2()
{
	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle,3, 0, 0); //Matte
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 5,0,8);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 5,0,8);

		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 2, 0, 0); // Pearl
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, 145, 142); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
}


#pragma endregion

int PaintDemonPurpleV2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
DemonPurpleV2();
return 0;
}

#pragma endregion

#pragma region [LavaOrange]

#pragma region Function

void LavaOrange()
{
	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 0, 0, 0); //Matallic
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 105,0,0);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 105,0,0);

		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 2, 0, 0); // Pearl
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, 89, 156); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
}


#pragma endregion

int PaintLavaOrange(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
LavaOrange();
return 0;
}




#pragma region [Experimental]

int PaintTest2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	int TestColor1 = (255,255,255);
	int TestColor2 = (255,0,0);
	
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);
		
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, TestColor1, TestColor2, 0);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, TestColor1, TestColor2, 0);
		//PaintCar(vehicle, TestColor1,TestColor2);
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}


void Testing3()
{
	int vehicle;
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);

	GRAPHICS::DRAW_RECT(0.29, 0.86, 0.19, 0.18, 0, 0, 0, 80);
	PrintToScreen("Vehicle Colour:", 0.28, 0.875, 255, 255, 255, 255, 0.5, 0.5, 0, itemfont);
	PrintToScreenFloat(vehicle, 0.32f, 0.875, 0, 255, 0, 255, 0.5, 0.5, 0, 6);
		
}
int PaintTest3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int P_Paint = (73,24,129);
	int S_Paint = (73,24,129);
	int EX_Paint =((Any)70, (Any)0);

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 0, 0, 0); //Metallic
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, P_Paint ,0 ,0);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, S_Paint, 0, 0);

		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 2, 0, 0); // Pearl
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, EX_Paint, 0); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}

#pragma endregion

#pragma endregion

#pragma region [Coral]

#pragma region Function

void Coral()
{
	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 0, 0, 0); //Matallic
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 0,33,30);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 0,33,30);

		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 2, 0, 0); // Pearl
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, 91, 156); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
}


#pragma endregion

int PaintCoral(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
Coral();
return 0;
}

#pragma endregion

#pragma region [Purple Crush]

#pragma region Function

void PurpleCrush()
{
	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 0, 0, 0); //Matallic
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 22,22,41);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 22,22,41);

		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 2, 0, 0); // Pearl
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, 89, 156); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
}


#pragma endregion

int PaintPurpleCrush(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
PurpleCrush();
return 0;
}

#pragma endregion

#pragma region [Passion Fruit 3]

#pragma region Function

void PassionFruit3()
{
	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 0, 0, 0); //Matallic
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 50,6,66);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 50,6,66);

		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 2, 0, 0); // Pearl
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, 138, 0); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
}


#pragma endregion

int PaintPassionFruit3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
PassionFruit3();
return 0;
}

#pragma endregion

#pragma region [Tron]

#pragma region Function

void Tron()
{
	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 3, 0, 0); //Matallic
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 18,18,18);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 18,18,18);

		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 2, 0, 0); // Pearl
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, 70, 0); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
}


#pragma endregion

int PaintTron(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
Tron();
return 0;
}

#pragma endregion

#pragma region [Tron2]

#pragma region Function

void Tron2()
{
	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 0, 0, 0); //Matallic
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 15,15,15);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 15,15,15);

		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 2, 0, 0); // Pearl
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, 70, 0); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
}


#pragma endregion

int PaintTron2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
Tron2();
return 0;
}

#pragma endregion

#pragma region [Chrome Blue]

#pragma region Function

void ChromeBlue()
{
	int lastv = GET_PLAYERS_LAST_VEHICLE();
	int vehicle;
	char PColour[256];
	char SColour[256];
	char EXColour[256];

	int r, g , b, r1, g1, b1, r2, g2;

	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);

		/*
		SHADERS:	
		0=metallic	,
		1=classic	,
		2=?	,	
		3=matte		,	
		4=metal		,
		5=chrome,
		*/
		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 5, 0, 0); //Chrome
		//VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 3, 0, 0); //Matallic
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 15,15,15);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 15,15,15);

		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 3, 0, 0); // Pearl
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, 70, 0); 
		}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
}


#pragma endregion

int PaintChromeBlue(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
ChromeBlue();
return 0;
}

#pragma endregion





#pragma region [Rims]
///////////////////////[Rim Paints]//////////////////////////
/////////////////////////////////////////////////////////////
int PaintRim0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle))
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCarExtra(vehicle, 0, 92);
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}

int PaintRim1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle))
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCarExtra(vehicle, 0, 0);
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}

int PaintRim2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCarExtra(vehicle, 0, 112);
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}

int PaintRim3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCarExtra(vehicle, 0, 140);
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}

int PaintRim4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCarExtra(vehicle, 0, 135);
	}
	}
	else{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}

int PaintRim5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCarExtra(vehicle, 0, 145);
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("r~ You aren't in a vehicle");
	}
	return 0;
}

int PaintRim6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) 
	{
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCarExtra(vehicle, 0, 29);
	}
	}
	else
	{
		ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle");
	}
	return 0;
}

#pragma endregion

#pragma region [Wheels]


int StockWheels(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 23);
	ShowMessageOnScreen_LSC("~p~ Stock wheels applied");
	return 0;
}

int StockTyres(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ Stock tyres applied, If your wheels changed with the tyres just change your wheels in the menu!");
	return 0;
}

int CustomTyres(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 23, wheel, 1);
	ShowMessageOnScreen_LSC("~p~ Custom tyres applied, If your wheels changed with the tyres just change your wheels in the menu!");
	return 0;
}

int BpTyres(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_tyres_can_burst(vehicle, 0);
	ShowMessageOnScreen_LSC("~p~ Your tyres are now bulletproof!");
	return 0;
}

#pragma region [Offroad]

int Offroad0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	wheel = 0;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 4);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Offroad1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	wheel = 1;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 4);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Offroad2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 2;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 4);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Offroad3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	wheel = 3;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 4);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Offroad4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 4;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 4);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Offroad5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	wheel = 5;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 4);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Offroad6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 6;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 4);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Offroad7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	wheel = 7;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 4);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Offroad8(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	wheel = 8;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 4);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Offroad9(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 9;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 4);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

#pragma endregion

#pragma region [HighEnd]

int HighEnd0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 0;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int HighEnd1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 1;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int HighEnd2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 2;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int HighEnd3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 3;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int HighEnd4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 4;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int HighEnd5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 5;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int HighEnd6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 6;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int HighEnd7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 7;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int HighEnd8(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 8;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int HighEnd9(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 9;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int HighEnd10(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 10;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int HighEnd11(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 11;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int HighEnd12(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 12;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int HighEnd13(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 13;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int HighEnd14(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 14;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int HighEnd15(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 15;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int HighEnd16(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 16;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int HighEnd17(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 17;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int HighEnd18(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 18;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int HighEnd19(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 19;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
#pragma endregion

#pragma region [Lowrider]


int Lowrider0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 0;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Lowrider1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 1;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Lowrider2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 2;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Lowrider3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 3;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Lowrider4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 4;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Lowrider5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 5;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Lowrider6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 6;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Lowrider7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 7;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Lowrider8(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 8;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Lowrider9(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 9;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Lowrider10(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 10;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Lowrider11(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 11;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Lowrider12(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 12;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Lowrider13(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 13;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Lowrider14(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 14;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

#pragma endregion

#pragma region [Muscle]

int Muscle0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 0;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Muscle1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 1;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Muscle2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 2;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Muscle3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 3;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Muscle4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 4;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Muscle5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	wheel = 5;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Muscle6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 6;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Muscle7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 7;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Muscle8(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 8;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Muscle9(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 9;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Muscle10(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 10;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Muscle11(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 11;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Muscle12(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 12;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Muscle13(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 13;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Muscle14(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 14;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Muscle15(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 15;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Muscle16(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 16;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Muscle17(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 17;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

#pragma endregion

#pragma region [Sport]

int Sport0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	wheel = 0;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	wheel = 1;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	wheel = 2;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	wheel = 3;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	wheel = 4;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 5;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 6;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 7;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport8(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 8;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport9(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	wheel = 9;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport10(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	wheel = 10;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport11(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 11;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport12(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	wheel = 12;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport13(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 13;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport14(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 14;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport15(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 15;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport16(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	wheel = 16;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport17(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 17;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport18(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 18;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport19(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 19;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport20(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 20;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport21(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	wheel = 21;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport22(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	wheel = 22;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport23(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	wheel = 23;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Sport24(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	wheel = 24;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

#pragma endregion

#pragma region [SUV]


int SUV0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 0;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int SUV1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 1;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int SUV2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 2;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int SUV3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 3;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int SUV4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 4;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int SUV5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 5;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int SUV6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 6;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int SUV7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 7;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int SUV8(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 8;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int SUV9(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 9;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int SUV10(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 10;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int SUV11(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 11;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int SUV12(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 12;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int SUV13(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 13;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int SUV14(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 14;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int SUV15(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 15;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int SUV16(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 16;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int SUV17(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 17;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int SUV18(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 18;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

#pragma endregion

#pragma region [Tuner]


int Tuner0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 0;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Tuner1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 1;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Tuner2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 2;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Tuner3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 3;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Tuner4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 4;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int Tuner5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 5;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int Tuner6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 6;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int Tuner7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 7;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int Tuner8(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 8;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int Tuner9(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 9;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int Tuner10(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 10;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int Tuner11(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 11;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int Tuner12(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 12;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int Tuner13(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 13;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int Tuner14(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 14;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int Tuner15(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 15;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int Tuner16(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 16;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int Tuner17(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 17;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int Tuner18(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 18;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}
int Tuner19(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 19;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Tuner20(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 20;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Tuner21(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 21;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Tuner22(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 22;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

int Tuner23(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 23;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen_LSC("~p~ New wheels have been applied!");
	return 0;
}

#pragma endregion


#pragma endregion

#pragma region [Horns]

int StockHorn(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 14);
	ShowMessageOnScreen_LSC("~p~ Stock horn installed");
	return 0;
}

int Horn0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 0, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 1, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 2, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 3, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 4, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 5, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 6, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 7, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn8(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 8, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn9(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 9, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn10(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 10, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn11(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 11, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn12(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 12, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn13(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 13, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn14(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 14, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn15(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 15, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn16(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 16, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn17(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 17, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn18(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 18, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn19(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 19, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn20(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 20, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn21(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 21, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn22(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 22, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn23(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 23, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn24(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 24, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn25(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 25, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn26(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 26, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn27(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 27, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn28(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 28, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn29(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 29, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

int Horn30(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 30, 0);
	ShowMessageOnScreen_LSC("~p~ Horn installed");
	return 0;
}

#pragma endregion

#pragma region [Full Body Kit]

#pragma region [Front & Back Bumpers]

///// Front Bumper /////////
int StockFb(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 1);
	ShowMessageOnScreen_LSC("~p~ Stock front bumper installed");
	return 0;
}

int Fb0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 1, 0, 0);
	ShowMessageOnScreen_LSC("~p~ Front bumper 1 installed");
	return 0;
}

int Fb1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 1, 1, 0);
	ShowMessageOnScreen_LSC("~p~ Front bumper 2 installed");
	return 0;
}

int Fb2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 1, 2, 0);
	ShowMessageOnScreen_LSC("~p~ Front bumper 3 installed");
	return 0;
}

int Fb3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 1, 3, 0);
	ShowMessageOnScreen_LSC("~p~ Front bumper 3 installed");
	return 0;
}

int Fb4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 1, 4, 0);
	ShowMessageOnScreen_LSC("~p~ Front bumper 3 installed");
	return 0;
}

int Fb5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 1, 5, 0);
	ShowMessageOnScreen_LSC("~p~ Front bumper 3 installed");
	return 0;
}

////// Rear Bumper ////////
int StockRb(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 2);
	ShowMessageOnScreen_LSC("~p~ Stock rear bumper installed");
	return 0;
}

int Rb0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 2, 0, 0);
	ShowMessageOnScreen_LSC("~p~ Rear bumper 1 installed");
	return 0;
}

int Rb1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 2, 1, 0);
	ShowMessageOnScreen_LSC("~p~ Rear bumper 2 installed");
	return 0;
}

int Rb2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 2, 2, 0);
	ShowMessageOnScreen_LSC("~p~ Rear bumper 3 installed");
	return 0;
}

int Rb3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 2, 3, 0);
	ShowMessageOnScreen_LSC("~p~ Rear bumper 4 installed");
	return 0;
}
#pragma endregion

#pragma region [Side Skirts]

////// Side Skirts //////
int StockSk(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 3);
	ShowMessageOnScreen_LSC("~p~ Stock side skirts installed");
	return 0;
}

int Sk0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 3, 0, 0);
	ShowMessageOnScreen_LSC("~p~ Side skirts 1 installed");
	return 0;
}

int Sk1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 3, 1, 0);
	ShowMessageOnScreen_LSC("~p~ Side skirts 2 installed");
	return 0;
}

int Sk2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 3, 2, 0);
	ShowMessageOnScreen_LSC("~p~ Side skirts 3 installed");
	return 0;
}

int Sk3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 3, 3, 0);
	ShowMessageOnScreen_LSC("~p~ Side skirts 4 installed");
	return 0;
}

#pragma endregion

#pragma region [Hoods]

/////// Hoods ////////
int StockHood(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 7);
	ShowMessageOnScreen_LSC("~p~ Stock hood installed");
	return 0;
}

int Hood0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 7, 0, 0);
	ShowMessageOnScreen_LSC("~p~ Hood 1 installed");
	return 0;
}

int Hood1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 7, 1, 0);
	ShowMessageOnScreen_LSC("~p~ Hood 2 installed");
	return 0;
}

int Hood2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 7, 2, 0);
	ShowMessageOnScreen_LSC("~p~ Hood 3 installed");
	return 0;
}

int Hood3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 7, 3, 0);
	ShowMessageOnScreen_LSC("~p~ Hood 4 installed");
	return 0;
}

int Hood4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 7, 4, 0);
	ShowMessageOnScreen_LSC("~p~ Hood 5 installed");
	return 0;
}

#pragma endregion

#pragma region [Fenders Left & Right]

////// Fenders [Right & Left] ////////
int StockLFender(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 8);
	ShowMessageOnScreen_LSC("~p~ Stock left fender installed");
	return 0;
}

int LFender0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 8, 0, 0);
	ShowMessageOnScreen_LSC("~p~ Left fender 1 installed");
	return 0;
}

int LFender1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 8, 1, 0);
	ShowMessageOnScreen_LSC("~p~ Left fender 2 installed");
	return 0;
}

int LFender2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 8, 2, 0);
	ShowMessageOnScreen_LSC("~p~ Left fender 3 installed");
	return 0;
}

int StockRFender(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 8);
	ShowMessageOnScreen_LSC("~p~ Stock right fender installed");
	return 0;
}

int RFender0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 9, 0, 0);
	ShowMessageOnScreen_LSC("~p~ Right fender 1 installed");
	return 0;
}

int RFender1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 9, 1, 0);
	ShowMessageOnScreen_LSC("~p~ Right fender 2 installed");
	return 0;
}

int RFender2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 9, 2, 0);
	ShowMessageOnScreen_LSC("~p~ Right fender 3 installed");
	return 0;
}

#pragma endregion

#pragma region [Roofs]

///// Roof ///////
int StockRoof(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 10);
	ShowMessageOnScreen_LSC("~p~ Stock roof installed");
	return 0;
}

int Roof0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 10, 0, 0);
	ShowMessageOnScreen_LSC("~p~ Roof 1 installed");
	return 0;
}

int Roof1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 10, 1, 0);
	ShowMessageOnScreen_LSC("~p~ Roof 2 installed");
	return 0;
}

int Roof2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 10, 2, 0);
	ShowMessageOnScreen_LSC("~p~ Roof 3 installed");
	return 0;
}

int Roof3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 10, 3, 0);
	ShowMessageOnScreen_LSC("~p~ Roof 4 installed");
	return 0;
}

#pragma endregion

#pragma region [Interiors]

//////Interiors ////////
int StockInterior(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 5);
	ShowMessageOnScreen_LSC("~p~ Stock interior/chassis installed");
	return 0;
}

int Interior0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 5, 0, 0);
	ShowMessageOnScreen_LSC("~p~ Interior/Chassis installed");
	return 0;
}

int Interior1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 5, 1, 0);
	ShowMessageOnScreen_LSC("~p~ Interior/Chassis installed");
	return 0;
}

int Interior2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 5, 2, 0);
	ShowMessageOnScreen_LSC("~p~ Interior/Chassis installed");
	return 0;
}

int Interior3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 5, 3, 0);
	ShowMessageOnScreen_LSC("~p~ Interior/Chassis installed");
	return 0;
}

#pragma endregion

#pragma region [Grills]

/////// Grills ///////
int StockGrill(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 6);
	ShowMessageOnScreen_LSC("~p~ Stock grill installed");
	return 0;
}

int Grill0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 6, 0, 0);
	ShowMessageOnScreen_LSC("~p~ Grill 1 installed");
	return 0;
}

int Grill1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 6, 1, 0);
	ShowMessageOnScreen_LSC("~p~ Grill 2 installed");
	return 0;
}

int Grill2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 6, 2, 0);
	ShowMessageOnScreen_LSC("~p~ Grill 3 installed");
	return 0;
}

int Grill3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 6, 3, 0);
	ShowMessageOnScreen_LSC("~p~ Grill 4 installed");
	return 0;
}

#pragma endregion

#pragma endregion

#pragma region [Spoilers]

int StockSpoiler(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 0);
	ShowMessageOnScreen_LSC("~p~ Stock spoiler installed");
	return 0;
}

int Spoiler0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 0, 0, 0);
	ShowMessageOnScreen_LSC("~p~ Spoiler 1 installed");
	return 0;
}

int Spoiler1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 0, 1, 0);
	ShowMessageOnScreen_LSC("~p~ Spoiler 2 installed");
	return 0;
}

int Spoiler2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 0, 2, 0);
	ShowMessageOnScreen_LSC("~p~ Spoiler 3 installed");
	return 0;
}

int Spoiler3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 0, 3, 0);
	ShowMessageOnScreen_LSC("~p~ Spoiler 4 installed");
	return 0;
}

int Spoiler4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 0, 4, 0);
	ShowMessageOnScreen_LSC("~p~ Spoiler 5 installed");
	return 0;
}

int Spoiler5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 0, 5, 0);
	ShowMessageOnScreen_LSC("~p~ Spoiler 6 installed");
	return 0;
}

int Spoiler6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 0, 6, 0);
	ShowMessageOnScreen_LSC("~p~ Spoiler 7 installed");
	return 0;
}

#pragma endregion

#pragma region [Exhaust]

int ExStock(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 4);
	ShowMessageOnScreen_LSC("~p~ Stock exhaust installed");
	return 0;
}

int Ex0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 4, 0, 0);
	ShowMessageOnScreen_LSC("~p~ Exhaust 1 installed");
	return 0;
}

int Ex1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 4, 1, 0);
	ShowMessageOnScreen_LSC("~p~ Exhaust 2 installed");
	return 0;
}

int Ex2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 4, 2, 0);
	ShowMessageOnScreen_LSC("~p~ Exhaust 3 installed");
	return 0;
}

int Ex3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 4, 3, 0);
	ShowMessageOnScreen_LSC("~p~ Exhaust 4 installed");
	return 0;
}

#pragma endregion

#pragma region [Suspension]

int SuspStock(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 15);
	ShowMessageOnScreen_LSC("~p~ Stock suspension installed");
	return 0;
}

int Susp0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 15, 0, 0);
	ShowMessageOnScreen_LSC("~p~ Lowered suspension installed");
	return 0;
}

int Susp1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 15, 1, 0);
	ShowMessageOnScreen_LSC("~p~ Street suspension installed");
	return 0;
}

int Susp2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 15, 2, 0);
	ShowMessageOnScreen_LSC("~p~ Sports suspension installed");
	return 0;
}

int Susp3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 15, 3, 0);
	ShowMessageOnScreen_LSC("~p~ Competition suspension installed");
	return 0;
}

#pragma endregion

#pragma region [Brakes]

int BrakeStock(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 12);
	ShowMessageOnScreen_LSC("~p~ Stock brakes installed");
	return 0;
}

int Brake0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 12, 0, 0);
	ShowMessageOnScreen_LSC("~p~ Street brakes installed");
	return 0;
}

int Brake1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 12, 1, 0);
	ShowMessageOnScreen_LSC("~p~ Sports brakes installed");
	return 0;
}

int Brake2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 12, 2, 0);
	ShowMessageOnScreen_LSC("~p~ Race brakes installed");
	return 0;
}

#pragma endregion

#pragma region [Transmission]

int TranStock(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 13);
	ShowMessageOnScreen_LSC("~p~ Stock transmission installed");
	return 0;
}

int Tran0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 13, 0, 0);
	ShowMessageOnScreen_LSC("~p~ Street transmission installed");
	return 0;
}

int Tran1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 13, 1, 0);
	ShowMessageOnScreen_LSC("~p~ Sports transmission installed");
	return 0;
}

int Tran2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 13, 2, 0);
    ShowMessageOnScreen_LSC("~p~ Race transmission installed");
	return 0;
}

#pragma endregion

#pragma region [Engine]

int EngineStock(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 11);
	ShowMessageOnScreen_LSC("~p~ Stock engine installed");
	return 0;
}

int Engine0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 11, 0, 0);
	ShowMessageOnScreen_LSC("~p~ New engine has been installed!");
	return 0;
}

int Engine1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 11, 1, 0);
	ShowMessageOnScreen_LSC("~p~ New engine has been installed!");
	return 0;
}

int Engine2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 11, 2, 0);
	ShowMessageOnScreen_LSC("~p~ New engine has been installed!");
	return 0;
}

int Engine3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 11, 3, 0);
	ShowMessageOnScreen_LSC("~p~ New engine has been installed!");
	return 0;
}

#pragma endregion

#pragma region [Tints]


int Tint0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    set_vehicle_window_tint(vehicle, 4);
	ShowMessageOnScreen_LSC("~p~ Tint removed!");
	return 0;
}

int Tint1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    set_vehicle_window_tint(vehicle, 3);
	ShowMessageOnScreen_LSC("~p~ Light tint installed!");
	return 0;
}

int Tint2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    set_vehicle_window_tint(vehicle, 2);
	ShowMessageOnScreen_LSC("~p~ Dark tint installed!");
	return 0;
}

int Tint3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    set_vehicle_window_tint(vehicle, 1);
	ShowMessageOnScreen_LSC("~p~ Limo tint installed!");
	return 0;
}

int Tint4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    set_vehicle_window_tint(vehicle, 5);
	ShowMessageOnScreen_LSC("~p~ Mexican's Black tint installed!");
	return 0;
}

int Tint5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    set_vehicle_window_tint(vehicle, 7);
	ShowMessageOnScreen_LSC("~p~ Mexican's Green tint installed!");
	return 0;
}

#pragma endregion

#pragma region [Armour]

int NoArmour(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 16);
	ShowMessageOnScreen_LSC("~p~ Armour removed");
	return 0;
}

int Armour0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 16, 0, 0);
	ShowMessageOnScreen_LSC("~p~ 20 percent Armour installed");
	return 0;
}

int Armour1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 16, 1, 0);
	ShowMessageOnScreen_LSC("~p~ 40 percent Armour installed");
	return 0;
}

int Armour2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 16, 2, 0);
	ShowMessageOnScreen_LSC("~p~ 60 percent Armour installed");
	return 0;
}

int Armour3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 16, 3, 0);
	ShowMessageOnScreen_LSC("~p~ 80 percent Armour installed");
	return 0;
}

int Armour4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 16, 4, 0);
	ShowMessageOnScreen_LSC("~p~ 100 percent Armour installed");
	return 0;
}

#pragma endregion

#pragma region [Smoke]

int Smoke0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_tyre_smoke_color(vehicle, 255, 0, 0);
	ShowMessageOnScreen_LSC("~p~ Red tyre smoke applied");
	return 0;
}

int Smoke1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_tyre_smoke_color(vehicle, 0, 255, 0);
	ShowMessageOnScreen_LSC("~p~ Green tyre smoke applied");
	return 0;
}

int Smoke2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_tyre_smoke_color(vehicle, 0, 0, 255);
	ShowMessageOnScreen_LSC("~p~ Blue tyre smoke applied");
	return 0;
}

int Smoke3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_tyre_smoke_color(vehicle, 127, 0, 255);
	ShowMessageOnScreen_LSC("~p~ Purple tyre smoke applied");
	return 0;
}

int Smoke4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_tyre_smoke_color(vehicle, 255, 51, 255);
	ShowMessageOnScreen_LSC("~p~ Pink tyre smoke applied");
	return 0;
}

int Smoke5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_tyre_smoke_color(vehicle, 102, 178, 255);
	ShowMessageOnScreen_LSC("~p~ Sky blue tyre smoke applied");
	return 0;
}

int Smoke6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_tyre_smoke_color(vehicle, 255, 128, 0);
	ShowMessageOnScreen_LSC("~p~ Orange tyre smoke applied");
	return 0;
}

int Smoke7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_tyre_smoke_color(vehicle, 255, 255, 0);
	ShowMessageOnScreen_LSC("~p~ Yellow tyre smoke applied");
	return 0;
}

int Smoke8(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_tyre_smoke_color(vehicle, 0, 255, 255);
	ShowMessageOnScreen_LSC("~p~ Cyan tyre smoke applied");
	return 0;
}

#pragma endregion



#pragma region []

#pragma endregion

#pragma region []

#pragma endregion

///////////////////////////////
///////////////////////////////
#pragma endregion

#pragma endregion

/////////////[Other Cars Stuff here]//////////////////////

#pragma region [Fix The Car]

int FixMyCar(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) 
	{
	myvehicle = GetCarCharIsIn(myhandle, 0);
	if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) 
	{
	FixCar(myvehicle);
	set_vehicle_dirt_level(myvehicle, 0.0f);
	ShowMessageOnScreen_LSC("~p~ Fixed Vehicle!");
		}
	}
	else
	{
	ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle!");
	}
	return 0;
}

int FixPlayerCar(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int myhandle = GetPlayerHandle(subMenuIndex);
	float Position[3];

	GetEntityCoords(myhandle, Position);

	//int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) 
	{
	myvehicle = GetCarCharIsIn(myhandle, 0);
	if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) 
	{
	FixCar(myvehicle);
	set_vehicle_dirt_level(myvehicle, 0.0f);
	ShowMessageOnScreen_LSC("~p~ Fixed Vehicle!");
		}
	}
	else
	{
	ShowMessageOnScreen_LSC("~r~ You aren't in a vehicle!");
	}
	return 0;
}

#pragma endregion

#pragma region [Set Stolen or Not Stolen]

int NoStolenVehicle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	int Veh = GetCarCharIsIn(PlayerPedId(), 0);
	if(IS_VEHICLE_STOLEN(Veh))
	{
	  SET_VEHICLE_IS_STOLEN(Veh, false);
	}
	return 0;
}

int StolenVehicle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	int Veh = GetCarCharIsIn(PlayerPedId(), 0);
	if(!IS_VEHICLE_STOLEN(Veh))
	{
	  SET_VEHICLE_IS_STOLEN(Veh, true);
	}
	return 0;
}


int PlayerNoStolenVehicle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Veh = GetPlayerHandle(subMenuIndex);
	float Position[3];

	//int Veh = GetCarCharIsIn(PlayerPedId(), 0);
	if(IS_VEHICLE_STOLEN(Veh))
	{
	  SET_VEHICLE_IS_STOLEN(Veh, false);
	}
	return 0;
}
int PlayerStolenVehicle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Veh = GetPlayerHandle(subMenuIndex);
	float Position[3];

	//int Veh = GetCarCharIsIn(PlayerPedId(), 0);
	if(!IS_VEHICLE_STOLEN(Veh))
	{
	  SET_VEHICLE_IS_STOLEN(Veh, true);
	}
	return 0;
}

#pragma endregion


#pragma endregion














