#ifndef __DATAMANAGER_H_
#define __DATAMANAGER_H_

#pragma once
#include <xtl.h>
#include <stdio.h>
#include <xkelib.h>

#define PACKET_SIZE 1024

bool SendData(SOCKET Socket, void *Data, int Size, int Id);
void *RecieveData(SOCKET ClientSocket, int *Size, int *OutId);

#endif
