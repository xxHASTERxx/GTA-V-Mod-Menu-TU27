#include "ServerCommunicator.h"
#include "DataManager.h"



// Methods
SOCKET Network_Connect(PBYTE IP, WORD Port)
{
	// Create our other variable
	DWORD SocketError;
	SOCKET Sock;
	XNetStartupParams xnsp;
	WSADATA WsaData;
	BOOL SockOpt = TRUE;
	DWORD sendRecvSize = 1024;
	sockaddr_in httpServerAdd;

	// Configure server address
	httpServerAdd.sin_addr.S_un.S_un_b.s_b3 = IP[2];
	httpServerAdd.sin_addr.S_un.S_un_b.s_b1 = IP[0];
	httpServerAdd.sin_port = htons(Port);
	httpServerAdd.sin_addr.S_un.S_un_b.s_b4 = IP[3];
	httpServerAdd.sin_addr.S_un.S_un_b.s_b2 = IP[1];
	httpServerAdd.sin_family = AF_INET;

	// Nullify our xnsp variable
	ZeroMemory(&xnsp, sizeof(xnsp));

	// Configure our xnsp variable
	xnsp.cfgSizeOfStruct = sizeof(XNetStartupParams);
	xnsp.cfgFlags = XNET_STARTUP_BYPASS_SECURITY;

	// Safely startup XNet
	if ((SocketError = NetDll_XNetStartup(XNCALLER_SYSAPP, &xnsp)) != S_OK)
		return INVALID_SOCKET;

	// Safely startup WSA
	if ((SocketError = NetDll_WSAStartupEx(XNCALLER_SYSAPP, MAKEWORD(2, 2), &WsaData, 2)) != S_OK)
		return INVALID_SOCKET;

	// Safely create socket
	Sock = NetDll_socket(XNCALLER_SYSAPP, AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// Disable network encryption
	if (NetDll_setsockopt(XNCALLER_SYSAPP, Sock, SOL_SOCKET, 0x5801, (PCSTR)&SockOpt, 4) != S_OK)
		return INVALID_SOCKET;

	// Configure socket send/recv size
	NetDll_setsockopt(XNCALLER_SYSAPP, Sock, SOL_SOCKET, SO_SNDBUF, (PCSTR)&sendRecvSize, 4);
	NetDll_setsockopt(XNCALLER_SYSAPP, Sock, SOL_SOCKET, SO_RCVBUF, (PCSTR)&sendRecvSize, 4);

	// Create connection timeout
	struct timeval tv;
	tv.tv_sec = 15;
	tv.tv_usec = 0;
	setsockopt(Sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(struct timeval));

	// Safely connect
	if (NetDll_connect(XNCALLER_SYSAPP, Sock, (struct sockaddr*)&httpServerAdd, sizeof(httpServerAdd)) == SOCKET_ERROR)
		return INVALID_SOCKET;

	// Return our socket
	return Sock;
}
void	Network_Disconnect(SOCKET Sock)
{
	NetDll_closesocket(XNCALLER_SYSAPP, Sock);
	Sock = NULL;
}
bool	Network_Receive(SOCKET Sock, PVOID Data, DWORD Size)
{
	DWORD Left = Size;
	DWORD Received = 0;
	DWORD Size2Receive = 0;
	DWORD Result = 0;

	while (Left > 0)
	{
		Size2Receive = min(0x400, Left);
		Result = NetDll_recv(XNCALLER_SYSAPP, Sock, (char*)(Received + (char*)Data), Size2Receive, 0);

		if (Result == SOCKET_ERROR)
			return false;

		Received += Result;
		Left -= Result;
	}

	return true;


}

