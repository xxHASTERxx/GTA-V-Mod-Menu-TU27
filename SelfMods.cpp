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

bool playerInvincibilityActive = false;
bool showingMessageOnScreen_self = false;
bool SelfInvis = false;

int fagcashclient;
bool fagdropbool = false;
float fagcash[3];

void ShowMessageOnScreen_self(char* Text, ...) 
{
	SET_NOTIFICATION_TEXT_ENTRY("STRING");
	ADD_TEXT_COMPONENT_STRING(Text);
	_SET_NOTIFICATION_MESSAGE_CLAN_TAG("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", false, 2, "~HUD_COLOUR_BLUE~BlackLegion Mod Menu", "~HUD_COLOUR_RADAR_DAMAGE~TU 1.27", 0.5, "___XeX");
	UI::_DRAW_NOTIFICATIONv2(0, 1, 0, 255, 0, 190);
	AUDIO::PLAY_SOUND_FRONTEND(-1, "Hack_Success", "DLC_HEIST_BIOLAB_PREP_HACKING_SOUNDS");
}
unsigned int get_hash_key_self(char *key)
{
	size_t len = strlen(key);
    unsigned int hash, i;
    for(hash = i = 0; i < len; ++i)
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

enum ExlposionType_Self 
{
 GRENADE_Self,
 GRENADELAUNCHER_Self,
 STICKYBOMB_Self,
 MOLOTOV_Self, // 3
 ROCKET_Self,
 TANKSHELL_Self,
 HI_OCTANE_Self,
 CAR_Self,
 PLANE_Self,
 PETROL_PUMP_Self,
 BIKE_Self,
 DIR_STEAM_Self,
 DIR_FLAME_Self,
 DIR_WATER_HYDRANT_Self,
 DIR_GAS_CANISTER_Self,
 BOAT_Self,
 SHIP_DESTROY_Self,
 TRUCK_Self,
 BULLET_Self,
 SMOKEGRENADELAUNCHER_Self,
 SMOKEGRENADE_Self,
 BZGAS_Self,
 FLARE_Self,
 GAS_CANISTER_Self,
 EXTINGUISHER_Self,
 PROGRAMMABLEAR_Self,
 TRAIN_Self,
 BARREL_Self,
 PROPANE_Self,
 BLIMP_Self,
 DIR_FLAME_EXPLODE_Self,
 TANKER_Self,
 PLANE_ROCKET_Self,
 VEHICLE_BULLET_Self,
 GAS_TANK_Self,
 FIREWORK_Self
};

// [Self Toggles]
#pragma region GodMode

//God Mode

void ToggleSelfGodMode()
{
	SetPlayerInvincible(PlayerId(), true);
	set_entity_proofs(PlayerPedId(), true, true, true, true, true, false, false, false);
	set_entity_invincible(PlayerPedId(), true);
}
int SelfInvincibility(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	if(!playerInvincibilityActive)
	{
	  playerInvincibilityActive = true;
	  ShowMessageOnScreen_self("~p~ God Mode: [~p~ON!]");
	}
	else if(playerInvincibilityActive)
	{
	SetPlayerInvincible(PlayerId(), false);
	set_entity_proofs(PlayerPedId(), false, false, false, false, false, false, false, false);
	set_entity_invincible(PlayerPedId(), false);
	playerInvincibilityActive = false;
	ShowMessageOnScreen_self("~p~ God Mode: [~r~Off!]");
	}
	return 0;
}

#pragma region OffRadar

int OffRadar(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	NETWORK_SPENT_BUY_OFFTHERADAR;
	ShowMessageOnScreen_self("~p~  Off The Radar: [~r~On!]");
	return 0;
}

#pragma endregion


#pragma region NeverWanted

// Never Wanted
bool SelfWanted = false;
int wantedvar = 0;

void SelfWantedLoop() 
{
set_player_wanted_level(PlayerId(), 0);
}

int SelfWantedPlayer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
if (wantedvar == 0)
{
SelfWanted = true;
wantedvar = 1;
ShowMessageOnScreen_self("~p~ Never Wanted: [~p~On!~p~]");
}
else if (wantedvar == 1)
{
SelfWanted = false;
wantedvar = 0;
ShowMessageOnScreen_self("~p~ Never Wanted: [~r~Off!~p~]");
}
return 0;
}


#pragma endregion

#pragma region Self Invisibility



void SelfInvisibilityLoop()
{
int player = GetPlayerHandle(PlayerId());
set_entity_visible(player, false);

}

int SetInvisible(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int player = GetPlayerHandle(PlayerId());

	if (!SelfInvis)
	{
	SelfInvis = true;
	set_entity_visible(PlayerId(), true);
	ShowMessageOnScreen_self("~p~ Now Invisible: [~p~On!]");
	}
	else if (SelfInvis)
	{
	set_entity_visible(PlayerId(), false);
	ShowMessageOnScreen_self("~p~ Now Visible: [~r~Off!]");
	SelfInvis = false;
	}
return 0;
}

#pragma endregion

///// [Weapons]

#pragma region ExplodeAmmo
bool SelfExplosiveAmmo = false;

void ExplosiveAmmoLoop()
{
	set_explosive_ammo_this_frame(PlayerId());
}

int ExplosiveAmmo(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	if(!SelfExplosiveAmmo)
	{
		SelfExplosiveAmmo = true;
		ShowMessageOnScreen_self("Explosive Ammo: ~g~ON!");
	}
	else if(SelfExplosiveAmmo)
	{
		SelfExplosiveAmmo = false;
		ShowMessageOnScreen_self("Explosive Ammo: ~r~OFF!");
	}
	return 0;
}

#pragma endregion

#pragma region FireAmmo
bool SelfFireAmmo =false;

void SelfFireAmmoLoop()
{
	set_fire_ammo_this_frame(PlayerId());

}
int FireAmmo(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	
	if(!SelfFireAmmo)
	{
		SelfFireAmmo = true;
		ShowMessageOnScreen_self("~p~ Fire Ammo: [~p~ON!]");
	}
	else if(SelfFireAmmo)
	{
		SelfFireAmmo = false;
		ShowMessageOnScreen_self("~p~ Fire Ammo: [~r~OFF!]");
	}

	return 0;
}

#pragma endregion

#pragma region Self Inf Ammo
// Inf Ammo
bool SelfAmmo;

int SelfToggleAmmo(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	if (!SelfAmmo) 
	{
	SelfAmmo = true;
	set_ped_infinite_ammo_clip(PlayerPedId(), true);
	ShowMessageOnScreen_self("~p~ Inf Ammo: [~p~ON!]");
	}
	else if (SelfAmmo) 
	{
    set_ped_infinite_ammo_clip(PlayerPedId(), false);
	ShowMessageOnScreen_self("~p~ Inf Ammo: [~r~OFF!]");
    SelfAmmo = false;
	}
    //ShowMessageOnScreen("~r~ Sorry this has been disabled for now it isn't working properly!");
	return 0;
}
#pragma endregion

#pragma region Force Field

bool field = false;
int fieldvar = 0;
float Position[3];

void SelfForceFieldLoop() 
{
	GetEntityCoords(GetPlayerHandle(PlayerId()), Position);
	AddExplosion(Position[0], Position[1], Position[2], BLIMP_Self, FLT_MAX, false, true, 0.0f);
	AddExplosion(Position[0], Position[1], Position[2], TRAIN_Self, FLT_MAX, false, true, 0.0f);

	AddExplosion(Position[0], Position[1], Position[2], BLIMP_Self, FLT_MAX, false, true, 0.0f);
	AddExplosion(Position[0], Position[1], Position[2], TRAIN_Self, FLT_MAX, false, true, 0.0f);
	
	AddExplosion(Position[0], Position[1], Position[2], BLIMP_Self, FLT_MAX, false, true, 0.0f);
	AddExplosion(Position[0], Position[1], Position[2], TRAIN_Self, FLT_MAX, false, true, 0.0f);
}

int SelfFieldToggle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	if (fieldvar == 0)
	{
		field = true;
		fieldvar = 1;
		ShowMessageOnScreen_self("~p~ Force Field: [~p~ON]");
		SetPlayerInvincible(PlayerId(), true);
	} 
	else if (fieldvar == 1)
	{
		field = false;
		fieldvar = 0;
		ShowMessageOnScreen_self("~p~ Force Field: [~r~OFF]");
		SetPlayerInvincible(PlayerId(), false);
	}
	return 0;
}



#pragma endregion

///// [Self Give Options]

#pragma region GiveAllWeps

int GiveAllWeapons(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{
	int player = selectedMenuIndexes->operator[](1);
	int ped = GetPlayerHandle(player);

	GiveWeaponDelayed(PlayerPedId(), 0x3656C8C1, 9999, 1); // stun gun
	GiveWeaponDelayed(PlayerPedId(), 0x99B507EA, 9999, 1); // knife
	GiveWeaponDelayed(PlayerPedId(), 0x678B81B1, 9999, 1); // night stick
	GiveWeaponDelayed(PlayerPedId(), 0x4E875F73, 9999, 1); // hammer
	GiveWeaponDelayed(PlayerPedId(), 0x958A4A8F, 9999, 1); // bat
	GiveWeaponDelayed(PlayerPedId(), 0x440E4788, 9999, 1); // golf club
	GiveWeaponDelayed(PlayerPedId(), 0x84BD7BFD, 9999, 1); // crowbar
	GiveWeaponDelayed(PlayerPedId(), 0x1B06D571, 9999, 5); // pistol
	GiveWeaponDelayed(PlayerPedId(), 0x5EF9FEC4, 9999, 1); // combat pistol
	GiveWeaponDelayed(PlayerPedId(), 0x22D8FE39, 9999, 1); // ap pistol
	GiveWeaponDelayed(PlayerPedId(), 0x99AEEB3B, 9999, 1); // pistol 50.
	GiveWeaponDelayed(PlayerPedId(), 0x13532244, 9999, 1); // micro smg
	GiveWeaponDelayed(PlayerPedId(), 0x2BE6766B, 9999, 1); // smg
	GiveWeaponDelayed(PlayerPedId(), 0xEFE7E2DF, 9999, 1); // assault smg
	GiveWeaponDelayed(PlayerPedId(), 0xBFEFFF6D, 9999, 1); // assault rifle
	GiveWeaponDelayed(PlayerPedId(), 0x83BF0278, 9999, 1); // carbine rifle
	GiveWeaponDelayed(PlayerPedId(), 0xAF113F99, 9999, 1); // advanced rifle
	GiveWeaponDelayed(PlayerPedId(), 0x9D07F764, 9999, 1); // MG
	GiveWeaponDelayed(PlayerPedId(), 0x7FD62962, 9999, 1); // combat mg
	GiveWeaponDelayed(PlayerPedId(), 0x1D073A89, 9999, 1); // pump shotgun
	GiveWeaponDelayed(PlayerPedId(), 0x7846A318, 9999, 1); // sawnoff shotgun
	GiveWeaponDelayed(PlayerPedId(), 0xE284C527, 9999, 1); // assault shotgun
	GiveWeaponDelayed(PlayerPedId(), 0x9D61E50F, 9999, 1); // bullpupshotgun
	GiveWeaponDelayed(PlayerPedId(), 0x05FC3C11, 9999, 1); // sniper
	GiveWeaponDelayed(PlayerPedId(), 0x0C472FE2, 9999, 1); // heavy sniper
	GiveWeaponDelayed(PlayerPedId(), 0xA284510B, 9999, 1); // grenade launcher
	GiveWeaponDelayed(PlayerPedId(), 0xB1CA77B1, 9999, 1); // rpg
	GiveWeaponDelayed(PlayerPedId(), 0x42BF8A85, 9999, 1); // minigun
	GiveWeaponDelayed(PlayerPedId(), 0x93E220BD, 9999, 1); // grenades
	GiveWeaponDelayed(PlayerPedId(), 0x2C3731D9, 9999, 1); // sticky bomb
	GiveWeaponDelayed(PlayerPedId(), 0xFDBC8A50, 9999, 1); // smoke grenade
	GiveWeaponDelayed(PlayerPedId(), 0x34A67B97, 9999, 1); // petrol can
	GiveWeaponDelayed(PlayerPedId(), 0x060EC506, 9999, 1); // fire extinguisher
	GiveWeaponDelayed(PlayerPedId(), 0x24B17070, 9999, 1); // moltovs
	GiveWeaponDelayed(PlayerPedId(), 0x497FACC3, 9999, 1); // flare
	GiveWeaponDelayed(PlayerPedId(), 0xFDBADCED, 9999, 1); // digiscanner
	GiveWeaponDelayed(PlayerPedId(), 0x687652CE, 9999, 1); // stinger
	GiveWeaponDelayed(PlayerPedId(), 600439132, 9999, 1); // ball
	
	//DLC Weapons
	GiveWeaponDelayed(PlayerPedId(), 0xF9E6AA4B, 9999, 1); // bottle
	GiveWeaponDelayed(PlayerPedId(), 0x61012683, 9999, 1); // gusenerg
	GiveWeaponDelayed(PlayerPedId(), 0xC0A3098D, 9999, 1); // special carbine
	GiveWeaponDelayed(PlayerPedId(), 0xD205520E, 9999, 1); // heavy pistol
	GiveWeaponDelayed(PlayerPedId(), 0xBFD21232, 9999, 1); // sns pistol
	GiveWeaponDelayed(PlayerPedId(), 0x7F229F94, 9999, 1); // bullpup rifle
	GiveWeaponDelayed(PlayerPedId(), 0x92A27487, 9999, 1); // dagger
	GiveWeaponDelayed(PlayerPedId(), 0x083839C4, 9999, 1); // vintage pistol
	GiveWeaponDelayed(PlayerPedId(), 0x7F7497E5, 9999, 1); // firework launcher
	GiveWeaponDelayed(PlayerPedId(), 0xA89CB99E, 9999, 1); // musket
	GiveWeaponDelayed(PlayerPedId(), 0x63AB0442, 9999, 1); // homing launcher
	GiveWeaponDelayed(PlayerPedId(), 0xAB564B93, 9999, 1); // proxmine
	GiveWeaponDelayed(PlayerPedId(), 0x787F0BB, 9999, 1); // snowball
	GiveWeaponDelayed(PlayerPedId(), 0xC734385A, 9999, 1); // marksman rifle
	GiveWeaponDelayed(PlayerPedId(), 0x47757124, 9999, 1); // flare gun
	GiveWeaponDelayed(PlayerPedId(), 0x0A3D4D34, 9999, 1); // Combat PDW
	GiveWeaponDelayed(PlayerPedId(), 0xF9D04ADB, 9999, 1); // marksman pistol
	GiveWeaponDelayed(PlayerPedId(), 0xB32BE614, 9999, 1); // knuckle dusters
	GiveWeaponDelayed(PlayerPedId(), 0x0A3D4D34, 9999, 1); // combat pdw
//	GiveWeaponDelayed(PlayerPedId(), get_hash_key("PICKUP_WEAPON_HEAVYSHOTGUN"), 9999, 1); // HEAVYSHOTGUN

	//Attachments FlashLight
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xAF113F99, 0x359B7AAE); //Advanced Rifle
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x0A3D4D34, 0x7BC4CDDC); //Combat PDW
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x13532244, 0x359B7AAE); //Micro SMG
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x22D8FE39, 0x359B7AAE); //AP Pistol
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xD205520E, 0x359B7AAE); //Heavy Pistol
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x7F229F94, 0x7BC4CDDC); //Bullpump Rifle
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x1B06D571, 0x359B7AAE); //Pistol
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x5EF9FEC4, 0x359B7AAE); //Combat Pistol
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x99AEEB3B, 0x359B7AAE); //.50 Pistol
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x2BE6766B, 0x7BC4CDDC); //SMG
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xEFE7E2DF, 0x7BC4CDDC); //Assault SMG
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xBFEFFF6D, 0x7BC4CDDC); //Assault Rifle
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x83BF0278, 0x7BC4CDDC); //Carbine Rifle

	//Attachments Clips
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xAF113F99, 0x8EC1C979); //Extened Clip Advanced Rifle
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x05FC3C11, 0xBC54DA77); //Advanced scope Sniper Rifle
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x22D8FE39, 0x249A17D5); //Extended Clip AP Pistol
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x0C472FE2, 0xBC54DA77); //Advanced scope Heavy Sniper
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xD205520E, 0x64F9C62B); //Heavy Pistol
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xBFD21232, 0x7B0033B3); //SNS Pistol
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xC0A3098D, 0x7C8BD10E); //Special Carbine
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xE284C527, 0x86BD7F72); //Assault Shotgun
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x7F229F94, 0xB3688B0F); //Bullpump Rifle
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x7FD62962, 0xD6C59CD6); //Combat MG
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x1B06D571, 0xED265A1C); //Pistol
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x5EF9FEC4, 0xD67B4F2D); //Combat Pistol
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x99AEEB3B, 0xD9D3AC92); //.50 Pistol
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x083839C4, 0x33BA12E8); //Vintage Pistol
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x13532244, 0x10E6BA2B); //Micro SMG
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x2BE6766B, 0x350966FB); //SMG
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xEFE7E2DF, 0xBB46E417); //Assault SMG
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x0A3D4D34, 0x334A5203); //Combat PDW
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x9D07F764, 0x82158B47); //MG
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x61012683, 0xEAC8C270); //Gusenberg
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xBFEFFF6D, 0xB1214F9B); //Assault Rifle
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x83BF0278, 0x91109691); //Carbine Rifle
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xC734385A, 0xCCFD2AC5); //Marksman Rifle
//	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), get_hash_key("PICKUP_WEAPON_HEAVYSHOTGUN"), 0x971CF6FD); //Heavy Shotgun


	//Attachments Scopes
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xAF113F99, 0xAA2C45B4); //Extened Clip Advanced Rifle
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x05FC3C11, 0xD2443DDC); //Advanced scope Sniper Rifle, 
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x0C472FE2, 0xD2443DDC); //Advanced scope Heavy Sniper
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xC0A3098D, 0xA0D89C42); //Special Carbine
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x7F229F94, 0xAA2C45B4); //Bullpump Rifle
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x13532244, 0x9D2FBF29); //Micro SMG
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x2BE6766B, 0x3CC6BA57); //SMG
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xEFE7E2DF, 0x9D2FBF29); //Assault SMG
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x0A3D4D34, 0xAA2C45B4); //Combat PDW
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x3C00AFED, 0x82158B47); //MG
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xBFEFFF6D, 0x9D2FBF29); //Assault Rifle
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x83BF0278, 0xA0D89C42); //Carbine Rifle

	//Attachments Supressors
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xAF113F99, 0x8EC1C979); //Advanced Rifle
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x05FC3C11, 0xA73D4664); //Sniper Rifle
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x22D8FE39, 0xC304849A); //AP Pistol
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xD205520E, 0xC304849A); //Heavy Pistol
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xC0A3098D, 0xA73D4664); //Special Carbine
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x7F229F94, 0x837445AA); //Bullpump Rifle
	//GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x9D61E50F, 0xA73D4664); //Bullpump ShotGun
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x1B06D571, 0x65EA7EBB); //Pistol
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x5EF9FEC4, 0xC304849A); //Combat Pistol
	//GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x99AEEB3B, 0xA73D4664); //.50 Pistol
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x083839C4, 0xC304849A); //Vintage Pistol
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x2BE6766B, 0xC304849A); //SMG
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xEFE7E2DF, 0xA73D4664); //Assault SMG
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xBFEFFF6D, 0xA73D4664); //Assault Rifle
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x83BF0278, 0x837445AA); //Carbine Rifle
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xC734385A, 0x837445AA); //Marksman Rifle
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x1D073A89, 0xE608B35E); //Pump Shotgun
//	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), get_hash_key("PICKUP_WEAPON_HEAVYSHOTGUN"), 0xA73D4664); //Heavy Shotgun

	//Attachments Grip
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xC0A3098D, 0xC164F53); //Special Carbine
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x7F229F94, 0xC164F53); //Bullpump Rifle
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x9D61E50F, 0xC164F53); //Bullpump ShotGun
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xBFEFFF6D, 0xC164F53); //Assault Rifle
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x83BF0278, 0xC164F53); //Carbine Rifle
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xC734385A, 0xC164F53); //Marksman Rifle
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x0A3D4D34, 0xC164F53); //Combat PDW
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x7FD62962, 0xC164F53); //Combat MG
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0xE284C527, 0xC164F53); //Assault Shotgun
//	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), get_hash_key("PICKUP_WEAPON_HEAVYSHOTGUN"), 0xC164F53); //Heavy Shotgun

	//Special Finish
	GIVE_WEAPON_COMPONENT_TO_PED(PlayerPedId(), 0x83BF0278, 0xD89B9658); //Carbine Rifle

	//Paints
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x1B06D571, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x5EF9FEC4, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x22D8FE39, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x99AEEB3B, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x13532244, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x2BE6766B, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0xEFE7E2DF, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0xBFEFFF6D, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x83BF0278, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0xAF113F99, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x9D07F764, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x7FD62962, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x1D073A89, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x7846A318, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0xE284C527, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x9D61E50F, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x05FC3C11, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x0C472FE2, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0xA284510B, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0xB1CA77B1, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x42BF8A85, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x687652CE, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x61012683, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0xC0A3098D, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0xD205520E, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0xBFD21232, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x7F229F94, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x083839C4, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x7F7497E5, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0xA89CB99E, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x63AB0442, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0xC734385A, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x0A3D4D34, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0xF9D04ADB, 2);
	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), 0x0A3D4D34, 2);
//	SET_PED_WEAPON_TINT_INDEX(PlayerPedId(), get_hash_key("PICKUP_WEAPON_HEAVYSHOTGUN"), 2);
	
	ShowMessageOnScreen_self("~p~ Gave all weapons" +(ped) );
	return 0;
}

#pragma endregion

#pragma region Max Health/Armour

int GiveHealth(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	float Pos[3];
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);

	float HealthNeeded = GET_ENTITY_MAX_HEALTH(Handle) - GET_ENTITY_HEALTH(Handle); //Note: This should get the health they need.
	GetEntityCoords(Handle, Pos);
    create_ambient_pickup(get_hash_key_self("PICKUP_HEALTH_STANDARD"), Pos, 0, HealthNeeded, 1, 0, 1);
	create_ambient_pickup(get_hash_key_self("PICKUP_HEALTH_STANDARD"), Pos, 0, HealthNeeded, 1, 0, 1);
	create_ambient_pickup(get_hash_key_self("PICKUP_HEALTH_STANDARD"), Pos, 0, HealthNeeded, 1, 0, 1);
	create_ambient_pickup(get_hash_key_self("PICKUP_HEALTH_STANDARD"), Pos, 0, HealthNeeded, 1, 0, 1);
	return 0;
}

int GiveHealthTest(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int player = selectedMenuIndexes->operator[](1);
	int ped = GetPlayerHandle(player);

	float HealthNeeded = GET_ENTITY_MAX_HEALTH(PlayerPedId()) - GET_ENTITY_HEALTH(PlayerPedId());
	return 0;
}

int GiveArmour(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int player = selectedMenuIndexes->operator[](1);
	int ped = GetPlayerHandle(player);

	float Pos[3];
	GetEntityCoords(ped, Pos);
       create_ambient_pickup(get_hash_key_self("PICKUP_ARMOUR_STANDARD"), Pos, 0, 100, 1, 0, 1);
	   create_ambient_pickup(get_hash_key_self("PICKUP_ARMOUR_STANDARD"), Pos, 0, 100, 1, 0, 1);
	   create_ambient_pickup(get_hash_key_self("PICKUP_ARMOUR_STANDARD"), Pos, 0, 100, 1, 0, 1);
	   create_ambient_pickup(get_hash_key_self("PICKUP_ARMOUR_STANDARD"), Pos, 0, 100, 1, 0, 1);
	   create_ambient_pickup(get_hash_key_self("PICKUP_ARMOUR_STANDARD"), Pos, 0, 100, 1, 0, 1);
	return 0;
}

#pragma endregion

// [Self Cash Drop]
#pragma region Self Cash Drop
//
//bool drop = false;
//float cash[100];
////int cashclient;
//
//void cashloop()
//{
//	GetEntityCoords(GetPlayerHandle(PlayerId()), cash);
//
//       RequestModel(0x113FD533);
//		if(HasModelLoaded(0x113FD533))
//		{
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[2], fagcash[1], fagcash[0] + 0, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[5], fagcash[4], fagcash[3] + 1, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[8], fagcash[7], fagcash[6] + 2, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[11], fagcash[10], fagcash[9] + 0, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[14], fagcash[13], fagcash[12] + 1, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[17], fagcash[16], fagcash[15] + 2, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[20], fagcash[19], fagcash[18] + 0, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[23], fagcash[22], fagcash[21] + 1, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[26], fagcash[25], fagcash[24] + 2, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[29], fagcash[28], fagcash[27] + 0, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[32], fagcash[31], fagcash[30] + 1, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[35], fagcash[34], fagcash[33] + 2, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[38], fagcash[37], fagcash[36] + 0, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[41], fagcash[40], fagcash[39] + 1, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[44], fagcash[43], fagcash[42] + 2, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[48], fagcash[47], fagcash[46] + 0, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[51], fagcash[50], fagcash[49] + 1, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[54], fagcash[53], fagcash[52] + 2, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[57], fagcash[56], fagcash[55] + 0, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[60], fagcash[59], fagcash[58] + 1, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[63], fagcash[62], fagcash[61] + 2, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[66], fagcash[65], fagcash[64] + 0, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[69], fagcash[68], fagcash[67] + 1, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[72], fagcash[71], fagcash[70] + 2, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[75], fagcash[74], fagcash[73] + 0, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[78], fagcash[77], fagcash[76] + 1, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[81], fagcash[80], fagcash[79] + 2, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[84], fagcash[83], fagcash[82] + 0, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[87], fagcash[86], fagcash[85] + 1, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[90], fagcash[89], fagcash[88] + 2, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[94], fagcash[93], fagcash[92] + 0, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[97], fagcash[96], fagcash[95] + 1, 0, 80000, 0x113FD533, 0, 1);
//		create_ambient_pickup2(0xCE6FDD6B, fagcash[100], fagcash[99], fagcash[98] + 2, 0, 80000, 0x113FD533, 0, 1);
//	}
//}
//
//int SelfCashDrop(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
//{
//	int subMenuIndex = selectedMenuIndexes->operator[](1);
//	fagcashclient = subMenuIndex;
//
//	if (!fagdropbool) 
//	{
//	cashloop();
//	fagdropbool = true;
//	ShowMessageOnScreen_self("~p~Self Test Drop: [~g~On!]");
//	GetEntityCoords(GetPlayerHandle(subMenuIndex), cash);
//	}
//	else if (fagdropbool) 
//	{
//	fagdropbool = false;
//	ShowMessageOnScreen_self("~p~Self Test Drop: [~r~Off!]");
//	GetEntityCoords(GetPlayerHandle(subMenuIndex), cash);
//	}
//	return 0;
//}
//
#pragma endregion