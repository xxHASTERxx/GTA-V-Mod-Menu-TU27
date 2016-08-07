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

#pragma region Int,Bools,Floats

char *pexp_carspawn = "";
char *pexp1_carspawn = "";

int scriptsetModel = -1;
int modelHash;
int vehToSpawnHash;
int handle;

float pcoords[3];
bool car = true;
bool car18 = true;
bool mar = false;
bool pwvcheck11 = true;

#pragma endregion

#pragma region Variables

unsigned int get_hash_key_carspawn(char *key)
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

void ShowMessageOnScreen_carspawn(char* Text, ...) 
{
	SET_NOTIFICATION_TEXT_ENTRY("STRING");
	ADD_TEXT_COMPONENT_STRING(Text);
	_SET_NOTIFICATION_MESSAGE_CLAN_TAG("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", false, 2, "~HUD_COLOUR_BLUE~BlackLegion Mod Menu", "~HUD_COLOUR_RADAR_DAMAGE~TU 1.27", 0.5, "___XeX");
	UI::_DRAW_NOTIFICATIONv2(0, 1, 0, 255, 0, 190);
	AUDIO::PLAY_SOUND_FRONTEND(-1, "Hack_Success", "DLC_HEIST_BIOLAB_PREP_HACKING_SOUNDS");
}

#pragma endregion

#pragma region [Particle Effect]


#pragma endregion


#pragma region Car Spawners

#pragma region Give Tracker

int TrackerIndexOnline;
float TrackerPosOnline[3];


int giveselftracker(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = TrackerIndexOnline; //<-- List of players that is grabs
	int Player = GetPlayerHandle(subMenuIndex); //<--- This grabs the name of select player on the list

	GetEntityCoords(Player, TrackerPosOnline);
	int vehicle = GetCarCharIsIn(Player, 0);
	VEHICLE::SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER(vehicle, true);
	return 0;
}

int givetracker1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int player = GetPlayerHandle(subMenuIndex);
	int vehicle = GetCarCharIsIn(player, 0);

	VEHICLE::SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER(vehicle, true);
	DECORATOR::DECOR_REGISTER("Player_Vehicle", 3);
	DECORATOR::DECOR_REGISTER("Veh_Modded_By_Player", 3);
	DECORATOR::DECOR_SET_INT(vehicle, "Player_Vehicle", NETWORK::_0xF8D7AF3B(player));
	DECORATOR::DECOR_SET_INT(vehicle, "Veh_Modded_By_Player", GAMEPLAY::GET_HASH_KEY(PLAYER::GET_PLAYER_NAME(player)));
	DECORATOR::DECOR_GET_BOOL(vehicle, "Player_Vehicle");
	DECORATOR::DECOR_GET_BOOL(vehicle, "Veh_Modded_By_Player");
	return 0;
}

int givetracker(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int player = GetPlayerHandle(subMenuIndex);
	int vehicle = GetCarCharIsIn(player, 0);
	VEHICLE::SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER(vehicle, true);
	return 0;
}

#pragma endregion

#pragma region Spawn The Car

void SpawnTheParticles()
{
if (pwvcheck11)
		{
		if (!unk_0x9ACC6446("scr_rcbarry2"))
		{
        unk_0xCFEA19A9("scr_rcbarry2");
		}
		else 
		{
		float f1;
		f1 = 1.0;
		unk_0x9C720B61( "scr_rcbarry2" );
		unk_0x633F8C48(pexp_carspawn, pcoords[0], pcoords[1], pcoords[2], 0.0f, 0.0f, 0.0f, f1, 0, 0, 0);
		pwvcheck11 = false;
		}
}

pexp_carspawn = "scr_clown_appears";
pwvcheck11 = true;

}

#pragma endregion

#pragma region  [Online]Player CarSpawn

#pragma region Gains DLC

int GainsOsiris_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);

	modelHash = 0x767164D6;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
}


int GainsT20_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 

	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = 0x6322B39A;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
}

int GainsStirling_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = 0xA29D6D10;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
}

int GainsVirgo_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0xE2504942;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
}

int GainsWindsor_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0x5E4327C8;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
}

int GainsCoil_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0xFFFFFFFFA7CE1BC5;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
}

int GainsToro_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0x3FD5AA2F;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
}

int GainsChino_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0x14D69010;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
}

int GainsCoq_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0x2EC385FE;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
}

int GainsVin_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0xFFFFFFFFAF599F01;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
}

int GainsLuxor_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0xB79F589E;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
}

int GainsSwift_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0x4019CB4C;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
}


#pragma endregion 
//done

#pragma region Favorites

int SpawnLazer_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = -1281684762;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnHakuchou_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =1265391242;             
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnBuzzard_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x2F03547B;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

int SpawnTank_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x2EA68690;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnFIB_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x432EA949;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnFIB2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xFFFFFFFF9DC66994;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnPolice_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x71FA16EA;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnPolice3_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =-1627000575;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnUnmarked_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = -1973172295;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0;
}

int SpawnJester2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  = 0xBE0E6126;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}
//Page2
int Spawn6x66_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xB6410173;      
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

int SpawnMonster_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xFFFFFFFFCD93A7DB;    
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnMesa3_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x84F42E51;   
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnPhantom_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x809AA4CB;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

int SpawnBlimp_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xFFFFFFFFF7004C86;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnJumbo_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =105811586;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnCargo_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x15F27762;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

int SpawnDozer_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =1886712733;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

#pragma endregion 
//done

#pragma region Heist Vehicles

int SpawnHydra_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x39D6E83F;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnMule3_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x85A5B471;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnTanker2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x74998082;      
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnCasco_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x3822BDFE;     
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBoxville4_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x1A79847A;   
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnInsurgent_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x9114EADA;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnInsurgent2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x7B7E56F0; 
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0; 
}

int SpawnGBurrito2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x11AA0E14;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnTechnical_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x83051506;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnDinghy3_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x1E5E54EA;      
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSavage_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xFB133A17;    
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnEnduro_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x6882FA73;             
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnGuardian_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x825A9F4C;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnLectro_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x26321E67;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnKumura_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xAE2BFE94;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}
//Page 2
int SpawnKumura2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x187D938D;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnTrash2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xB527915C;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnBarracks3_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x2592B5CF;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnValkyrie_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xA09E15FD;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSlamvan2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x31ADBBFC;    
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnVelum2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x403820E8;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}


#pragma endregion
//done

#pragma region Super Cars


int SpawnAdder_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = 0xB779A091;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0;
}

int SpawnBullet_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = 0x9AE6DDA1;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnCheetah_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = 0xB1D95DA0;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnEntityXF_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0xB2FE5CF9;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnInfernus_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0x18F25AC7;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnTurismoR_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0x185484E1;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0;
}

int SpawnVacca_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); modelHash = 0x142E0DC3;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0;
}

int SpawnVoltic_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0x9F4B77BE;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0;
}

int SpawnZentorno_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);

	modelHash = 0xAC5DF515;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0;
}



#pragma endregion 
//done

#pragma region Sports


int Spawn9F_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x3D8FA25C;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int Spawn9F2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xA8E38B01;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnAlpha_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x2DB8D1AA;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnBanshee_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xC1E908D2;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBuffalo_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xEDD516C6;             
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBuffalo2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x2BEC3CBE;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnCarbonizzare_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x7B8AB45F;             
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnComet_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xC1AE4D16;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnCoquette_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x67BC037;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnElegy_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = 0xDE3D9D22;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnFeltzer_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xDE3D9D22;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnFuroreGT_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xBF1691E; 
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnFusilade_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x1DC0BA53;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}
//Sports Page 2
int SpawnFuto_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x7836CE2F;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnJester_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xB2A716A3;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnKhamelion_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x206D1B68;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnMassacro_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xF77ADE32;      
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnMassacro2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xDA5819A3;      
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnPenumbra_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xE980555; 
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnRapidGT_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x8CB29A14;  
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnRapidGT2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x679450AF;    
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSchwartzer_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xD37B7976;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnSultan_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x39DA2754;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSurano_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x16E478C1;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

#pragma endregion 
//done

#pragma region Coupes


int SpawnCognoscenti_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x13B57D8A;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

int SpawnExemplar_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xFFB15B5E;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

int SpawnF6200_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xDCBCBE48;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnFelon_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xE8A8BDA8;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnFelon2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xFAAD85EE;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnJackal_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xDAC67112;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnOracle_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0x506434F6;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnOracle2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xE18195B2;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSentinel_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x50732C82;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSentinel2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x3412AE2D;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnZion_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xBD1B39C3;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnZion2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xB8E2AE18;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

#pragma endregion 
//done

#pragma region Sedans


int SpawnAsea_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x94204D89;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnAsea2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x9441D8D5;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnAsterope_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x8E9254FB;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnEmperor_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xD7278283;    
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnEmperor2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x8FC3AADC;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnEmperor3_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xB5FCF74E;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnFugitive_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x71CB2FFB;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnGlendale_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x47A6BC1;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnIngot_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xB3206692;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnIntruder_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x34DD8AA1;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnPremier_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x8FB66F9B;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}
//Page 2

int SpawnPrimo_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0xBB6B404F;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnRegina_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xFF22D208;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnRomero_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x2560B2FC;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnSchafter_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xB52B5113;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnStanier_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xA7EDE74D;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnStratum_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x66B4FC45;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnStretch_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x8B13F083;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSuperDiamond_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x42F2ED16;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSurge_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x8F0E3594;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnTailgater_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xC3DDFDCE;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnWarrener_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
	{

	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0x51D83328;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
	}

int SpawnWashington_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x69F06B57;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}



#pragma endregion 
//done

#pragma region Emergency


int SpawnAmbulance_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x45D56ADA;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnFireTruck_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x73920F8E;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnLGuard_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = 469291905;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnPRanger_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x2C33B46E;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnPBike_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xFDEFAEC3;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnPolice2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 2046537925;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnPBus_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = -2007026063;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnRiot_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xB822A1AA;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnPVan_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 456714581;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnSheriff_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =-168332890; 
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0; 
}

int SpawnSheriff2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =1922257928;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnRancherSPP_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xA46462F7;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnEsperantoSPP_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x95F4C618;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

#pragma endregion 
//done

#pragma region Off Road


int SpawnBifta_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xEB298297;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnBlazer_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x8125BCF9;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnBlazer2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xFD231729;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  // lifeguard
	return 0; 
}

int SpawnBlazer3_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xB44F0582;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBodhi_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xAA699BB6;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnDune_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x9CF21E0F;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnDuneloader_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x698521E3;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnInjection_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x432AA566;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnKalahari_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x5852838;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnRancherXL_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x6210CBB; 
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnRebel_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xB802DD46;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnRebel2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x8612B64B;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSandkingSWB_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x3AF8C345;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnSandkingXL_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xFFFFFFFFB9210FD0; 
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0; 
}

int SpawnRancherSnow_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x7341576B;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSpace_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 534258863;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

#pragma endregion 
//done

#pragma region Muscle

int SpawnBlade_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xB820ED5E;             
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnBuccaneer_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xD756460C;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnDominator_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x4CE68AC;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnGauntlet_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x94B395C5;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnHotknife_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash=0x239E390;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0; 
}

int SpawnPhoenix_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x831A21D5;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnPicador_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x59E0FBF3;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnRatLoader_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xD83C13CE;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnRatLoader2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xDCE1D9F7;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSlamVan_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x2B7F9DE3;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnRuiner_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xF26CEFF9;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSabreGT_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x9B909C94;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnVigero_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xCEC6B9B7;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnVoodoo_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x1F3766E3;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}


#pragma endregion 
//done

#pragma region SUVs 


int SpawnBaller_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xCFCA3668;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBaller2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x8852855;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; handle = Handle; RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBeeJayXL_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x32B29A4B;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnCavalcade_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x779F23AA;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnCavalcade2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xD0EB2BE5;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnDubsta_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x462FE277;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnDubsta2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xE882E5F6;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnFQ2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xBC32A33B;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnGranger_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x9628879C;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnGresley_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xA3FC0F4D;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}
//SUV Page 2

int SpawnHabanero_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x34B7390F;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnHuntleySS_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0x1D06D681;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnLandstalker_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x4BA4E8DC;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnMesa_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x36848602;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnMesa2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xD36A4B44;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnPatriot_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xCFCFEB3B;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnRadius_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x9D96B45B;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnRocoto_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x7F5C91F1;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSeminole_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x48CECED3;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSerrano_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x4FB1A214;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}


#pragma endregion 
//done

#pragma region Motorcycles

int SpawnAkuma_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x63ABADE7;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnBagger_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x806B9CC3;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnBati801_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xF9300CC5;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnBati801RR_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xCADD5D2D;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnCarbonRS_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xABB0C0;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnDaemon_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x77934CEE;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnDoubleT_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x9C669788;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnFaggio_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x0350D1AB;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnHexer_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x11F76C14;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}
//Motorcycle Page 2
int SpawnInnovation_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xFFFFFFFFF683EAB1;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnNemesis_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xDA288376;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnPCJ6000_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xC9CEAF06;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnRuffian_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xCABD11E8;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSanchez_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x2EF89E46;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSanchez2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xA960B13E;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSovereign_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0x2C509634;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnThrust_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x6D6F8F43;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnVader_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xF79A00F7;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}



#pragma endregion 
//done

#pragma region Helicopters

int SpawnAnnihilator_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =837858166;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnBuzzard2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x2C75F0DD;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnCargobob_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xFCFCB68B;    
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnCargobob2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x60A7EA1; // medical
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnFrogger_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x2C634FBD;   
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnFrogger2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 1949211328;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnMaverick_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x9D0450CA;    
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnPMav_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = 353883353;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnSkylift_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =1044954915;    
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSwift_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xEBC24DF2;     
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}


#pragma endregion 
//done

#pragma region Planes

int SpawnBesra_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x6CBD1D6D;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

int SpawnCuban8000_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xD9927FE3;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnDuster_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x39D6779E;      
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else{ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");} return 0;  

	return 0; 
}

int SpawnLuxor_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x250B0C5E;    
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnMallard_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x81794C7; 
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnMilJet_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x09D80F93;     
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnMammatus_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x97E55D11;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnShamal_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xB79C1BF5;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnTitan_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x761E2AD3;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnVelum_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x9C429B6A;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnVestra_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x4FF77E37;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}



#pragma endregion
//done

#pragma region Commercial

int SpawnBiff_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x32B91AE8;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnHauler_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x5A82F9AE;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnMule_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x35ED670B;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnPacker_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x21EEE87D;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnStockade_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x6827CF72;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnStockadeSnow_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xF337AB36;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

#pragma endregion 
//done

#pragma region Industrial

int SpawnDHandler_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = 444583674;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnDump_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =-2130482718;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnFlatbed_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x50B0215A;      
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnMixer_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xD138A6BB;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnMixer2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x1C534995;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnRubble_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0x9A5B1DCC;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnTipper_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x02E19879;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnTipper2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xC7824E5E;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

#pragma endregion 
//done

#pragma region Utility

int SpawnAirtug_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x5D0AAC8F;     
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}


int SpawnBison_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xFEFD644F;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBison2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x7B8297C5;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBison3_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x67B3F02; 
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0; 
}

int SpawnBobcatXL_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x3FC5D44; 
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnCaddy_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x44623884;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnCaddy2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xDFF0594C;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnDocktug_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xCB44B1CA;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnFieldmaster_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x843B73DE;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnForklift_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x58E49664;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}
//Page 2
int SpawnRipley_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xCD935EF9;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSadler_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xDC434E51;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnSadler2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x2BC345D1;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnScrap_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x9A9FD3DF;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnTow_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = -1323100960;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnTow2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = -442313018;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnTractor_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x61D6BA8C;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnTractor2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x562A97BD;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnUtility_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x1ED0A534;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnUtility2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x34E6BF6B;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnUtility3_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x7F2153DF;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}


#pragma endregion 
//done

#pragma region Trailers

int SpawnTR2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x7BE032C6;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

int SpawnTR3_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x6A59902D;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnTR4_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x7CAB34D;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnLog_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x782A236D;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}
int SpawnMetal_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xCBB2BE0E;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnRandom_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xA1DA3C91;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}
int SpawnBig_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x8548036D;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnFlat_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xAF62F6B2;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnFame_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x967620BE;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

int SpawnArmyT1_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xA7FF33F5;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnArmyT2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x9E6B14D6;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnArmyT3_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xB8081009;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnBoatT_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x1F3D44B5;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}
int SpawnDockT_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x806EFBEE;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnFreightT_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xD1ABB666;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnTanker_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xD46F4737;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnConstruct_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x2A72BEAB;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}


#pragma endregion 
//done

#pragma region Compacts


int SpawnBlista_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xEB70965F;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnDilettante_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xBC993509;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnIssi_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0xB9CB3B69;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnPanto_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xE644E48;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnPrairie_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xA988D3A2;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnRhapsody_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x322CF98F;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

#pragma endregion 
//done

#pragma region Military

int SpawnBarracks_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xCEEA3F4B;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnBarracks2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x4008EABB;      
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnCrusader_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x132D5A1A;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

#pragma endregion 
//done

#pragma region Service

int SpawnAirportBus_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x4C80EB0E;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBus_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xD577C962;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnDashound_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x84718D34;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnShuttle_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xBE819C63;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnTaxi_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xC703DB5F;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnTourbus_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x73B1C3CB;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnTrashmaster_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x72435A19;             
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}


#pragma endregion 
//done

#pragma region Sports Classics

int SpawnCoquette2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x3C4E2113;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnJB700_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x3EAB5555;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnManana_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x81634188;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnMonroe_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xE62B361B;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnPeyote_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x6D19CCBC;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnPigalle_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x404B6381;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBType_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x06FF6914;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnStinger_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x5C23AF9B;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnStingerGTT_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x82E499FA;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnTornado_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x1BB290BC;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnTornado2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x5B42A5C4;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnTornado3_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x690A4153;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnZType_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x2D3BD401;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}


#pragma endregion 
//done

#pragma region Vans

int SpawnBoxville_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x898ECCEA;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBoxville2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xF21B33BE;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBoxville3_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x7405E08;             
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBurrito_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xAFBB2CA4;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBurrito2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xC9E8FF76;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBurrito3_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x98171BD3;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBurrito4_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x353B561D;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnBurrito5_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x437CF2A; 
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0; 
}

int SpawnCamper_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x6FD95F68;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnGBurrito_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x97FA4F36;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnJourney_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xF8D48E7A;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}
//Page 2
int SpawnMinivan_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xED7EADA4;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnParadise_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x58B3979C;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnPony_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xF8DE29A8;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnWeedVan_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = 943752001;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnRumpo_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x4543B74D;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnRumpo2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x961AFEF7;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSpeedo_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xCFB3870C;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnClown_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =728614474;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSurfer_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x29B0DA97;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSurfer2_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xB1D80E06;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnTacoVan_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x744CA80D;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnYouga_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x3E5F6B8;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

#pragma endregion
//done

#pragma region Bicycles 

int SpawnBMX_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{	
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash=0x43779C54;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnCruiser_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
   	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash=0x1ABA13B5;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnEndurex_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xB67597EC;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnFixter_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xCE23D3BF;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnScorcher_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xF4E1AA15;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnTriCycles_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xE823FB48;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnWhippet_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x4339CD69;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

#pragma endregion 
//done

#pragma region Boats

int SpawnJetmax_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0x33581161;      
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; vehToSpawnHash = modelHash; handle = Handle; RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnMarquis_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0xC1CE1183;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; vehToSpawnHash = modelHash; handle = Handle; RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSeashark_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0xC2974024;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSeasharkLG_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xDB4388E4;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash; 
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSqualo_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x17DF5EC2;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSuntrap_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
    
	int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0xEF2295C9;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnTropic_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x1149422F;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSpeeder_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0x0DC60D2B;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

int SpawnPredator_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);  
	int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = -488123221;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true; 
	vehToSpawnHash = modelHash;
	handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnSub_player(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1); 
	int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x2DFF622F;   
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car18 = true;
	vehToSpawnHash = modelHash;
	handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

#pragma endregion 
//done

#pragma endregion

#pragma region  [Offline]Player CarSpawn

#pragma region Gains DLC

int GainsOsiris_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);

	modelHash = 0x767164D6;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
}


int GainsT20_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 

	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = 0x6322B39A;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
}

int GainsStirling_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = 0xA29D6D10;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
}

int GainsVirgo_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0xE2504942;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
}

int GainsWindsor_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0x5E4327C8;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
}

int GainsCoil_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0xFFFFFFFFA7CE1BC5;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
}

int GainsToro_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0x3FD5AA2F;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
}

int GainsChino_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0x14D69010;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
}

int GainsCoq_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0x2EC385FE;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
}

int GainsVin_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0xFFFFFFFFAF599F01;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
}

int GainsLuxor_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0xB79F589E;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
}

int GainsSwift_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0x4019CB4C;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
}


#pragma endregion 
//done

#pragma region Favorites

int SpawnLazer_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = -1281684762;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnHakuchou_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =1265391242;             
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnBuzzard_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x2F03547B;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

int SpawnTank_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x2EA68690;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnFIB_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x432EA949;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnFIB2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xFFFFFFFF9DC66994;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnPolice_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x71FA16EA;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnPolice3_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =-1627000575;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnUnmarked_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = -1973172295;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0;
}

int SpawnJester2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  = 0xBE0E6126;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}
//Page2
int Spawn6x66_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xB6410173;      
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

int SpawnMonster_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xFFFFFFFFCD93A7DB;    
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnMesa3_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x84F42E51;   
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnPhantom_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x809AA4CB;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

int SpawnBlimp_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xFFFFFFFFF7004C86;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnJumbo_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =105811586;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnCargo_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x15F27762;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

int SpawnDozer_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =1886712733;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

#pragma endregion 
//done

#pragma region Heist Vehicles

int SpawnHydra_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x39D6E83F;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnMule3_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x85A5B471;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnTanker2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x74998082;      
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnCasco_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x3822BDFE;     
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBoxville4_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x1A79847A;   
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnInsurgent_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x9114EADA;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnInsurgent2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x7B7E56F0; 
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0; 
}

int SpawnGBurrito2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x11AA0E14;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnTechnical_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x83051506;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnDinghy3_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x1E5E54EA;      
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSavage_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xFB133A17;    
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnEnduro_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x6882FA73;             
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnGuardian_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x825A9F4C;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnLectro_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x26321E67;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnKumura_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xAE2BFE94;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}
//Page 2
int SpawnKumura2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x187D938D;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnTrash2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xB527915C;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnBarracks3_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x2592B5CF;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnValkyrie_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xA09E15FD;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSlamvan2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x31ADBBFC;    
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnVelum2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x403820E8;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}


#pragma endregion
//done

#pragma region Super Cars


int SpawnAdder_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = 0xB779A091;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0;
}

int SpawnBullet_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = 0x9AE6DDA1;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnCheetah_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = 0xB1D95DA0;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnEntityXF_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0xB2FE5CF9;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnInfernus_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0x18F25AC7;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnTurismoR_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0x185484E1;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0;
}

int SpawnVacca_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); modelHash = 0x142E0DC3;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0;
}

int SpawnVoltic_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 0x9F4B77BE;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0;
}

int SpawnZentorno_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);

	modelHash = 0xAC5DF515;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0;
}



#pragma endregion 
//done

#pragma region Sports


int Spawn9F_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x3D8FA25C;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int Spawn9F2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xA8E38B01;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnAlpha_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x2DB8D1AA;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnBanshee_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xC1E908D2;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBuffalo_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xEDD516C6;             
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBuffalo2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x2BEC3CBE;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnCarbonizzare_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x7B8AB45F;             
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnComet_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xC1AE4D16;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnCoquette_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x67BC037;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnElegy_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = 0xDE3D9D22;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnFeltzer_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xDE3D9D22;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnFuroreGT_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xBF1691E; 
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnFusilade_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x1DC0BA53;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}
//Sports Page 2
int SpawnFuto_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x7836CE2F;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnJester_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xB2A716A3;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnKhamelion_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x206D1B68;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnMassacro_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xF77ADE32;      
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnMassacro2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xDA5819A3;      
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnPenumbra_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xE980555; 
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnRapidGT_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x8CB29A14;  
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnRapidGT2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x679450AF;    
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSchwartzer_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xD37B7976;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnSultan_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x39DA2754;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSurano_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x16E478C1;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

#pragma endregion 
//done

#pragma region Coupes


int SpawnCognoscenti_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x13B57D8A;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

int SpawnExemplar_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xFFB15B5E;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

int SpawnF6200_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xDCBCBE48;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnFelon_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xE8A8BDA8;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnFelon2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xFAAD85EE;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnJackal_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xDAC67112;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnOracle_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0x506434F6;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnOracle2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xE18195B2;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSentinel_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x50732C82;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSentinel2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x3412AE2D;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnZion_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xBD1B39C3;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnZion2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xB8E2AE18;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

#pragma endregion 
//done

#pragma region Sedans

int SpawnAsea_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x94204D89;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnAsea2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x9441D8D5;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnAsterope_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x8E9254FB;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnEmperor_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xD7278283;    
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnEmperor2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x8FC3AADC;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnEmperor3_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xB5FCF74E;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnFugitive_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x71CB2FFB;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnGlendale_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x47A6BC1;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnIngot_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xB3206692;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnIntruder_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x34DD8AA1;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnPremier_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x8FB66F9B;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}
//Page 2

int SpawnPrimo_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0xBB6B404F;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnRegina_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xFF22D208;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnRomero_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x2560B2FC;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnSchafter_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xB52B5113;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnStanier_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xA7EDE74D;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnStratum_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x66B4FC45;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnStretch_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x8B13F083;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSuperDiamond_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x42F2ED16;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSurge_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x8F0E3594;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnTailgater_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xC3DDFDCE;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnWarrener_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
	{

	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0x51D83328;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
	}

int SpawnWashington_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x69F06B57;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}



#pragma endregion 
//done

#pragma region Emergency

int SpawnAmbulance_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x45D56ADA;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnFireTruck_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x73920F8E;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnLGuard_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = 469291905;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnPRanger_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x2C33B46E;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnPBike_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xFDEFAEC3;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnPolice2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 2046537925;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnPBus_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = -2007026063;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnRiot_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xB822A1AA;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnPVan_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 456714581;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnSheriff_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =-168332890; 
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0; 
}

int SpawnSheriff2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =1922257928;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnRancherSPP_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xA46462F7;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnEsperantoSPP_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x95F4C618;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

#pragma endregion 
//done

#pragma region Off Road

int SpawnBifta_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xEB298297;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnBlazer_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x8125BCF9;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnBlazer2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xFD231729;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  // lifeguard
	return 0; 
}

int SpawnBlazer3_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xB44F0582;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBodhi_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xAA699BB6;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnDune_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x9CF21E0F;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnDuneloader_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x698521E3;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnInjection_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x432AA566;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnKalahari_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x5852838;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnRancherXL_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x6210CBB; 
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnRebel_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xB802DD46;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnRebel2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x8612B64B;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSandkingSWB_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x3AF8C345;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnSandkingXL_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xFFFFFFFFB9210FD0; 
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0; 
}

int SpawnRancherSnow_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x7341576B;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSpace_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 534258863;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

#pragma endregion 
//done

#pragma region Muscle

int SpawnBlade_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xB820ED5E;             
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnBuccaneer_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xD756460C;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnDominator_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x4CE68AC;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnGauntlet_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x94B395C5;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnHotknife_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash=0x239E390;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0; 
}

int SpawnPhoenix_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x831A21D5;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnPicador_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x59E0FBF3;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnRatLoader_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xD83C13CE;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnRatLoader2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xDCE1D9F7;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSlamVan_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x2B7F9DE3;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnRuiner_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xF26CEFF9;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSabreGT_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x9B909C94;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnVigero_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xCEC6B9B7;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnVoodoo_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x1F3766E3;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}


#pragma endregion 
//done

#pragma region SUVs 

int SpawnBaller_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xCFCA3668;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBaller2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x8852855;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; ////handle = Handle; RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBeeJayXL_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x32B29A4B;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnCavalcade_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x779F23AA;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnCavalcade2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xD0EB2BE5;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnDubsta_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x462FE277;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnDubsta2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xE882E5F6;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnFQ2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xBC32A33B;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnGranger_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x9628879C;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnGresley_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xA3FC0F4D;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}
//SUV Page 2

int SpawnHabanero_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x34B7390F;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnHuntleySS_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0x1D06D681;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnLandstalker_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x4BA4E8DC;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnMesa_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x36848602;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnMesa2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xD36A4B44;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnPatriot_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xCFCFEB3B;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnRadius_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x9D96B45B;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnRocoto_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x7F5C91F1;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSeminole_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x48CECED3;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSerrano_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x4FB1A214;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}


#pragma endregion 
//done

#pragma region Motorcycles

int SpawnAkuma_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x63ABADE7;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnBagger_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x806B9CC3;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnBati801_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xF9300CC5;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnBati801RR_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xCADD5D2D;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnCarbonRS_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xABB0C0;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnDaemon_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x77934CEE;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnDoubleT_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x9C669788;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnFaggio_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x0350D1AB;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnHexer_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x11F76C14;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}
//Motorcycle Page 2
int SpawnInnovation_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xFFFFFFFFF683EAB1;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnNemesis_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xDA288376;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
//	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnPCJ6000_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xC9CEAF06;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnRuffian_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xCABD11E8;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSanchez_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x2EF89E46;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSanchez2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xA960B13E;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSovereign_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0x2C509634;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnThrust_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x6D6F8F43;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnVader_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xF79A00F7;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}



#pragma endregion 
//done

#pragma region Helicopters

int SpawnAnnihilator_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =837858166;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnBuzzard2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x2C75F0DD;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnCargobob_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xFCFCB68B;    
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnCargobob2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x60A7EA1; // medical
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnFrogger_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x2C634FBD;   
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnFrogger2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = 1949211328;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnMaverick_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x9D0450CA;    
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnPMav_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = 353883353;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnSkylift_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =1044954915;    
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSwift_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xEBC24DF2;     
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}


#pragma endregion 
//done

#pragma region Planes

int SpawnBesra_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x6CBD1D6D;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

int SpawnCuban8000_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xD9927FE3;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnDuster_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x39D6779E;      
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else{ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");} return 0;  

	return 0; 
}

int SpawnLuxor_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x250B0C5E;    
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnMallard_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x81794C7; 
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnMilJet_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x09D80F93;     
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnMammatus_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x97E55D11;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnShamal_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xB79C1BF5;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnTitan_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x761E2AD3;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnVelum_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x9C429B6A;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnVestra_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x4FF77E37;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}



#pragma endregion
//done

#pragma region Commercial

int SpawnBiff_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x32B91AE8;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnHauler_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x5A82F9AE;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnMule_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x35ED670B;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnPacker_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x21EEE87D;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnStockade_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x6827CF72;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnStockadeSnow_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xF337AB36;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

#pragma endregion 
//done

#pragma region Industrial

int SpawnDHandler_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = 444583674;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnDump_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =-2130482718;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnFlatbed_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x50B0215A;      
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnMixer_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xD138A6BB;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnMixer2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x1C534995;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnRubble_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0x9A5B1DCC;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnTipper_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x02E19879;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnTipper2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xC7824E5E;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

#pragma endregion 
//done

#pragma region Utility

int SpawnAirtug_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x5D0AAC8F;     
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}


int SpawnBison_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xFEFD644F;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBison2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x7B8297C5;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBison3_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x67B3F02; 
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0; 
}

int SpawnBobcatXL_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x3FC5D44; 
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnCaddy_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x44623884;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnCaddy2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xDFF0594C;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnDocktug_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xCB44B1CA;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnFieldmaster_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x843B73DE;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnForklift_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x58E49664;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}
//Page 2
int SpawnRipley_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xCD935EF9;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSadler_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xDC434E51;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnSadler2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x2BC345D1;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnScrap_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x9A9FD3DF;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnTow_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = -1323100960;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnTow2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash = -442313018;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnTractor_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x61D6BA8C;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnTractor2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x562A97BD;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnUtility_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x1ED0A534;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnUtility2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x34E6BF6B;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnUtility3_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x7F2153DF;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}


#pragma endregion 
//done

#pragma region Trailers

int SpawnTR2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x7BE032C6;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

int SpawnTR3_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x6A59902D;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnTR4_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x7CAB34D;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnLog_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x782A236D;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}
int SpawnMetal_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xCBB2BE0E;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnRandom_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xA1DA3C91;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}
int SpawnBig_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x8548036D;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnFlat_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xAF62F6B2;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnFame_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x967620BE;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

int SpawnArmyT1_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xA7FF33F5;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnArmyT2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x9E6B14D6;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnArmyT3_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xB8081009;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnBoatT_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x1F3D44B5;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}
int SpawnDockT_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x806EFBEE;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnFreightT_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xD1ABB666;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnTanker_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xD46F4737;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnConstruct_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x2A72BEAB;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}


#pragma endregion 
//done

#pragma region Compacts

int SpawnBlista_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xEB70965F;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnDilettante_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xBC993509;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnIssi_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0xB9CB3B69;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnPanto_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xE644E48;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0; 
}

int SpawnPrairie_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xA988D3A2;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnRhapsody_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x322CF98F;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

#pragma endregion 
//done

#pragma region Military

int SpawnBarracks_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xCEEA3F4B;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnBarracks2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x4008EABB;      
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnCrusader_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x132D5A1A;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

#pragma endregion 
//done

#pragma region Service

int SpawnAirportBus_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x4C80EB0E;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBus_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xD577C962;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnDashound_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x84718D34;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnShuttle_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xBE819C63;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnTaxi_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xC703DB5F;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnTourbus_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x73B1C3CB;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnTrashmaster_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x72435A19;             
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}


#pragma endregion 
//done

#pragma region Sports Classics

int SpawnCoquette2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x3C4E2113;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnJB700_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x3EAB5555;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnManana_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x81634188;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnMonroe_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xE62B361B;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnPeyote_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x6D19CCBC;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnPigalle_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x404B6381;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBType_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x06FF6914;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnStinger_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x5C23AF9B;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnStingerGTT_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x82E499FA;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnTornado_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x1BB290BC;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnTornado2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x5B42A5C4;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnTornado3_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x690A4153;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnZType_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x2D3BD401;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}


#pragma endregion 
//done

#pragma region Vans

int SpawnBoxville_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x898ECCEA;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBoxville2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xF21B33BE;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBoxville3_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x7405E08;             
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBurrito_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xAFBB2CA4;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBurrito2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xC9E8FF76;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBurrito3_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x98171BD3;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnBurrito4_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x353B561D;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnBurrito5_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x437CF2A; 
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;
	return 0; 
}

int SpawnCamper_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x6FD95F68;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnGBurrito_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x97FA4F36;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnJourney_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xF8D48E7A;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}
//Page 2
int SpawnMinivan_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xED7EADA4;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnParadise_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x58B3979C;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnPony_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xF8DE29A8;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0;  
	return 0; 
}

int SpawnWeedVan_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = 943752001;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnRumpo_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x4543B74D;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnRumpo2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x961AFEF7;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSpeedo_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xCFB3870C;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnClown_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =728614474;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSurfer_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x29B0DA97;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnSurfer2_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xB1D80E06;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnTacoVan_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x744CA80D;           
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

int SpawnYouga_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x3E5F6B8;            
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;  
	return 0; 
}

#pragma endregion
//done

#pragma region Bicycles 

int SpawnBMX_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{	
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash=0x43779C54;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnCruiser_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
   	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash=0x1ABA13B5;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnEndurex_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xB67597EC;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnFixter_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xCE23D3BF;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnScorcher_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xF4E1AA15;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnTriCycles_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0xE823FB48;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnWhippet_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x4339CD69;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

#pragma endregion 
//done

#pragma region Boats

int SpawnJetmax_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0x33581161;      
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; vehToSpawnHash = modelHash; ////handle = Handle; RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnMarquis_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0xC1CE1183;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; vehToSpawnHash = modelHash; ////handle = Handle; RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSeashark_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0xC2974024;       
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSeasharkLG_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0xDB4388E4;        
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash; 
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSqualo_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x17DF5EC2;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSuntrap_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
    
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  	
	//int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0xEF2295C9;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnTropic_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash  =0x1149422F;          
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	}
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

int SpawnSpeeder_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); modelHash  =0x0DC60D2B;         
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	}
	return 0; 
	return 0; 
}

int SpawnPredator_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);  
	//int Handle = GetPlayerHandle(subMenuIndex); 
	modelHash = -488123221;
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true; 
	vehToSpawnHash = modelHash;
	//handle = Handle;
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0;
	return 0;
}

int SpawnSub_self(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1); 
	//int Handle = GetPlayerHandle(subMenuIndex);
	modelHash  =0x2DFF622F;   
	if(IS_MODEL_VALID(modelHash) && STREAMING::IS_MODEL_A_VEHICLE(modelHash))
	{
	car = true;
	vehToSpawnHash = modelHash;
	////handle = Handle; 
	RequestModel(modelHash);
	} 
	else
	{
	ShowMessageOnScreen_carspawn("~r~Model Isn't Valid");
	} 
	return 0; 
	return 0; 
}

#pragma endregion 
//done

#pragma endregion


#pragma endregion