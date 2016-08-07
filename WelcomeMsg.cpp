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

void WelcomeMsg_Dev()
{
Sleep(1500);
XNotifyUI(L"Welcome! | (Dev)xxHASTERxx v4.9 |");
Sleep(10);
PXOVERLAPPED over = new XOVERLAPPED();
PMESSAGEBOX_RESULT result = new MESSAGEBOX_RESULT();
LPCWSTR text[] = {L"Let the Chaos Rise!!"};

while(XShowMessageBoxUI(0,L"[GTAV: xxHASTERxx v4.9]",L" \n Title Update: 27 \n To Open/Close:(DPAD_LEFT + X)",1,text,NULL,XMB_NOICON,result,over) == ERROR_ACCESS_DENIED)
Sleep(10);
while(!XHasOverlappedIoCompleted(over))
Sleep(10);
}
void WelcomeMsg_Rel()
{
Sleep(1500);
XNotifyUI(L"Welcome! | (Rel)xxHASTERxx v4.9 |");
Sleep(10);
PXOVERLAPPED over = new XOVERLAPPED();
PMESSAGEBOX_RESULT result = new MESSAGEBOX_RESULT();
LPCWSTR text[] = {L"Let the Chaos Rise!!"};

while(XShowMessageBoxUI(0,L"[GTAV: xxHASTERxx v4.9]",L" \n Title Update: 27 \n To Open/Close:(DPAD_LEFT + X)",1,text,NULL,XMB_NOICON,result,over) == ERROR_ACCESS_DENIED)
Sleep(10);
while(!XHasOverlappedIoCompleted(over))
Sleep(10);
}