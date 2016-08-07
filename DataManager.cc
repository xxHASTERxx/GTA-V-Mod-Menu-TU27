#include "DataManager.h"

unsigned char AuthKey[16] = {
0xCC, 0x75, 0xB9, 0xA7, 
0xAE, 0x83, 0x78, 0x40, 
0x2B, 0x84, 0x5B, 0x3B,
0x28, 0x8D, 0x91, 0x66
};

void DoSha1(void *Data, int Length, void *Out) {
XeCryptSha((const PBYTE)Data, Length, NULL, NULL, NULL, NULL, (const PBYTE)Out, 20);
}

void DoRc4(void *Data, int Length) {
XeCryptRc4((const PBYTE)AuthKey, 16, (const PBYTE)Data, Length);
}

/*
What we will do is send an 8 byte header to tell the client what its getting

4 bytes | UGAY (lol)
4 bytes | length

Then we will send a SHA1 hash of the unencrypted data
Then we will send the encrypted data split up in 1024 byte packets
*/

bool Send(SOCKET Socket, void *Data, int Size) {
int Left = Size;
int Sent = 0;

while (Left > 0) {
int SizeToSend = min(PACKET_SIZE, Left);
int Result = NetDll_send(XNCALLER_SYSAPP, Socket, (const char*)(Sent + (char*)Data), SizeToSend, 0);

if (Result == SOCKET_ERROR) {
return false;
}

Sent += Result;
Left -= Result;
}

return true;
}

bool Recieve(SOCKET Socket, void *Data, int Size) {
int Left = Size;
int Recieved = 0;

while (Left > 0) {
int SizeToRecieve = min(PACKET_SIZE, Left);
int Result = NetDll_recv(XNCALLER_SYSAPP, Socket, (char*)(Recieved + (char*)Data), SizeToRecieve, 0);

if (Result == SOCKET_ERROR) {
return false;
}

Recieved += Result;
Left -= Result;
}

return true;
}

bool SendData(SOCKET ClientSocket, void *Data, int Size, int Id) {
unsigned char Header[8];
unsigned char Digest[20];
int TotalSize = Size + 4;
unsigned char *SendData = (unsigned char*)malloc(TotalSize);

// Format the header
Header[0] = 'U';
Header[1] = 'G';
Header[2] = 'A';
Header[3] = 'Y';

// Setup the size with big endian
Header[4] = (TotalSize & 0xFF000000) >> 24;
Header[5] = (TotalSize & 0xFF0000  ) >> 16;
Header[6] = (TotalSize & 0xFF00    ) >> 8;
Header[7] = (TotalSize & 0xFF      );

// Set up our data with its id
memcpy(SendData    , &Id, 4);
memcpy(SendData + 4, Data, Size);

DoSha1(SendData, TotalSize, Digest);

// Send the header
if (!Send(ClientSocket, Header, 8)) {
//printf("Failed to send header.\n");
return false;
}

// Send the hash
if (!Send(ClientSocket, Digest, 20)) {
//printf("Failed to send hash.\n");
return false;
}

// Encrypt
DoRc4(SendData, TotalSize);

// Send the data
if (!Send(ClientSocket, SendData, TotalSize)) {
free(SendData);
//printf("Failed to send data.\n");
return false;
}

free(SendData);

return true;
}

void *RecieveData(SOCKET ClientSocket, int *Size, int *OutId) {
unsigned char Header[8];
unsigned char Digest[20];
unsigned char CalcDigest[20];
int DataSize;
unsigned char *RecievedData;
unsigned char *Data;

// Get our header
if (!Recieve(ClientSocket, Header, 8)) {
//printf("Failed to recieve header.\n");
return 0;
}

// Check our packet header
if (Header[0] != 'U' || Header[1] != 'G' || Header[2] != 'A' || Header[3] != 'Y') {
//printf("Header had bad UGAY magic.\n");
return 0;
}

// Our data size
DataSize = (Header[4] << 24) | (Header[5] << 16) | (Header[6] << 8) | (Header[7]);

// Allocate
RecievedData = (unsigned char*)malloc(DataSize);
Data =  (unsigned char*)malloc(DataSize - 4);

// Our data hash
if (!Recieve(ClientSocket, Digest, 20)) {
//printf("Failed to recieve data hash.\n");
return 0;
}

// Get our data
if (!Recieve(ClientSocket, RecievedData, DataSize)) {
//printf("Failed to recieve data.\n");
return 0;
}

// Decrypt
DoRc4(RecievedData, DataSize);

// Get our digest
DoSha1(RecievedData, DataSize, CalcDigest);

// Compare them
if (memcmp(Digest, CalcDigest, 20) != 0) {
//printf("Data hash failed.\n");
free(RecievedData);
return 0;
}

*Size = DataSize - 4;

// Get our id
*OutId = *(int*)RecievedData;

// If we succeed our hash check we copy the data over
memcpy(Data, RecievedData + 4, DataSize - 4);

free(RecievedData);

return Data;
}

