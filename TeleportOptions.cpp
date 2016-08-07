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

#pragma region Int,Bools,Float

bool alltelefootway = false;
bool teleportingPlayer = false;
int teleportingPlayerIndex = 0;
int teleportingPlayerTimeout = 310;
int teleportingPlayerTimeoutCounter = 0;
int animid;

#pragma endregion

#pragma region Variables

unsigned int get_hash_key_teleport(char *key)
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


void ShowMessageOnScreen_Teleport(char* Text, ...) 
{
	SET_NOTIFICATION_TEXT_ENTRY("STRING");
	ADD_TEXT_COMPONENT_STRING(Text);
	_SET_NOTIFICATION_MESSAGE_CLAN_TAG("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", false, 2, "~HUD_COLOUR_BLUE~BlackLegion Mod Menu", "~HUD_COLOUR_RADAR_DAMAGE~TU 1.27", 0.5, "___XeX");
	UI::_DRAW_NOTIFICATIONv2(0, 1, 0, 255, 0, 190);
	AUDIO::PLAY_SOUND_FRONTEND(-1, "Hack_Success", "DLC_HEIST_BIOLAB_PREP_HACKING_SOUNDS");
}

enum ExlposionType_Teleport 
{
 GRENADE_Teleport,
 GRENADELAUNCHER_Teleport,
 STICKYBOMB_Teleport,
 MOLOTOV_Teleport, // 3
 ROCKET_Teleport,
 TANKSHELL_Teleport,
 HI_OCTANE_Teleport,
 CAR_Teleport,
 PLANE_Teleport,
 PETROL_PUMP_Teleport,
 BIKE_Teleport,
 DIR_STEAM_Teleport,
 DIR_FLAME_Teleport,
 DIR_WATER_HYDRANT_Teleport,
 DIR_GAS_CANISTER_Teleport,
 BOAT_Teleport,
 SHIP_DESTROY_Teleport,
 TRUCK_Teleport,
 BULLET_Teleport,
 SMOKEGRENADELAUNCHER_Teleport,
 SMOKEGRENADE_Teleport,
 BZGAS_Teleport,
 FLARE_Teleport,
 GAS_CANISTER_Teleport,
 EXTINGUISHER_Teleport,
 PROGRAMMABLEAR_Teleport,
 TRAIN_Teleport,
 BARREL_Teleport,
 PROPANE_Teleport,
 BLIMP_Teleport,
 DIR_FLAME_EXPLODE_Teleport,
 TANKER_Teleport,
 PLANE_ROCKET_Teleport,
 VEHICLE_BULLET_Teleport,
 GAS_TANK_Teleport,
 FIREWORK_Teleport
};

#pragma endregion


#pragma region [Online] Player Teleports

#pragma region Teleport To Player

bool RequestNetworkControl(int playerHandle, int carHandle) 
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

void TeleportPlayerProcess() 
{
	int subMenuIndex = teleportingPlayerIndex;	
	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (teleportingPlayerTimeoutCounter >= teleportingPlayerTimeout)
	{
		teleportingPlayer = false;
		ShowMessageOnScreen_Teleport("~r~Failed to teleport player. Retrys timed out.");
		teleportingPlayerTimeoutCounter = 0;
		return;
	}
	if (RequestNetworkControl(Player, Vehicle))
	{
		float Position[3];
		GetEntityCoords(PlayerPedId(), Position);
		set_entity_coords(Vehicle, Position[0], Position[1] + 2.0f, Position[2] + 12.0f, 0, 0, 0, 1);
		ShowMessageOnScreen_Teleport("~p~Teleported player");
		teleportingPlayerTimeoutCounter = 0;
		teleportingPlayer = false;
	}
	teleportingPlayerTimeoutCounter++;
}

int TeleportToOnlinePlayer1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);
	
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;

	if (is_ped_in_any_vehicle(myhandle)) 
	{
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) 
		{
			float Position[3];
			GetEntityCoords(Handle, Position);
			set_entity_coords(myvehicle, Position[0], Position[1], Position[2], 0, 0, 0, 1);
		}
		else 
		{
			float Position[3];
			GetEntityCoords(Handle, Position);
			set_entity_coords(myhandle, Position[0], Position[1], Position[2], 0, 0, 0, 1);
		}
		ShowMessageOnScreen_Teleport("~p~ Teleported to online player.");
		return 0;
	}
}

#pragma endregion

#pragma region Player Teleport To Me


bool follow = false;
void MakePlayerComeTome(int playerID)
{
	if (!network_is_player_active(playerID))
	return;
	int theirPedHandle = GetPlayerHandle(playerID);
	int myPedHandle = PlayerPedId();
	if (!DoesEntityExist(theirPedHandle))
	return;
	follow = true;
}
int LolWander(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animid = subMenuIndex;
	MakePlayerComeTome(subMenuIndex);
	return 0;
}


bool telefoot = false;
void MakePlayerComeTomeFoot(int playerID)
{
	if (!network_is_player_active(playerID))
	return;
	int theirPedHandle = GetPlayerHandle(playerID);
	int myPedHandle = PlayerPedId();
	if (!DoesEntityExist(theirPedHandle))
	return;
	telefoot = true;
}
int LolWanderTele(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animid = subMenuIndex;
	MakePlayerComeTomeFoot(subMenuIndex);
	return 0;
}

/// Teleport All Players
bool alltelefoot = false;
int TeleAllOnlinePlayers(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	alltelefoot = true;
	ShowMessageOnScreen_Teleport("~p~ Teleporting all players");
	return 0;
}

int TeleportPlayerToMe(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	// Check to see if we are in the process of teleporting a player
	if (!teleportingPlayer)
	{
		teleportingPlayer = true;
		teleportingPlayerIndex = selectedMenuIndexes->operator[](1);
	}
	return 0;
}

#pragma endregion

#pragma region  Teleport To Player Car

int CarPed;
bool warp = false;

int TeleportInToCar(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	CarPed = selectedMenuIndexes->operator[](1);
	int player = selectedMenuIndexes->operator[](1);
	animid = selectedMenuIndexes->operator[](1);

	int ped = GetPlayerHandle(player);
	float Pos[3];
	GetEntityCoords(ped, Pos);
	set_entity_coords(PlayerPedId(), Pos[0], Pos[1], Pos[2]);
	warp = true;
	return 0;
}


#pragma endregion

#pragma region Teleport Player to WayPoint

int AllWay(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
	{
	alltelefootway = true;
	ShowMessageOnScreen_Teleport("~y~ Teleporting all players");
	return 0;
}


#pragma endregion


#pragma endregion
