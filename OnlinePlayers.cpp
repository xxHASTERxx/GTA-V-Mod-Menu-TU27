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


#pragma region Variables

EncryptedDWORD *printToScreen_online;

unsigned int get_hash_key_online(char *key)
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


void ShowMessageOnScreen_Online(char* Text, ...) 
{
	SET_NOTIFICATION_TEXT_ENTRY("STRING");
	ADD_TEXT_COMPONENT_STRING(Text);
	_SET_NOTIFICATION_MESSAGE_CLAN_TAG("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", false, 2, "~HUD_COLOUR_BLUE~BlackLegion Mod Menu", "~HUD_COLOUR_RADAR_DAMAGE~TU 1.27", 0.5, "___XeX");
	UI::_DRAW_NOTIFICATIONv2(0, 1, 0, 255, 0, 190);
	AUDIO::PLAY_SOUND_FRONTEND(-1, "Hack_Success", "DLC_HEIST_BIOLAB_PREP_HACKING_SOUNDS");
}

enum ExlposionType_Online 
{
 GRENADE_Online,
 GRENADELAUNCHER_Online,
 STICKYBOMB_Online,
 MOLOTOV_Online, // 3
 ROCKET_Online,
 TANKSHELL_Online,
 HI_OCTANE_Online,
 CAR_Online,
 PLANE_Online,
 PETROL_PUMP_Online,
 BIKE_Online,
 DIR_STEAM_Online,
 DIR_FLAME_Online,
 DIR_WATER_HYDRANT_Online,
 DIR_GAS_CANISTER_Online,
 BOAT_Online,
 SHIP_DESTROY_Online,
 TRUCK_Online,
 BULLET_Online,
 SMOKEGRENADELAUNCHER_Online,
 SMOKEGRENADE_Online,
 BZGAS_Online,
 FLARE_Online,
 GAS_CANISTER_Online,
 EXTINGUISHER_Online,
 PROGRAMMABLEAR_Online,
 TRAIN_Online,
 BARREL_Online,
 PROPANE_Online,
 BLIMP_Online,
 DIR_FLAME_EXPLODE_Online,
 TANKER_Online,
 PLANE_ROCKET_Online,
 VEHICLE_BULLET_Online,
 GAS_TANK_Online,
 FIREWORK_Online
};

int insane;
int Handle;
int cashclient;

bool insane_test = false;
float cash[3];
float coords[3];

INT Cashtype = 0xFE18F3AF;



#pragma endregion

// Player Info
#pragma region [Online] Player Info

bool pninfo1 = false;

void pninfo()
	{
		char *playerName = GetPlayerName(cashclient);
		int subMenuIndex;
		int DisplayCar;
		float Pos[3];
		int Test =0;
		int Test2 = 0;

		GetEntityCoords(GetPlayerHandle(cashclient), Pos);
		int playerCar = PED::GET_VEHICLE_PED_IS_IN(GetPlayerHandle(cashclient), 0);
		int thisPlayersCar = ENTITY::GET_ENTITY_MODEL(playerCar);
		//int pedheading = ENTITY::GET_ENTITY_MODEL(GetPlayerHandle(cashclient));
		int pedheading = ENTITY::GET_ENTITY_HEADING(GetPlayerHandle(cashclient));
		int pedHealth = PED::GET_PED_MAX_HEALTH(GetPlayerHandle(cashclient));
		int pedArmour = PED::GET_PED_ARMOUR(GetPlayerHandle(cashclient));
		int pedPassengers = VEHICLE::GET_VEHICLE_NUMBER_OF_PASSENGERS(playerCar);
		int pedMoney = PED::GET_PED_MONEY(GetPlayerHandle(cashclient));
		
		//int GetCarColour = PED::GET_VEHICLE_EXTRA_COLOURS(GetPlayerHandle(cashclient), Test, Test2));
		
		//int pedalpha = ENTITY::GET_ENTITY_ALPHA(GetPlayerHandle(cashclient));
		GRAPHICS::DRAW_RECT(0.29, 0.86, 0.19, 0.18, 0, 0, 0, 80);

		PrintToScreen("Online Player Info", 0.2, 0.775, SpriteR, SpriteG, SpriteB, 255, 0.5, 0.5, 0, itemfont);
		PrintToScreen(playerName, 0.2f, 0.8f, 255, 255, 255, 255, 0.5f, 0.5f, 0, itemfont);//0.15 //0.25

		PrintToScreen("X:", 0.2, 0.825, 255, 255, 255, 255, 0.5, 0.5, 0, itemfont);//0.
		PrintToScreenFloat(Pos[0], 0.215, 0.825, 0, 255, 0, 255, 0.5, 0.5, 0, 6);

		PrintToScreen("Y:", 0.2, 0.85, 255, 255, 255, 255, 0.5, 0.5, 0, itemfont);
		PrintToScreenFloat(Pos[1], 0.215, 0.85, 0, 255, 0, 255, 0.5, 0.5, 0, 6);

		PrintToScreen("Z:", 0.2, 0.875, 255, 255, 255, 255, 0.5, 0.5, 0, itemfont);
		PrintToScreenFloat(Pos[2], 0.215, 0.875, 0, 255, 0, 255, 0.5, 0.5, 0, 6);

		PrintToScreen("H:", 0.2, 0.9f, 255, 255, 255, 255, 0.5, 0.5, 0, itemfont);
		PrintToScreenFloat(pedheading, 0.215f, 0.9f, 0, 255, 0, 255, 0.5, 0.5, 0, 6);

		//PrintToScreen("Alpha:", 0.2, 0.925f, 255, 255, 255, 255, 0.5, 0.5, 0, itemfont);
		//PrintToScreenFloat(pedalpha, 0.215f, 0.925f, 0, 255, 0, 255, 0.5, 0.5, 0, 6);

		PrintToScreen("Health:", 0.28, 0.85, 255, 255, 255, 255, 0.5, 0.5, 0, itemfont);
		PrintToScreenFloat(pedHealth, 0.32f, 0.85f, 0, 255, 0, 255, 0.5, 0.5, 0, 6);

		PrintToScreen("License:", 0.28, 0.9, 255, 255, 255, 255, 0.5, 0.5, 0, itemfont);
		PrintToScreen(VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(playerCar), 0.32, 0.9, 255, 255, 255, 255, 0.5, 0.5, 0, itemfont);

		PrintToScreen("Armour:", 0.28, 0.875, 255, 255, 255, 255, 0.5, 0.5, 0, itemfont);
		PrintToScreenFloat(pedArmour, 0.32f, 0.875, 0, 255, 0, 255, 0.5, 0.5, 0, 6);

		PrintToScreen("Passengers:", 0.28, 0.825, 255, 255, 255, 255, 0.5, 0.5, 0, itemfont);
		PrintToScreenFloat(pedPassengers, 0.34, 0.825, 0, 255, 0, 255, 0.5, 0.5, 0, 6);

		//PrintToScreen("Vehicle Colour:", 0.28, 0.8f, 255, 255, 255, 255, 0.5, 0.5, 0, itemfont);
		//PrintToScreen(VEHICLE::GET_VEHICLE_EXTRA_COLOURS(playerCar, Test, Test2), 0.32, 0.8f, 255, 255, 255, 255, 0.5, 0.5, 0, itemfont);
	}

int playinfo(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	cashclient = subMenuIndex;
	if (!pninfo1)
	{
	pninfo1 = true;
	ShowMessageOnScreen_Online("~p~ Player Info: ~p~ ON!");

	}
	else if (pninfo1) 
	{
	pninfo1 = false;
	ShowMessageOnScreen_Online("~p~ Player Info: ~r~ OFF!");
	}
	return 0;
}
#pragma endregion

//Give Online Options

#pragma region [Online] Give Weapon Options

#pragma region [Online] GiveAllWeapons

int GiveAllWeaponsOnline(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int player = selectedMenuIndexes->operator[](1);
	int ped = GetPlayerHandle(player);


	float Pos[3];

	GetEntityCoords(ped, Pos);

	GiveWeaponDelayed(ped, 0x3656C8C1, 9999, 1); // stun gun
	GiveWeaponDelayed(ped, 0x99B507EA, 9999, 1); // knife
	GiveWeaponDelayed(ped, 0x678B81B1, 9999, 1); // night stick
	GiveWeaponDelayed(ped, 0x4E875F73, 9999, 1); // hammer
	GiveWeaponDelayed(ped, 0x958A4A8F, 9999, 1); // bat
	GiveWeaponDelayed(ped, 0x440E4788, 9999, 1); // golf club
	GiveWeaponDelayed(ped, 0x84BD7BFD, 9999, 1); // crowbar
	GiveWeaponDelayed(ped, 0x1B06D571, 9999, 1); // pistol
	GiveWeaponDelayed(ped, 0x5EF9FEC4, 9999, 1); // combat pistol
	GiveWeaponDelayed(ped, 0x22D8FE39, 9999, 1); // ap pistol
	GiveWeaponDelayed(ped, 0x99AEEB3B, 9999, 1); // pistol 50.
	GiveWeaponDelayed(ped, 0x13532244, 9999, 1); // micro smg
	GiveWeaponDelayed(ped, 0x2BE6766B, 9999, 1); // smg
	GiveWeaponDelayed(ped, 0xEFE7E2DF, 9999, 1); // assault smg
	GiveWeaponDelayed(ped, 0xBFEFFF6D, 9999, 1); // assault rifle
	GiveWeaponDelayed(ped, 0x83BF0278, 9999, 1); // carbine rifle
	GiveWeaponDelayed(ped, 0xAF113F99, 9999, 1); // advanced rifle
	GiveWeaponDelayed(ped, 0x9D07F764, 9999, 1); // MG
	GiveWeaponDelayed(ped, 0x7FD62962, 9999, 1); // combat mg
	GiveWeaponDelayed(ped, 0x1D073A89, 9999, 1); // pump shotgun
	GiveWeaponDelayed(ped, 0x7846A318, 9999, 1); // sawnoff shotgun
	GiveWeaponDelayed(ped, 0xE284C527, 9999, 1); // assault shotgun
	GiveWeaponDelayed(ped, 0x9D61E50F, 9999, 1); // bullpupshotgun
	GiveWeaponDelayed(ped, 0x05FC3C11, 9999, 1); // sniper
	GiveWeaponDelayed(ped, 0x0C472FE2, 9999, 1); // heavy sniper
	GiveWeaponDelayed(ped, 0xA284510B, 9999, 1); // grenade launcher
	GiveWeaponDelayed(ped, 0xB1CA77B1, 9999, 1); // rpg
	GiveWeaponDelayed(ped, 0x42BF8A85, 9999, 1); // minigun
	GiveWeaponDelayed(ped, 0x93E220BD, 9999, 1); // grenades
	GiveWeaponDelayed(ped, 0x2C3731D9, 9999, 1); // sticky bomb
	GiveWeaponDelayed(ped, 0xFDBC8A50, 9999, 1); // smoke grenade
	GiveWeaponDelayed(ped, 0x34A67B97, 9999, 1); // petrol can
	GiveWeaponDelayed(ped, 0x060EC506, 9999, 1); // fire extinguisher
	GiveWeaponDelayed(ped, 0x24B17070, 9999, 1); // moltovs
	GiveWeaponDelayed(ped, 0x497FACC3, 9999, 1); // flare
    GiveWeaponDelayed(ped, 0xFDBADCED, 9999, 1); // digiscanner
	GiveWeaponDelayed(ped, 0x687652CE, 9999, 1); // stinger
	GiveWeaponDelayed(ped, 600439132,  9999, 1); // ball
	// DLC Weapons
	GiveWeaponDelayed(ped, 0xF9E6AA4B, 9999, 1); // bottle
	GiveWeaponDelayed(ped, 0x61012683, 9999, 1); // gusenerg
	GiveWeaponDelayed(ped, 0xC0A3098D, 9999, 1); // special carbine
	GiveWeaponDelayed(ped, 0xD205520E, 9999, 1); // heavy pistol
	GiveWeaponDelayed(ped, 0xBFD21232, 9999, 1); // sns pistol
	GiveWeaponDelayed(ped, 0x7F229F94, 9999, 1); // bullpup rifle
	GiveWeaponDelayed(ped, 0x92A27487, 9999, 1); // dagger
	GiveWeaponDelayed(ped, 0x083839C4, 9999, 1); // vintage pistol
	GiveWeaponDelayed(ped, 0x7F7497E5, 9999, 1); // firework launcher
	GiveWeaponDelayed(ped, 0xA89CB99E, 9999, 1); // musket
	GiveWeaponDelayed(ped, 0x63AB0442, 9999, 1); // homing launcher
	GiveWeaponDelayed(ped, 0xAB564B93, 9999, 1); // proxmine
	GiveWeaponDelayed(ped, 0x787F0BB,  9999, 1); // snowball
	GiveWeaponDelayed(ped, 0xC734385A, 9999, 1); // marksman rifle
	GiveWeaponDelayed(ped, 0x47757124, 9999, 1); // flare gun
	GiveWeaponDelayed(ped, 0x0A3D4D34, 9999, 1); // Combat PDW
	//GiveWeaponDelayed(ped, 0xE232C28C, 9999, 1); // trash bag
	//GiveWeaponDelayed(ped, 0xD04C944D, 9999, 1); // handcuffs

	ShowMessageOnScreen_Online("~p~ Gave online player all weapons");

	return 0;
}
#pragma endregion

#pragma region [Online] Give Ammo
// Give Ammo
int GiveOnlineAmmo(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int player = selectedMenuIndexes->operator[](1);
	int ped = GetPlayerHandle(player);


	float Pos[3];

	GetEntityCoords(ped, Pos);

	create_ambient_pickup(get_hash_key_online("PICKUP_AMMO_BULLET_MP"), Pos, 0, 9999, 1, 0, 1);
	create_ambient_pickup(get_hash_key_online("PICKUP_AMMO_MISSILE_MP"), Pos, 0, 9999, 1, 0, 1);
	create_ambient_pickup(get_hash_key_online("PICKUP_AMMO_GRENADELAUNCHER_MP"), Pos, 0, 9999, 1, 0, 1);
	create_ambient_pickup(get_hash_key_online("PICKUP_AMMO_PISTOL"), Pos, 0, 9999, 1, 0, 1);
	create_ambient_pickup(get_hash_key_online("PICKUP_AMMO_SMG"), Pos, 0, 9999, 1, 0, 1);
	create_ambient_pickup(get_hash_key_online("PICKUP_AMMO_RIFLE"), Pos, 0, 9999, 1, 0, 1);
	create_ambient_pickup(get_hash_key_online("PICKUP_AMMO_MG"), Pos, 0, 9999, 1, 0, 1);
	create_ambient_pickup(get_hash_key_online("PICKUP_AMMO_SHOTGUN"), Pos, 0, 19999, 1, 0, 1);
	create_ambient_pickup(get_hash_key_online("PICKUP_AMMO_SNIPER"), Pos, 0, 9999, 1, 0, 1);
	create_ambient_pickup(get_hash_key_online("PICKUP_AMMO_GRENADELAUNCHER"), Pos, 0, 9999, 1, 0, 1);
	create_ambient_pickup(get_hash_key_online("PICKUP_AMMO_RPG"), Pos, 0, 9999, 1, 0, 1);
	create_ambient_pickup(get_hash_key_online("PICKUP_AMMO_MINIGUN"), Pos, 0, 9999, 1, 0, 1);
	create_ambient_pickup(get_hash_key_online("PICKUP_AMMO_FIREWORK_MP"), Pos, 0, 9999, 1, 0, 1);
	create_ambient_pickup(get_hash_key_online("PICKUP_AMMO_HOMINGLAUNCHER"), Pos, 0, 9999, 1, 0, 1);
	create_ambient_pickup(get_hash_key_online("PICKUP_AMMO_FLAREGUN"), Pos, 0, 9999, 1, 0, 1);
	set_stat_int(get_hash_key_online("MP0_MPPLY_WAS_I_BAD_SPORT"), 0);
	set_stat_int(get_hash_key_online("MP1_MPPLY_WAS_I_BAD_SPORT"), 0);
	set_stat_int(get_hash_key_online("MP3_MPPLY_WAS_I_BAD_SPORT"), 0);
	set_stat_int(get_hash_key_online("MPPLY_GAME_EXPLOITS"), 0);
	set_stat_int(get_hash_key_online("MPPLY_EXPLOITS"), 0);

	return 0;
}

#pragma endregion

#pragma endregion

#pragma region [Online] Players GodMode

bool PlayerOnline = false;
int PlayerIndexOnline = 0;
//int PlayerIndexOnline;
float PlayerPosOnline[3];

//Online Players God Mode
bool OnlineplayerInvincibilityActive = false;
void OnlineToggleGodMode()
{	
	int subMenuIndex = PlayerIndexOnline; //<-- List of players that is grabs
	int Player = GetPlayerHandle(subMenuIndex); //<--- This grabs the name of select player on the list

	GetEntityCoords(Player, PlayerPosOnline);

	SetPlayerInvincible(Player, true);
	set_entity_proofs(Player, true, true, true, true, true, false, false, false);
	set_entity_invincible(Player, true);
}

int OnlineToggleInvincibility(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = PlayerIndexOnline; //<-- List of players that is grabs
	int Player = GetPlayerHandle(subMenuIndex); //<--- This grabs the name of select player on the list

	GetEntityCoords(Player, PlayerPosOnline);

	
	if(!OnlineplayerInvincibilityActive)
	{
	OnlineplayerInvincibilityActive = true;
	ShowMessageOnScreen_Online("~p~Player God Mode: ~g~ON!");
	PlayerIndexOnline = selectedMenuIndexes->operator[](1);
	}
	else if(OnlineplayerInvincibilityActive)
	{
	SetPlayerInvincible(Player, false);
	set_entity_proofs(Player, false, false, false, false, false, false, false, false);
	set_entity_invincible(Player, false);
	OnlineplayerInvincibilityActive = false;
	ShowMessageOnScreen_Online("~p~ Player God Mode: ~r~OFF!");
	PlayerIndexOnline = selectedMenuIndexes->operator[](1);
	}

	return 0;
}

#pragma endregion


// Online Options
#pragma region [Online] Clone Player

bool ClonePlayerOnline = false;
//int ClonePlayerIndexOnline = 0;
int ClonePlayerIndexOnline;

float ClonedPlayerPosOnline[3];

void ClonePlayerProcessOnline() 
{
	int subMenuIndex = ClonePlayerIndexOnline; //<-- List of players that is grabs
	int Player = GetPlayerHandle(subMenuIndex); //<--- This grabs the name of select player on the list

	GetEntityCoords(Player, ClonedPlayerPosOnline);

	CLONE_PED(Player, ClonedPlayerPosOnline[0], ClonedPlayerPosOnline[1], ClonedPlayerPosOnline[2]);
	ClonePlayerOnline = false;

	char szTemp[256];
	sprintf( szTemp, "~p~Player = %d", Player );
	ShowMessageOnScreen_Online( szTemp );

	sprintf( szTemp, "~p~ %s: Has been Cloned!", GetPlayerName(Player) );
	ShowMessageOnScreen_Online( szTemp );
}

int ClonePedOnlineOnline(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	if (!ClonePlayerOnline) 
	{
		ClonePlayerOnline = true;
		ClonePlayerIndexOnline = selectedMenuIndexes->operator[](1);
	}
	return 0;
}

#pragma endregion

#pragma region [Online] Steal Player Outfit

int stealoutfit(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int player = selectedMenuIndexes->operator[](1);
	int ped = GetPlayerHandle(player);


	float Pos[3];

	GetEntityCoords(ped, Pos);

	int drawable = PED::GET_PED_DRAWABLE_VARIATION(ped, 4);
	int Texture1 = PED::GET_PED_TEXTURE_VARIATION(ped, 4) ;

	PED::SET_PED_COMPONENT_VARIATION(ped, 4, drawable, Texture1, 2);
	ShowMessageOnScreen_Online("~p~ Stole Outfit!");
	return 0;
}

#pragma endregion

#pragma region [Online] Player Cash Drop

void SpawnTheMoneyBitch()
{
		GetEntityCoords(GetPlayerHandle(cashclient), cash);
		RequestModel(0x113FD533);
		
		if(HasModelLoaded(0x113FD533))
		{
		set_stat_int(get_hash_key_online("MPPLY_GAME_EXPLOITS"), 0);
		set_stat_int(get_hash_key_online("MPPLY_EXPLOITS"), 0);

		create_ambient_pickup(0xCE6FDD6B, cash, + 1, 80000, 0x113FD533, 0, 1);
		create_ambient_pickup(0xCE6FDD6B, cash, + 1, 80000, 0x113FD533, 0, 1);
		create_ambient_pickup(0xCE6FDD6B, cash, + 1, 80000, 0x113FD533, 0, 1);

		set_stat_int(get_hash_key_online("MP0_MPPLY_WAS_I_BAD_SPORT"), 0);
	    set_stat_int(get_hash_key_online("MP1_MPPLY_WAS_I_BAD_SPORT"), 0);
	    set_stat_int(get_hash_key_online("MP3_MPPLY_WAS_I_BAD_SPORT"), 0);
		}
}

void InsaneLoop() 
{
		GetEntityCoords(GetPlayerHandle(cashclient), cash);
		RequestModel(0x113FD533);
		RequestModel(0xCE6FDD6B);
		SpawnTheMoneyBitch();
}

int InsaneCashTest(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	cashclient = subMenuIndex;
	
	if (!insane_test)
	{
	insane_test = true;
	GetEntityCoords(GetPlayerHandle(subMenuIndex), coords);
	ShowMessageOnScreen_Online("~p~ Insane Drop: ~p~[ON]");

	}
	else if (insane_test) 
	{
	insane_test = false;
	ShowMessageOnScreen_Online("~p~ Insane Drop: ~r~[OFF]");
	}
	return 0;
}


#pragma endregion

#pragma region [Online] Player kill types

int blamePlayerIndex;
int kWithBlameIndex = 0;
bool blamePlayer = false;
int PlayerToBlame;
int blamedPlayer;

int sBlamedPlayerIndex = 0;
int setBlamedPlayer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	PlayerToBlame = sBlamedPlayerIndex;
	return 0;
}

int killWithBlame(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = kWithBlameIndex;
	float deadPos[3];
	GetEntityCoords(subMenuIndex, deadPos);
	AddExplosion(deadPos[0], deadPos[1], deadPos[2] - 0.8f, BLIMP_Online, 8.0f, true, false, 0.0f);;
	
	return 0;
}
int blameExplosion(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	if (!blamePlayer) 
	{
		blamePlayer = true;
		blamePlayerIndex = selectedMenuIndexes->operator[](1);
	}
	return 0;
}

int KillPassive(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);
	float Position[3];

	GetEntityCoords(Handle, Position);
	AddExplosion(Position[0], Position[1], Position[2] - 0.8f, DIR_FLAME_Online, 8.0f, true, false, 0.0f);
	return 0;
}



// Kill all passive player
void KillAllPassiveLoop()
{
	int i = 0;
	for (i = 0;i<18;i++)
    {
    if (i == PlayerId()) continue;
    int Handle = GetPlayerHandle(i);
    if(!DoesEntityExist(Handle)) continue;
	float Position[3];

    GetEntityCoords(Handle, Position);
	AddExplosion(Position[0], Position[1], Position[2] - 0.8f, DIR_FLAME_Online, 8.0f, true, false, 0.0f);
	AddExplosion(Position[0], Position[1], Position[2], BLIMP_Online, FLT_MAX, false, true, 0.0f);
	AddExplosion(Position[0], Position[1], Position[2], TRAIN_Online, FLT_MAX, false, true, 0.0f);
	}
}

bool KillAllPassive = false;
int KillAllPassiveToggle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	if (!KillAllPassive) 
	{
	KillAllPassive = true;
	ShowMessageOnScreen_Online("~p~PassiveKill All: ~g~ ON!");
	} 
	else if (KillAllPassive) 
	{
	KillAllPassive = false;
	ShowMessageOnScreen_Online("~p~PassiveKill All: ~r~ OFF!");
	}
	return 0;
}


// Forcefield Pwn
int ForceFieldKill(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);

	float Position[3];
	GetEntityCoords(Handle, Position);
	AddExplosion(Position[0], Position[1], Position[2], BLIMP_Online, FLT_MAX, false, true, 0.0f);
	AddExplosion(Position[0], Position[1], Position[2], TRAIN_Online, FLT_MAX, false, true, 0.0f);

	AddExplosion(Position[0], Position[1], Position[2], BLIMP_Online, FLT_MAX, false, true, 0.0f);
	AddExplosion(Position[0], Position[1], Position[2], TRAIN_Online, FLT_MAX, false, true, 0.0f);
	
	AddExplosion(Position[0], Position[1], Position[2], BLIMP_Online, FLT_MAX, false, true, 0.0f);
	AddExplosion(Position[0], Position[1], Position[2], TRAIN_Online, FLT_MAX, false, true, 0.0f);
	ShowMessageOnScreen_Online("~p~Forcefield Killed!");
	return 0;
}

int TunablesAddress;
int FindTunablesPointer()
{
 return TunablesAddress = (*(int*)0x83DDD934) + 4;
}


void SetTunable(int index, int value)
{
 FindTunablesPointer();
    if (TunablesAddress != 4)
    {
  int temp = TunablesAddress; 
  temp += (index * 4);
  *(int*)temp = value;
 }
}

int KickOnlinePlayer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	network_session_kick_player(subMenuIndex);
	ShowMessageOnScreen_Online("~g~ Kicked online player");
	return 0;
}


#pragma endregion

#pragma region [Online] Lobby Cash Drop

bool alldrop = false;
float allcash[50];

int AllCashDrop(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	if (!alldrop) 
	{
	alldrop = true;
	ShowMessageOnScreen_Online("~p~Lobby Drop: ~b~ ON!");
	} else if (alldrop) 
	{
	alldrop = false;
	ShowMessageOnScreen_Online("~p~Lobby Drop: ~r~ OFF!");
	}
	return 0;
}

void allcashloop() 
{
	int i = 0;
	for (i = 0; i < 18; i++) 
	{
	if (i == PlayerId()) continue;
	int Handle = GetPlayerHandle(i);
	if (!DoesEntityExist(Handle)) continue;
	
	GetEntityCoords(Handle, allcash);
	RequestModel(0x113FD533);
	
	if(HasModelLoaded(0x113FD533))
		{
			create_ambient_pickup2(0xCE6FDD6B, allcash[0], allcash[1], allcash[2] + 1, 0, 40000, 0x113FD533, 0, 1);
		}

	}
}

#pragma endregion


int BypassTUTMP0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	set_stat_bool(get_hash_key_online("MP0_NO_TUT_SPAWN"), true);
	set_stat_bool(get_hash_key_online("MP0_FRONT_END_JIP_UNLOCKED"), true);
	set_stat_bool(get_hash_key_online("MP0_FM_TRIGTUT_DONE"), true);
	set_stat_bool(get_hash_key_online("MP0_FM_HOLDTUT_DONE"), true);	
	set_stat_bool(get_hash_key_online("MP0_FM_CMODTUT_DONE"), true);
	set_stat_bool(get_hash_key_online("MP0_FM_RACETUT_DONE"), true);
	set_stat_bool(get_hash_key_online("MP0_NO_MORE_TUTORIALS"), true);
	ShowMessageOnScreen_Online("~p~ Bypass Tutorial!");
	return 0;
}

bool banloop2 = false;
int bypassthecash(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	if (!banloop2)
	{
	ShowMessageOnScreen_Online("~p~Bypass Loop: ~b~ON");
	banloop2 = true;
	}
	else if (banloop2)
	{
	banloop2 = false;
	ShowMessageOnScreen_Online("~p~Bypass Loop: ~r~OFF");
	banloop2 = false;
	}
	return 0;
}
