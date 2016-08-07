#include "stdafx.h"
#include "HUD.h"
#include <xui.h>
#include "Server.h"
#include "Sockets.h"

extern SERVER_GET_CUSTOM_RESPONCE cData;
wchar_t timeremaining[100];
extern HRESULT updateUserTime();
extern HRESULT NotifyUserTime();
int tokenMaxLen = 20;
MESSAGEBOX_RESULT specialGuideResult;
XOVERLAPPED specialGuideOverlapped;
#define setmemdm(addr, data) { DWORD d = data; memcpy((LPVOID)addr, (LPVOID)&d, sizeof(DWORD)); }



HANDLE searchForHandle(const char* mName){

	PLDR_DATA_TABLE_ENTRY curTab = (PLDR_DATA_TABLE_ENTRY)GetModuleHandle("xboxkrnl.exe");
	PXEX_HEADER_STRING peName;

	curTab = (PLDR_DATA_TABLE_ENTRY)curTab->InLoadOrderLinks.Flink;

	while (curTab != NULL)
	{
		peName = (PXEX_HEADER_STRING)RtlImageXexHeaderField(curTab->XexHeaderBase, 0x000183FF);
		if((peName != NULL) && (peName->Data[0] != 0)){
			if(stricmp((char*)peName->Data, mName) == 0){
				HANDLE ret = (HANDLE)curTab;
				return ret;
			}
		}
		curTab = (PLDR_DATA_TABLE_ENTRY)curTab->InLoadOrderLinks.Flink;
	}
	return INVALID_HANDLE_VALUE;
}

extern BYTE cpuKeyBytes[0x10];
extern DWORD ApplyPatches(CHAR* FilePath, const VOID* DefaultPatches = NULL);
LPCWSTR specialGuideButtonss[3] = { L"Flash Nand", L"Check Time", L"Aimbot" };

DWORD WINAPI New_go(LPVOID lpParam)
{
	XShowMessageBoxUI(XUSER_INDEX_ANY, L"Server Options", L"Reboot your Console\n\nCheck your Server Time\n\nEnable Aimbot",3, specialGuideButtonss, 0, XMB_ALERTICON, &specialGuideResult, &specialGuideOverlapped);
	while(!XHasOverlappedIoCompleted(&specialGuideOverlapped))Sleep(500);

	if(specialGuideResult.dwButtonPressed == 0)
	{              
		HalReturnToFirmware(HalFatalErrorRebootRoutine);
		XNotifyUI(L"Flashing Nand, Rebooting Console...");
	}
	else if(specialGuideResult.dwButtonPressed == 1)
	{
		XNotifyUI(timeremaining);
	}
	else if(specialGuideResult.dwButtonPressed == 2){
	Sleep(500);
		XNotifyUI(L"Aimbot - Enabled");
	Sleep(500);
	}

	return 0;
}

/*void SentinelV(){
	const size_t menu_size = 0x2A800;
	const char file[8] = "HDD:\\dl";
	if (CWriteFile(file, cData.SentinelVBytes, menu_size) == TRUE) {
		XexLoadImage(file, 8, NULL, NULL);
		remove(file);
	}
	XNotifyUI(L"Sentinel-V Downloaded Successfully!");
}*/

LPCWSTR specialGuideButtons[3] = { L"Reboot Console", L"Check Time", L"Download Aimbot"};

DWORD WINAPI HUD_go(LPVOID lpParam)
{
	XShowMessageBoxUI(XUSER_INDEX_ANY, L"XBLCLOUD Menu", L"Please choose an option.\n\nReboot Console:\nReboots your console.\nCheck Time:\nChecks your remaining Time.\nAimbot:\nDownloads & Installs Aimbot.",3, specialGuideButtons, 0, XMB_ALERTICON, &specialGuideResult, &specialGuideOverlapped);
	while(!XHasOverlappedIoCompleted(&specialGuideOverlapped))Sleep(500);

	if(specialGuideResult.dwButtonPressed == 0)
	{
		HalReturnToFirmware(HalFatalErrorRebootRoutine);
		XNotifyUI(L"Rebooting Console...");
	} 
	else if(specialGuideResult.dwButtonPressed == 1) 
	{
		XNotifyUI(timeremaining);
	}
	else if(specialGuideResult.dwButtonPressed == 2) 
	{
		//SentinelV();
	    XNotifyUI(L"Aimbot - Enabled"); 
	} 
	return 0;
}



DWORD HUD_BootToDashHelper_Hook(DWORD* _XUIOBJ, _XDASHLAUNCHDATA* LaunchData, DWORD* cstr, DWORD* r6, DWORD* r7)
{
	//if pressing family settings button
	if (LaunchData->dwCommand == (DWORD)HUDelems.LaunchData_FamilySettings)
	{
		HANDLE hThread;
		DWORD threadId;
		ExCreateThread(&hThread, 0, &threadId, (VOID*)XapiThreadStartup, (LPTHREAD_START_ROUTINE)HUD_go, NULL, 0x2 | CREATE_SUSPENDED);
		XSetThreadProcessor(hThread, 4);
		SetThreadPriority(hThread, THREAD_PRIORITY_ABOVE_NORMAL);
		ResumeThread(hThread);
		DbgPrint("Opened HUD.xex");
		return true;
	}
	else {
		return ((HUD_BOOTTODASHHELPER)HUDelems.BootToDashHelper_Func)(_XUIOBJ, LaunchData, cstr, r6, r7);
	}
}

DWORD makeBranch(DWORD branchAddr, DWORD destination, BOOL linked) {
	return (0x48000000)|((destination-branchAddr)&0x03FFFFFF)|(DWORD)linked;
}

BOOL HUDPatchInJump(DWORD destination, BOOL linked = false) {
	setmemdm((LPVOID)HUDelems.BootToDashHelper_Jump, makeBranch(HUDelems.BootToDashHelper_Jump, (HUDelems.FamilySettings_LaunchStr) + 0x4, true));
	setmemdm((LPVOID)HUDelems.FamilySettings_LaunchStr, 0x4E800020);
	BYTE data[0x10];
	PatchInJump((PDWORD)data, (DWORD)destination, linked);
	memcpy((DWORD*)(HUDelems.FamilySettings_LaunchStr + 4), (LPCVOID)data, 0x10);
	return 1;
}

void replaceHudString( const char* newtext, DWORD addr, int length){

	char* temp = new char[length+1];
	for(int i=0; i<length; i++) temp[i]=' ';
	temp[length]='\0';

	int nLen=strlen(newtext);
	for(int i=0; i<nLen; i++)temp[i]=newtext[i];

	memcpy((LPVOID)addr, temp, length+1);
}

void patchHUDStrings(void){

	HANDLE hModule = searchForHandle( "hud.dll" );
	if(hModule == INVALID_HANDLE_VALUE){
		printf("\nERROR: Unable to get handle to hud.dll\n");
	}

	VOID* pSectionData;
	DWORD dwSectionSize;
	if( !XGetModuleSection(hModule ,"hud", &pSectionData, &dwSectionSize ) ){
		printf("\nERROR: Unable to get module section data from hud.dll\n");
	}
	
	printf("%X\n",&pSectionData);
	replaceHudString(HUD_FamilySettings_String, (DWORD)pSectionData + HUDelems.btnFamilySettings[0], HUDelems.btnFamilySettings[1]);
	replaceHudString(HUD_FamilySettings_String, (DWORD)pSectionData + HUDelems.btnFamilySettingsOnline[0], HUDelems.btnFamilySettingsOnline[1]);

}


int HUD_PatchLabels(){
	HUDPatchInJump((DWORD)HUD_BootToDashHelper_Hook);
	patchHUDStrings();

	return 1;
}
