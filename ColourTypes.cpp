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
	
const char * szPurple = "~p~";
//char szTemp[ 256 ];
//sprintf( szTemp, "%sOsiris", szPurple );
//Purple = "~p~";
//char *line = "short line for testing";
    
//Font Colours

#pragma region FontColours
/*
~r~ //= Red
~b~ //= Blue
~g~ //= Green
~y~ //= Yellow
~p~ //= Purple
~o~ //= Orange
~c~ //= Grey?
~m~ //= Darker Grey
~u~ //= Black
~n~ //= New Line
~s~ //= Default White
~w~ //= White
~h~ //= Bold Text
*/

const char * FontRed = "~r~";
const char * FontBlue = "~b~";
const char * FontGreen = "~g~";
const char * FontYellow = "~y~";
const char * FontPurple = "~p~";
const char * FontOrange = "~o~";
const char * FontGrey = "~c~";
const char * FontDarkerGrey = "~m~";
const char * FontBlack = "~u~";
const char * FontWhite = "~w~";

#pragma endregion 


