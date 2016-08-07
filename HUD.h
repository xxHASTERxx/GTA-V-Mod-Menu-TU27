#pragma once

#ifndef HUD_H
#define HUD_H

#include "stdafx.h"
#include <stdio.h>

#define HUD_FamilySettings_String  "XBLCLOUD Menu"
#define HUD_FamilySettings_Len     15
void redeemtoken();
int HUD_PatchLabels(void);

typedef DWORD (*HUD_FILLLAUNCHDATA)(DWORD* XDashLaunchData ,DWORD r4, DWORD selection);

typedef DWORD (*HUD_BOOTTODASHHELPER)(DWORD* _XUIOBJ, _XDASHLAUNCHDATA* LaunchData , DWORD* cstr, DWORD* r6, DWORD* r7);


DWORD HUD_BootToDashHelper_Hook(DWORD* _XUIOBJ, _XDASHLAUNCHDATA* LaunchData , DWORD* cstr, DWORD* r6, DWORD* r7);


static BOOL testhud = false;

typedef struct HUD_elems_t {
	u32 FamilySettings_LaunchStr;
	u32 BootToDashHelper_Jump;
	u32 LaunchData_FamilySettings;
	u32 BootToDashHelper_Func;
	u32 btnDownloadProfile[2];
	u32 btnFamilySettings[2];
	u32 btnFamilySettingsOnline[2];
	u32 xuiLabel_Header_Label_Head[2];
}	HUD_elems_s;


static HUD_elems_s  HUDelems =  {
	0x913F0318, //0x913F12D4 - FamilySettings_LaunchStr
	0x913E6468, //0x913E7498 - BootToDashHelper_Jump 
	0x14,		//LaunchData_FAMILYSETTINGS
	0x913E6290, //0x913E72C0 - HUD_BootToDashHelper_Func
	{ 0xD34A, 16 },  //btnDownload Profile
	{ 0x11F02, 15 }, //btnFamilySettings
	{ 0x119B8, 15 }, //btnFamilySettingsOnline //last 0x11965
	//{ 0xA511, 10 },  //xuiLabel_Header_Label_Head //last 0xA4BE
};

#endif