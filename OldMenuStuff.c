#include <xtl.h>
#include <xkelib.h>
#include <xbdm.h>

#include "Tools.h"
#include "GTAVMenu.h"
#include "Input.h"
#include "GTAVNatives.h"

extern "C" const TCHAR szModuleName[] = TEXT("GTAVMenu.dll");

GTAVMenu *mainMenu;
GTAVMenu *playerOptionsMenu;
GTAVMenu *vehicleOptionMenu;
GTAVMenu *weaponOptionsMenu;
GTAVMenu *onlinePlayers;
GTAVMenu *onlinePlayersSubMenu;
GTAVMenu *CarSpawnerMenu;
GTAVMenu *OnlinePlayerVehicleOptions;
GTAVMenu *OnlinePlayerTeleport;
Input *menuInputHandler;

bool inputButtonsPressed = false;
bool enableMenu = false;

bool playerInvincibilityActive = false;
bool buttonpressed = false;
bool rainbow = false;
bool invisible = false;
bool superjump = false;
bool superruncheck = false;
int myplayerped;
int rainbowcar;
int invisiblecar;

float Vec3DistanceSq(const float *p1, const float *p2)
{
	return ((p2[0] - p1[0]) * (p2[0] - p1[0]) + 
		((p2[2] - p1[2]) * (p2[2] - p1[2]) + 
		((p2[1] - p1[1]) * (p2[1] - p1[1]))));
}

float Distance(float p11, float p12, float p13, float p21, float p22, float p23)
{
	float p1[] = {p11, p12, p13},
		p2[] = {p21, p22, p23};
	return sqrt(Vec3DistanceSq(p1, p2));
}

float Distance(float *p1, float *p2)
{
	return sqrt(Vec3DistanceSq(p1, p2));
}

bool isInDistance(int Handle)
{
	float Pos[2][3],
	Dist;
	GetEntityCoords(PlayerPedId(), &Pos[0]);
	GetEntityCoords(Handle, &Pos[1]);
	Dist = Distance(Pos[0], Pos[1]);
	printf("Distance between you and the player is %f\n", Dist);
	return (Dist <= 880.0f && !is_ped_getting_into_a_vehicle(Handle));
}

void TeleportToClient(int Client)
{
	float* Location = (float *)(*(int *)((*(int *)(0x83BA3400 + 0x78) + 0x10 + (Client * 0x900)) + 0xF8) + 0x70);
	printf("Client %i's pos = { %f, %f, %f } \n", Client, Location[0], Location[1], Location[2]);
	memcpy((PVOID)(*(int *)(*(int *)((*(int *)(0x83BA3400 + 0x78) + 0x10 + (0 * 0x900)) + 0xF8) + 0x1C) + 0x40), Location, 0xC);
}

int ToggleInvincibility(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	playerInvincibilityActive = !playerInvincibilityActive;

	printf("Invincibility = %s\n", playerInvincibilityActive ? "true" : "false");

	SetPlayerInvincible(PlayerId(), playerInvincibilityActive);

	return 0;
}

int irand(int min, int max, int Add = 0)
{
	srand(GetTickCount() + Add);
	return min + (rand() % (int)(max - min + 1));
}

void rainbow_car()
{
	if (DoesEntityExist(rainbowcar) && IsEntityVehicle(rainbowcar)) {
		PaintCar(rainbowcar, irand(0, 255, 200), irand(0, 255, -40));
		PaintCarExtra(rainbowcar, irand(0, 255, 30), irand(0, 255, 400));
		printf("car exists and loop is intact");
	}
}


int ToggleRainbow(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	printf("Rainbow Car = %s\n", rainbowcar ? "true" : "false");
	rainbowcar = GetCarCharIsIn(PlayerPedId(), PlayerId());
    Sleep(500);
	if (DoesEntityExist(rainbowcar) && IsEntityVehicle(rainbowcar))
	{
		printf("Attempted to paint vehicle");
		rainbow = !rainbow;//toggle
	}
	else
	{
		printf("Failed, Entity may not exist or may not be a vehicle\n");
	}
	return 0;
}

int ToggleInvisibleCar(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	printf("Invisible Car = %s\n", invisiblecar ? "true" : "false");
	int car;
	car = GetCarCharIsIn(PlayerPedId(), PlayerId());
    Sleep(500);
	if (DoesEntityExist(car) && IsEntityVehicle(car))
	{
		printf("IsEntityVehicle == true, ");
		if (!invisiblecar)
		{
		CarVisibleDamage(car, false);
		set_entity_can_be_damaged(car, false);
		invisiblecar = true;
		printf("On\n");
		}
		else if (invisiblecar)
		{
		CarVisibleDamage(car, true);
		set_entity_can_be_damaged(car, true);
		invisiblecar = true;
		printf("Off\n");
		}
		printf("Car is %svisible\n", invisible ? "" : "in");
		invisible = !invisible;
		//set_entity_coords(car, 0, 0, 0, 0, 0, 0, 1);
	}
	else
	{
		printf("Failed, Entity may not exist or may not be a vehicle\n");
	}
	return 0;
}

int PaintOnlinePlayersCar(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	// subMenuIndex is the index of the player you selected in the game, or it should be at least
	int subMenuIndex = selectedMenuIndexes->operator[](1);

	printf("PaintOnlinePlayersCar, OnPlayerSelected subMenuIndex = %d\n", subMenuIndex);
	int Handle = GetPlayerHandle(subMenuIndex);
	printf("PlayerHandle = %i, ", Handle);
	int vehicle;
	int netid;
	if (isInDistance(Handle))
	{
		vehicle = GetCarCharIsIn2(Handle, subMenuIndex);
		printf("Got Vehicle Handle %i\n", vehicle);
		if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle))
		{
			printf("Car exists\n");
			netid = veh_to_net(vehicle);
			printf("veh_to_net\n");
			if (network_does_network_id_exist(netid))
			{
				printf("Network ID for vehicle does exist\n");
				network_request_control_of_network_id(netid);
				while (!network_has_control_of_network_id(netid))
				if (network_has_control_of_network_id(netid))
				{
				printf("Got full control of network ID %i\n", netid);
				}
			}
			printf("Vehicle Exists\n");
			network_request_control_of_entity(vehicle);
			while ((!network_has_control_of_entity(vehicle))){network_request_control_of_entity(vehicle);}
			printf("Attempted to grab control of vehicle\n");
			if (network_has_control_of_entity(vehicle))
			{
				printf("Got control\n");
				PaintCar(vehicle, irand(0, 255, 200), irand(0, 255, -40));
				PaintCarExtra(vehicle, irand(0, 255, 30), irand(0, 255, 400));
				printf("Painted car\n");
			}
		}
	}
	else printf("Player is out of range\n");
	return 0;
}

int ExplodeOnlinePlayerVehicle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	// subMenuIndex is the index of the player you selected in the game, or it should be at least
	int subMenuIndex = selectedMenuIndexes->operator[](1);

	printf("ExplodeOnlinePlayerVehicleOnPlayerSelected subMenuIndex = %d\n", subMenuIndex);
	int Handle = GetPlayerHandle(subMenuIndex);
	printf("PlayerHandle = %i, ", Handle);
	int vehicle;
	int hash;
	if (isInDistance(Handle))
	{
		vehicle = GetCarCharIsIn(Handle, subMenuIndex);
		printf("Got Vehicle Handle %i\n", vehicle);
		if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle))
		{
			printf("Vehicle Exists\n");
			network_request_control_of_entity(vehicle);
			while ((!network_has_control_of_entity(vehicle))){network_request_control_of_entity(vehicle);}
			printf("Attempted to grab control of vehicle\n");
			if (network_has_control_of_entity(vehicle))
			{
				printf("Got control\n");
				//delete_entity(vehicle);
				//PopCarTyre(vehicle, 1);
				//PopCarTyre(vehicle, 2);
				//PopCarTyre(vehicle, 3);
				set_vehicle_petrol_tank_health(vehicle, -1);
				//apply_force_to_entity(vehicle, true, 0, 0, 150, 0, 0, 0, true, true, true, true);
				printf("Blew car up\n");
			}
		}
	}
	else 
		printf("Player is out of range\n");
	return 0;
}

int SendPlayersCarToSpace(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	// subMenuIndex is the index of the player you selected in the game, or it should be at least
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	printf("ExplodeOnlinePlayerVehicleOnPlayerSelected subMenuIndex = %d\n", subMenuIndex);
	int Handle = GetPlayerHandle(subMenuIndex);
	printf("PlayerHandle = %i, ", Handle);
	int vehicle;
	int hash;
	if (isInDistance(Handle))
	{
		vehicle = GetCarCharIsIn2(Handle, subMenuIndex);
		printf("Got Vehicle Handle %i\n", vehicle);
		if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle))
		{
			printf("Vehicle Exists\n");
			network_request_control_of_entity(vehicle);
			while ((!network_has_control_of_entity(vehicle))){network_request_control_of_entity(vehicle);}
			printf("Attempted to grab control of vehicle\n");
			if (network_has_control_of_entity(vehicle))
			{
				printf("Got control\n");
				apply_force_to_entity(vehicle, true, 0, 0, 150, 0, 0, 0, true, true, true, true);
				printf("Sent Car Into The Sky!\n");
			}
		}
	}
	else
		printf("Player is out of range\n");
	return 0;
}

int TowTruck(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	// subMenuIndex is the index of the player you selected in the game, or it should be at least
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	printf("ExplodeOnlinePlayerVehicleOnPlayerSelected subMenuIndex = %d\n", subMenuIndex);
	int Handle = GetPlayerHandle(subMenuIndex);
	printf("PlayerHandle = %i, ", Handle);
	int vehicle;
	int myvehicle;
	int hash;
	vehicle = GetCarCharIsIn(Handle, subMenuIndex);
	//myvehicle = GetCarCharIsIn(0x1202/*PlayerPedId()*/, PlayerId());
	float Position[3];
    GetEntityCoords(Handle, &Position);
	printf("Player X = %f\n", Position[0]);
	printf("Player Y = %f\n", Position[1]);
	printf("Player Z = %f\n", Position[2]);
	printf("Got Vehicle Handle %i\n", vehicle);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle))
	{
		printf("Vehicle Exists\n");
		network_request_control_of_entity(vehicle);
		while ((!network_has_control_of_entity(vehicle))){network_request_control_of_entity(vehicle);}
		printf("Attempted to grab control of vehicle\n");
		if (network_has_control_of_entity(vehicle))
		{
			printf("Got control\n");
			//attach_entity_to_entity(vehicle, myvehicle, 0, 0, 0, 3.0, 0, 0, 0);
			CarVisibleDamage(vehicle, false);
		    set_entity_can_be_damaged(vehicle, false);
			printf("God Mode Vehicle Given!!\n");
		}
	}
	return 0;
}


int SuperRun(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	myplayerped = GetPlayerHandle(PlayerId());
    Sleep(500);
    printf("Attempted to activate super jump");
    superruncheck = !superruncheck;//toggle
	return 0;
}

void super_run()
{
if (menuInputHandler->AButtonDown())
{
printf("running\n");
apply_force_to_entity(myplayerped, true, 0, 3, 0, 0, 0, 0, true, true, true, true);
}
}

int SuperJump(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	myplayerped = GetPlayerHandle(PlayerId());
    Sleep(500);
    printf("Attempted to activate super jump");
    superjump = !superjump;//toggle
	return 0;
}

void super_jump()
{
	if (!buttonpressed)
	{
	if (menuInputHandler->XButtonDown())
	{
	buttonpressed = true;
	printf("X button pressed\n");
	apply_force_to_entity(myplayerped, true, 0, 0, 15, 0, 0, 0, true, true, true, true);
	Sleep(600);
	buttonpressed = false;
	}
	}
}

int SpawnSultan(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	unsigned int handle,
		Sultan = 0x39DA2754;
	float Position[3];
	if (DoesEntityExist(PlayerPedId())) {
		GetEntityCoords(PlayerPedId(), &Position);
		printf("Player Exists\n");
	}

	if (IsModelInCdImage(Sultan)) {
		printf("Sultan Model Exists\n");
		RequestModel(Sultan);
		printf("Request Model\n");
		while(!HasModelLoaded(Sultan));
		printf("Model Loaded\n");
		handle = CreateCar(Sultan, Position[0], Position[1] + 10.0f, Position[2], 0);
		printf("Spawned Sultan\n");
		return 0;
	}
}

int TeleportToOnlinePlayer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	TeleportToClient(subMenuIndex);
	return 0;
}

DWORD WINAPI GTAVMenuThread(LPVOID lpParam)
{
	// Allocate our input handler
	menuInputHandler = new Input;

	// Setup menu
	mainMenu = new GTAVMenu;
	playerOptionsMenu = new GTAVMenu;
	vehicleOptionMenu = new GTAVMenu;
	weaponOptionsMenu = new GTAVMenu;
	onlinePlayers = new GTAVMenu;
	onlinePlayersSubMenu = new GTAVMenu;
	CarSpawnerMenu = new GTAVMenu;
	OnlinePlayerVehicleOptions = new GTAVMenu;
	OnlinePlayerTeleport = new GTAVMenu;

	// Setup player options
	playerOptionsMenu->SetMenuTitle("Player Options");
	playerOptionsMenu->AddStaticItem("Toggle Invincibility", true, ToggleInvincibility, NULL);
	playerOptionsMenu->AddStaticItem("Super Jump", true, SuperJump, NULL);
	playerOptionsMenu->AddStaticItem("Super Run", true, SuperRun, NULL);

	// Setup vehicle options menu
	vehicleOptionMenu->SetMenuTitle("Vehicle Options");
	vehicleOptionMenu->AddStaticItem("Rainbow Car", true, ToggleRainbow, NULL);
	vehicleOptionMenu->AddStaticItem("Invincibe Vehicle", true, ToggleInvisibleCar, NULL);

	// Setup weapon options menu
	weaponOptionsMenu->SetMenuTitle("Weapon Options");
	weaponOptionsMenu->AddStaticItem("Dummy Item 1", false, NULL, NULL);
	weaponOptionsMenu->AddStaticItem("Dummy Item 2", false, NULL, NULL);

	// Setup online sub players
	onlinePlayersSubMenu->SetMenuTitle("Online Players Options");
	onlinePlayersSubMenu->AddSubMenu("Vehicle Options", OnlinePlayerVehicleOptions);
	onlinePlayersSubMenu->AddSubMenu("Teleport", OnlinePlayerTeleport);

	// Online player vehicle options

	OnlinePlayerVehicleOptions->SetMenuTitle("Vehicle Options");
	OnlinePlayerVehicleOptions->AddStaticItem("Change Colour Of Players Car", false, PaintOnlinePlayersCar, NULL);
	OnlinePlayerVehicleOptions->AddStaticItem("Light Players Car On Fire", false, ExplodeOnlinePlayerVehicle, NULL);
	OnlinePlayerVehicleOptions->AddStaticItem("Launch Players Vehicle In Sky", false, SendPlayersCarToSpace, NULL);
	OnlinePlayerVehicleOptions->AddStaticItem("Give Players Vehicle God Mode", false, TowTruck, NULL);

	// Online player teleport options

	OnlinePlayerTeleport->SetMenuTitle("Teleport Options");
	OnlinePlayerTeleport->AddStaticItem("Teleport To Player", false, TeleportToOnlinePlayer, NULL);

	// setup car spawner menu
    CarSpawnerMenu->SetMenuTitle("Vehicle Spawner");
	CarSpawnerMenu->AddStaticItem("Sultan", false, SpawnSultan, NULL);


	// Setup online players
	onlinePlayers->SetMenuTitle("Online Players");
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);

	// Setup main menu last
	mainMenu->SetMenuTitle("Main Menu");
	mainMenu->AddSubMenu("Player Options", playerOptionsMenu);
	mainMenu->AddSubMenu("Vehicle Options", vehicleOptionMenu);
	mainMenu->AddSubMenu("Weapon Options", weaponOptionsMenu);
	mainMenu->AddSubMenu("Online Player Menu", onlinePlayers);
	mainMenu->AddSubMenu("Vehicle Spawner", CarSpawnerMenu);
	

	while (TRUE)
	{
		if (XamGetCurrentTitleId() != 0x545408A7)
			std::terminate();
		if(rainbow)
		rainbow_car();
		if(superjump)
		super_jump();
		if(superruncheck)
		super_run();
		// Update our input
		menuInputHandler->UpdateInput();

		// Check to see if we activated our menu
		if (menuInputHandler->DPadLeftDown() && menuInputHandler->XButtonDown() && !inputButtonsPressed) {
			enableMenu = !enableMenu;
			printf("Menu %s\n", enableMenu ? "opened" : "closed");
			inputButtonsPressed = true;
		}
		else if (!menuInputHandler->DPadLeftDown() && !menuInputHandler->XButtonDown()) {
			inputButtonsPressed = false;

		}

		// Display our menu if we must
		if (enableMenu) {
			// update players list if the menu is open
			for (int i = 0; i < 16; i++) {
				GTAVMenuItem *menuItem = &onlinePlayers->menuItems->operator[](i);

				// Get player name
				char *playerName = GetPlayerName(i);

				// clear out the name
				memset(menuItem->itemText, 0, 32);

				// Copy the name into the struct
				strcpy_s(menuItem->itemText, 32, playerName);
			}

			mainMenu->DisplayMenu();
		}

		// this is a pretty cheap way of doing it, it makes it all flashy
		// TODO hook into the game loop and do it a better way
		Sleep(1);
	}
}

LONG WINAPI Exception(struct _EXCEPTION_POINTERS *e)
{
	printf("GTAV Menu crashed for some reason");

	HalReturnToFirmware(HalRebootQuiesceRoutine);
}

void TestPrint() {
	menuInputHandler->UpdateInput();

	// Check to see if we activated our menu
	if (menuInputHandler->DPadLeftDown() && menuInputHandler->XButtonDown() && !inputButtonsPressed) {
		enableMenu = !enableMenu;
		printf("Menu %s\n", enableMenu ? "opened" : "closed");
		inputButtonsPressed = true;
	}
	else if (!menuInputHandler->DPadLeftDown() && !menuInputHandler->XButtonDown()) {
		inputButtonsPressed = false;
	}

	if (enableMenu) {
		float staticItemX = 0.05000000f;
		float staticItemY = 0.10000000f;

		PrintToScreen("Hello World", staticItemX, staticItemY, 255, 255, 255, 255, 0.35f, 0.35f);
	}
}

void __declspec(naked) InGameHookDest() {
	__asm {
		bl TestPrint

		mr        r3, r26
		addi      r1, r1, 0x90
		ld        r26, -0x38(r1)
		ld        r27, -0x30(r1)
		ld        r28, -0x28(r1)
		ld        r29, -0x20(r1)
		ld        r30, -0x18(r1)
		ld        r31, -0x10(r1)
		lwz       r12, -0x8(r1)
		mtspr   LR, r12
		blr
	}
}

VOID PatchInJumpDev(DWORD addr, DWORD dest, BOOL linked) {
	DWORD Data[4];
	// Devkits dont like to be violated in thier code sections directly,
	// this is a workaround.
	printf("PatchInJump\n");
	PatchInJump(Data, dest, linked);

	DWORD cbRet = 0;
	printf("DmSetMemory\n");
	HRESULT hr = DmSetMemory((LPVOID)addr, 16, Data, &cbRet);

	printf("hr = %08X cbRet = %08X\n", hr, cbRet);

	if (hr != XBDM_NOERR || cbRet != 16) {
		printf("DmSetMemory failed. HRESULT = %08X cbRet = %d\n", hr, cbRet);
	}
}

BOOL APIENTRY DllMain( HANDLE hModule, DWORD dwReason, LPVOID lpReserved)  {
	if (dwReason == DLL_PROCESS_ATTACH)  {

		if (XamGetCurrentTitleId() != 0x545408A7 || *(int *)0x828CBF10 != 0x816308C4/*TU check*/) {
			printf("We are not in GTAV!\n");
			return FALSE;
		}

		printf("GTAV Menu Loading...\n");

		// Allocate our input handler
		menuInputHandler = new Input;

		DmStop();

		PatchInJumpDev(0x823A0A90, (DWORD)InGameHookDest, FALSE);

		DmGo();

		/*HANDLE hThread; 
		DWORD threadId;

		ExCreateThread(&hThread, 0, &threadId, (VOID*)XapiThreadStartup, GTAVMenuThread, NULL, 0x2 | CREATE_SUSPENDED);
		XSetThreadProcessor(hThread, 4);
		SetThreadPriority(hThread, THREAD_PRIORITY_HIGHEST);

		ResumeThread(hThread);*/
	}

	return TRUE;
}
