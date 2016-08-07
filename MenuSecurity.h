#ifndef _MENUSECURITY_H_
#define _MENUSECURITY_H_

#pragma once
#include <xtl.h>
#include <xkelib.h>

void GetServerIp(PBYTE pbOutIp);
void GetCPUDec();
void SecondaryDecryptTrampoline(PBYTE pbInData);
void ServerConnectionInit();
void MenuSecurityInit();
void AutorisationInit();// penis sweg

#endif
