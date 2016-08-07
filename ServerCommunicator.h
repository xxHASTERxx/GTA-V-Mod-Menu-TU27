#ifndef __SERVERCOMMUNICATOR_H_
#define __SERVERCOMMUNICATOR_H_

#pragma once
#include <xtl.h>
#include <stdio.h>
#include <xkelib.h>

SOCKET Network_Connect(PBYTE IP, WORD Port);
void Network_Disconnect(SOCKET Sock);
bool Network_Receive(SOCKET Sock, PVOID Data, DWORD Size);
#endif


