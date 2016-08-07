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

#pragma region Ints,Bools,Floats

bool drawT = false;

float xPos = 0.50f;
float yPos = 0.50f;
float xWidth = 0.10f;
float yLength = 0.10f;

enum MenuButtons
{
 Menu_Button_Back = 0xBF,
 Menu_Button_Y = 0xC0,
 Menu_Button_A = 0xC1, 
 Menu_Button_X = 0xC2,
 Menu_Button_B = 0xC3, 
 Menu_Button_LB = 0xC4, 
 Menu_Button_RB = 0xC5,
 Menu_Button_LT = 0xC6, 
 Menu_Button_RT = 0xC7,
 Menu_Button_LS = 0xC8,
 Menu_Button_RS = 0xC9,
 Menu_Dpad_Up = 0xCA,
 Menu_Dpad_Down = 0xCB,
 Menu_Dpad_Left = 0xCC,
 Menu_Dpad_Right = 0xCD,
};

#pragma endregion

#pragma region Menu Options


void DrawToolMain()
{
        CONTROLS::SET_INPUT_EXCLUSIVE(2, Menu_Button_X);
        CONTROLS::SET_INPUT_EXCLUSIVE(2, Menu_Button_B);
        CONTROLS::SET_INPUT_EXCLUSIVE(2, Menu_Button_LB);
        CONTROLS::SET_INPUT_EXCLUSIVE(2, Menu_Button_RB);
        CONTROLS::SET_INPUT_EXCLUSIVE(2, Menu_Dpad_Left);
        CONTROLS::SET_INPUT_EXCLUSIVE(2, Menu_Dpad_Right);
        CONTROLS:: SET_INPUT_EXCLUSIVE(2, Menu_Dpad_Up);
        CONTROLS:: SET_INPUT_EXCLUSIVE(2, Menu_Dpad_Down);
        CONTROLS:: SET_INPUT_EXCLUSIVE(2, Menu_Button_RS);
 
        draw_rect(xPos, yPos, xWidth, yLength, 0, 225, 225, 255);
 
		if(is_control_pressed(2, Menu_Button_X))
		{
				xPos -= 0.001f;;
				draw_rect(xPos, yPos, xWidth, yLength, 0, 225, 225, 255);
		}
        if(is_control_pressed(2, Menu_Button_B))
		{
                xPos += 0.001f;
                draw_rect(xPos, yPos, xWidth, yLength, 0, 225, 225, 255);
        }
        if(is_control_pressed(2, Menu_Button_LB))
		{
                yPos -= 0.001f;
                draw_rect(xPos, yPos, xWidth, yLength, 0, 225, 225, 255);
        }
        if(is_control_pressed(2, Menu_Button_RB))
		{
                yPos += 0.001f;
                draw_rect(xPos, yPos, xWidth, yLength, 0, 225, 225, 255);
        }
 
        if(is_control_pressed(2, Menu_Dpad_Right))
		{
                xWidth += 0.001f;
                draw_rect(xPos, yPos, xWidth, yLength, 0, 225, 225, 255);
        }
        if(is_control_pressed(2, Menu_Dpad_Left))
		{
                xWidth -= 0.001f;
                draw_rect(xPos, yPos, xWidth, yLength, 0, 225, 225, 255);
        }
        if(is_control_pressed(2, Menu_Dpad_Up))
		{
                yLength += 0.001f;
                draw_rect(xPos, yPos, xWidth, yLength,0, 225, 225, 255);
        }
        if(is_control_pressed(2, Menu_Dpad_Down))
		{
                yLength -= 0.001f;
                draw_rect(xPos, yPos, xWidth, yLength, 0, 225, 225, 255);
        }
        if(is_control_just_pressed(2, Menu_Button_RS))
		{
                drawT = false;
        }

		PrintToScreen("X:", 0.20000000, 0.86000000, 240, 15, 20, 255, 0.80000000, 0.80000000, 0, 6);
        PrintToScreenFloat(xPos, 0.23000000, 0.86000000, 240, 15, 20, 255, 0.80000000, 0.80000000, 0, 6);
   
        PrintToScreen("Y:", 0.340000000, 0.86000000, 240, 15, 20, 255, 0.80000000, 0.80000000, 0, 6);
        PrintToScreenFloat(yPos, 0.37000000, 0.86000000, 240, 15, 20, 255, 0.80000000, 0.80000000, 0, 6);
   
        PrintToScreen("X2:", 0.470000000, 0.86000000, 240, 15, 20, 255, 0.80000000, 0.80000000, 0, 6);
        PrintToScreenFloat(xWidth, 0.5000000, 0.86000000, 240, 15, 20, 255, 0.80000000, 0.80000000, 0, 6);
 
        PrintToScreen("Y2:", 0.620000000, 0.86000000, 240, 15, 20, 255, 0.80000000, 0.80000000, 0, 6);
        PrintToScreenFloat(yLength, 0.6500000, 0.86000000, 240, 15, 20, 255, 0.80000000, 0.80000000, 0, 6);
}

int DrawTool(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParametersconst)
{
        if(!drawT)
		{
        //ShowMessageOnScreen_m("~p~ Draw Tool: ~b~ ON");
        drawT = true;
        }
        else if(drawT)
		{
        //ShowMessageOnScreen_m("~~p~ Draw Tool: ~r~ OFF");
        drawT = false;
        }
  return 0;
}


#pragma endregion