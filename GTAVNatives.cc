#include "GTAVNatives.h"
#include "EncryptedDWORD.h"


DWORD VMPassed[100];
DWORD VMReturned[5];
DWORD *VMArgs[3] = {
VMReturned,
0,
VMPassed
};

vector<GTAVNative> *gtavNativesList;

void InitNativeHook() {
	gtavNativesList = new vector<GTAVNative>;
}

void GtavNativeLoadHook(unsigned int r3, unsigned int r4) {//
	extern EncryptedDWORD *nativeHook;
	int(__cdecl *func)(unsigned int, unsigned int, unsigned int) = (int(__cdecl *)(unsigned int, unsigned int, unsigned int))nativeHook->GetValue(); // 1.13 1.12 0x834BFBD8 Update every TU

	GTAVNative native;
	native.hashValue = r3;
	native.functionOffset = r4;
	gtavNativesList->push_back(native);



	unsigned int r5 = r4;
	r4 = (r3 < 2) ? r3 + 2 : r3;


	func(0x83DDCD08, r4, r5);

}

DWORD FindNative(DWORD hashValue) {
	for (int i = 0; i < gtavNativesList->size(); i++) {
		if (gtavNativesList->operator[](i).hashValue == hashValue) {
			return gtavNativesList->operator[](i).functionOffset;
		}
	}

	return 0;
}

int CallNative(int nativeAddress, int argumentCount, ...) {
	GTAVNativeCall gtavCall;

	gtavCall.returnValue = new int[1];
	gtavCall.argumentCount = argumentCount;
	gtavCall.argumentData = new int[argumentCount];

	va_list pArgList;
	va_start(pArgList, argumentCount);

	for (int i = 0; i < argumentCount; i++) {
		gtavCall.argumentData[i] = va_arg(pArgList, int);
	}

	int returnValue = ((int(*)(void *))nativeAddress)(&gtavCall);

	delete[] gtavCall.argumentData;

	int ret = gtavCall.returnValue[0];

	delete[] gtavCall.returnValue;

	return ret;
}



DWORD SaveVMPassed[100];

void SaveStack() {
	memcpy(&SaveVMPassed, &VMPassed, 100 * 4);
}

void ResetStack() {
	memcpy(&VMPassed, &SaveVMPassed, 100 * 4);
}

int GET_NUMBER_OF_PLAYERS() {
	((void(*)(void *))FindNative(0x4C1B8867))(VMArgs);
	return VMArgs[0][0];
}

void _START_SCREEN_EFFECT(char *effectName, int playLength, bool loop) {
	VMArgs[2][0] = *effectName;
	VMArgs[2][1] = playLength;
	VMArgs[2][2] = loop;
	((void(*)(void *))FindNative(0x1D980479))(VMArgs);
	ResetStack();
}

void SET_GRAVITY_LEVEL(int level) {
	VMArgs[2][0] = level;
	((void(*)(void *))FindNative(0x2D833F4A))(VMArgs);
	ResetStack();
}
void CarVisibleDamage(int carhandle, bool damage) {
	SaveStack();
	VMArgs[2][0] = carhandle;
	VMArgs[2][1] = damage;

	int(__cdecl *set_vehicle_can_be_visibly_damaged)(void *) = (int(__cdecl *)(void *))FindNative(0xC5D94017);
	set_vehicle_can_be_visibly_damaged(VMArgs);
	ResetStack();
}

int GET_CONTROL_VALUE(int index, int control) {
	VMArgs[2][0] = index;
	VMArgs[2][1] = control;
	((void(*)(void *))FindNative(0xC526F3C6))(VMArgs);
	return VMArgs[0][0];
}

void SET_PED_RANDOM_PROPS(int ped) {
	VMArgs[2][0] = ped;
	((void(__cdecl *)(void *))FindNative(0xE3318E0E))(VMArgs);
}


void draw_rect(float xpos, float ypos, float xlen, float ylen, int r, int g, int b, int a) {
	SaveStack();
	VMArgs[2][0] = *(DWORD *)(&xpos);
	VMArgs[2][1] = *(DWORD *)(&ypos);
	VMArgs[2][2] = *(DWORD *)(&xlen);
	VMArgs[2][3] = *(DWORD *)(&ylen);
	VMArgs[2][4] = r;
	VMArgs[2][5] = g;
	VMArgs[2][6] = b;
	VMArgs[2][7] = a;
	((void(*)(void *))FindNative(0xDD2BFC77))(VMArgs);
	ResetStack();
}

bool IS_ENTITY_TOUCHING_ENTITY(int player, int entity) {
	SaveStack();
	VMArgs[2][0] = player;
	VMArgs[2][1] = entity;
	int(__cdecl *IS_ENTITY_TOUCHING_ENTITY)(void *) = (int(__cdecl *)(void *))FindNative(0x6B931477);
	IS_ENTITY_TOUCHING_ENTITY(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void SHOOT_SINGLE_BULLET_BETWEEN_COORDS(float x, float y, float z, float x2, float y2, float z2, int unk, int unk1, int hash, int ped, int unk2, int unk3, float speed) {
	SaveStack();
	VMArgs[2][0] = *(int *)&x;
	VMArgs[2][1] = *(int *)&y;
	VMArgs[2][2] = *(int *)&z;
	VMArgs[2][3] = *(int *)&x2;
	VMArgs[2][4] = *(int *)&y2;
	VMArgs[2][5] = *(int *)&z2;
	VMArgs[2][6] = unk;
	VMArgs[2][7] = unk1;
	VMArgs[2][8] = hash;
	VMArgs[2][9] = ped;
	VMArgs[2][10] = unk2;
	VMArgs[2][11] = unk3;
	VMArgs[2][12] = *(int *)&speed;
	((void(*)(void *))FindNative(0xCB7415AC))(VMArgs);
	ResetStack();
}

void play_sound_frontend(int time, const char* sound_name, const char* sound_dict) {
	SaveStack();
	VMArgs[2][0] = time;
	VMArgs[2][1] = (DWORD)sound_name;
	VMArgs[2][2] = (DWORD)sound_dict;
	((void(*)(void*))FindNative(0x2E458F74))(VMArgs);
	ResetStack();
}

void SET_PED_INTO_VEHICLE(INT PED_ID, INT VEH_ID, INT r2) {
	VMArgs[2][0] = PED_ID;
	VMArgs[2][1] = VEH_ID;
	VMArgs[2][2] = r2;
	((VOID(*)(PVOID))FindNative(0x07500C79))(VMArgs);
}


void network_earn_from_rockstar(int amount) {
	SaveStack();
	VMArgs[2][0] = amount;
	((void(*)(void*))FindNative(0x5A3733CC))(VMArgs);
	ResetStack();
}

void TASK_GO_STRAIGHT_TO_COORD(int ped, float x, float y, float z, float speed, int timeout, float targetHeading, float distanceToSlide) {
	VMArgs[2][0] = ped;
	VMArgs[2][1] = *(DWORD *)&(x);
	VMArgs[2][2] = *(DWORD *)&(y);
	VMArgs[2][3] = *(DWORD *)&(z);
	VMArgs[2][4] = *(DWORD *)&(speed);
	VMArgs[2][5] = timeout;
	VMArgs[2][6] = *(DWORD *)&(targetHeading);
	VMArgs[2][7] = *(DWORD *)&(distanceToSlide);
	((void(*)(void*))FindNative(0x80A9E7A7))(VMArgs);
}

void SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(int ped, int state) {
	VMArgs[2][0] = ped;
	VMArgs[2][1] = state;
	((void(*)(void *))FindNative(0x8A251612))(VMArgs);
}

void SET_PED_PROP_INDEX(int ped, int componentId, int drawableId, int TextureId, BOOL isMP) {
	VMArgs[2][0] = ped;
	VMArgs[2][1] = componentId;
	VMArgs[2][2] = drawableId;
	VMArgs[2][3] = TextureId;
	VMArgs[2][4] = isMP;
	((void(*)(void*))FindNative(0x0829F2E2))(VMArgs);
}

void SET_PED_CAN_RAGDOLL(INT ped, BOOL toggle) {
	VMArgs[2][0] = ped;
	VMArgs[2][1] = toggle;
	((void(*)(void *))FindNative(0xCF1384C4))(VMArgs);
}

VOID CREATE_AMBIENT_PICKUP_CUSTOM(INT Hash, PFLOAT Origin, INT r5, INT r6, INT r7, INT r8, INT r9) {
	VMArgs[2][0] = Hash;
	VMArgs[2][1] = *(DWORD*)(&Origin[0]);
	VMArgs[2][2] = *(DWORD*)(&Origin[1]);
	VMArgs[2][3] = *(DWORD*)(&Origin[2]);
	VMArgs[2][4] = r5;
	VMArgs[2][5] = r6;
	VMArgs[2][6] = r7;
	VMArgs[2][7] = r8;
	VMArgs[2][8] = r9;
	((VOID(*)(PVOID))FindNative(0xE51B4C5A))(VMArgs);
}

void NETWORK_BUY_BOUNTY(int ped, int p1, int p2, int p3) {
	VMArgs[2][0] = ped;
	VMArgs[2][1] = p1;
	VMArgs[2][2] = p2;
	VMArgs[2][3] = p3;
	((void(*)(void *))FindNative(0xCB89CBE0))(VMArgs);
}

void NETWORK_SPENT_BUY_OFFTHERADAR(int ped, int p1, int p2) {
	VMArgs[2][0] = ped;
	VMArgs[2][1] = p1;
	VMArgs[2][2] = p2;
	((void(*)(void *))FindNative(0x20DDCF2F))(VMArgs);
}

void ROLL_DOWN_WINDOWS(int vehicle) {
	VMArgs[2][0] = vehicle;
	((void(*)(void *))FindNative(0x51A16DC6))(VMArgs);
}
void NETWORK_BUY_AIRSTRIKE(int cost, int p1, int p2) {
	VMArgs[2][0] = cost;
	VMArgs[2][1] = p1;
	VMArgs[2][2] = p2;
	((void(*)(void *))FindNative(0x40470683))(VMArgs);
}
void SET_PED_CURRENT_WEAPON_VISIBLE(int ped, int p1, int p2, int p3, int p4) {
	VMArgs[2][0] = ped;
	VMArgs[2][1] = p1;
	VMArgs[2][2] = p2;
	VMArgs[2][3] = p3;
	VMArgs[2][4] = p4;
	((void(*)(void *))FindNative(0x00BECD77))(VMArgs);
}


void set_vehicle_rpm(int veh, float rpm) {
	SaveStack();
	VMArgs[2][0] = veh;
	VMArgs[2][1] = *(DWORD *)(&rpm);
	((void(*)(void *))FindNative(0xE943B09C))(VMArgs);
	ResetStack();
}

void SMASH_VEHICLE_WINDOW(int vehicle, int window) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = window;
	((void(*)(void *))FindNative(0xDDD9A8C2))(VMArgs);
	ResetStack();
}

void REQUEST_NAMED_PTFX_ASSET(char *fxName) {
	SaveStack();
	VMArgs[2][0] = (int)fxName;
	((void(*)(void *))FindNative(0xCFEA19A9))(VMArgs);
	ResetStack();
}

void SET_PARTICLE_FX_NON_LOOPED_ALPHA(float alpha) {
	SaveStack();
	VMArgs[2][0] = *(int *)&alpha;
	((void(*)(void *))FindNative(0x497EAFF2))(VMArgs);
	ResetStack();
}
void _SET_PTFX_ASSET_NEXT_CALL(char *name) {
	SaveStack();
	VMArgs[2][0] = (int)name;
	((void(*)(void *))FindNative(0x9C720B61))(VMArgs);
	ResetStack();
}

bool HAS_NAMED_PTFX_ASSET_LOADED(char *fxName) {
	SaveStack();
	VMArgs[2][0] = (int)fxName;
	((void(*)(void *))FindNative(0x9ACC6446))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

bool START_PARTICLE_FX_NON_LOOPED_ON_ENTITY(char *effectName, int entity, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, float scale, BOOL p9, BOOL p10, BOOL p11) {
	SaveStack();
	VMArgs[2][0] = (int)effectName;
	VMArgs[2][1] = entity;
	VMArgs[2][2] = *(int *)&xOffset;
	VMArgs[2][3] = *(int *)&yOffset;
	VMArgs[2][4] = *(int *)&zOffset;
	VMArgs[2][5] = *(int *)&xRot;
	VMArgs[2][6] = *(int *)&yRot;
	VMArgs[2][7] = *(int *)&zRot;
	VMArgs[2][8] = *(int *)&scale;
	VMArgs[2][9] = p9;
	VMArgs[2][10] = p10;
	VMArgs[2][11] = p11;
	((void(*)(void *))FindNative(0x9604DAD4))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

BOOL START_PARTICLE_FX_NON_LOOPED_AT_COORD(char *effectName, float x, float y, float z, float xRot, float yRot, float zRot, float scale, BOOL p8, BOOL p9, BOOL p10) {
	VMArgs[2][0] = (int)effectName;
	VMArgs[2][1] = *(int *)&x;
	VMArgs[2][2] = *(int *)&y;
	VMArgs[2][3] = *(int *)&z;
	VMArgs[2][4] = *(int *)&xRot;
	VMArgs[2][5] = *(int *)&yRot;
	VMArgs[2][6] = *(int *)&zRot;
	VMArgs[2][7] = *(int *)&scale;
	VMArgs[2][8] = p8;
	VMArgs[2][9] = p9;
	VMArgs[2][10] = p10;
	((VOID(*)(PVOID))FindNative(0xDD79D679))(VMArgs);
	return VMArgs[0][0];
}
BOOL HAS_WEAPON_ASSET_LOADED(int Hash) {
	VMArgs[2][0] = Hash;
	((VOID(*)(PVOID))FindNative(0x1891D5BB))(VMArgs);
	return VMArgs[0][0];
}

BOOL STAT_SET_INT(DWORD statName, int value, BOOL save) {
	VMArgs[2][0] = statName;
	VMArgs[2][1] = value;
	VMArgs[2][2] = save;
	((VOID(*)(PVOID))FindNative(0xC9CC1C5C))(VMArgs);
	return VMArgs[0][0];
}


void set_stat_int(int stat, int val) {
	SaveStack();
	VMArgs[2][0] = stat;
	VMArgs[2][1] = val;
	((void(*)(void *))FindNative(0xC9CC1C5C))(VMArgs);
	ResetStack();
}

void set_stat_bool(int stat, bool val) {
	SaveStack();
	VMArgs[2][0] = stat;
	VMArgs[2][1] = val;
	((void(*)(void *))FindNative(0x55D79DFB))(VMArgs);
	ResetStack();
}

void CLONE_PED(int ped, float header, bool createNetworkHandle, bool createPedHandle) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = *(DWORD *)(&header);
	VMArgs[2][2] = createNetworkHandle;
	VMArgs[2][3] = createPedHandle;
	((void(*)(void *))FindNative(0x8C8A8D6E))(VMArgs);
	ResetStack();
}




void set_entity_can_be_damaged(int carhandle, bool damage) {
	SaveStack();
	VMArgs[2][0] = carhandle;
	VMArgs[2][1] = damage;
	((void(*)(void *))FindNative(0x60B6E744))(VMArgs);
	ResetStack();
}

bool is_ped_running(bool running) {
	SaveStack();
	VMArgs[2][0] = running;
	((void(*)(void *))FindNative(0xE9A5578F))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void set_cinematic_button_active(bool active) {
	SaveStack();
	VMArgs[2][0] = active;
	((void(*)(void *))FindNative(0x3FBC5D00))(VMArgs);
	ResetStack();
}

void hide_help_text_this_frame() {
	SaveStack();
	((void(*)(void *))FindNative(0xF3807BED))(VMArgs);
	ResetStack();
}

void disable_control_action(int unk, int unk2) {
	SaveStack();
	VMArgs[2][0] = unk;
	VMArgs[2][1] = unk2;
	((void(*)(void *))FindNative(0x3800C0DC))(VMArgs);
	ResetStack();
}

void unk_0x4E8E29E6(int unk, int unk1) {
	SaveStack();
	VMArgs[2][0] = unk;
	VMArgs[2][1] = unk1;
	((void(*)(void *))FindNative(0x4E8E29E6))(VMArgs);
	ResetStack();
}

void GIVE_WEAPON_COMPONENT_TO_PED(int playerid, int weapon, int component) {
	SaveStack();
	VMArgs[2][0] = playerid;
	VMArgs[2][1] = weapon;
	VMArgs[2][2] = component;

	((void(*)(void *))FindNative(0x3E1E286D))(VMArgs);
	ResetStack();
}
void hide_hud_component_this_frame(int unk) {
	SaveStack();
	VMArgs[2][0] = unk;
	((void(*)(void *))FindNative(0xDB2D0762))(VMArgs);
	ResetStack();
}

void create_ambient_pickup(int Hash, float* Pos, int r5, int r6, int r7, int r8, int r9) {
	SaveStack();
	VMArgs[2][0] = Hash;
	VMArgs[2][1] = *(DWORD *)(&Pos[0]);
	VMArgs[2][2] = *(DWORD *)(&Pos[1]);
	VMArgs[2][3] = *(DWORD *)(&Pos[2]);
	VMArgs[2][4] = r5;
	VMArgs[2][5] = r6;
	VMArgs[2][6] = r7;
	VMArgs[2][7] = r8;
	VMArgs[2][8] = r9;
	((void(*)(void *))FindNative(0xE51B4C5A))(VMArgs);
	ResetStack();
}

void create_ambient_pickup3(int Hash, Vector3 *Pos, int r5, int r6, int r7, int r8, int r9) {
	SaveStack();
	VMArgs[2][0] = Hash;
	VMArgs[2][1] = *(DWORD *)(&Pos[0]);
	VMArgs[2][2] = *(DWORD *)(&Pos[1]);
	VMArgs[2][3] = *(DWORD *)(&Pos[2]);
	VMArgs[2][4] = r5;
	VMArgs[2][5] = r6;
	VMArgs[2][6] = r7;
	VMArgs[2][7] = r8;
	VMArgs[2][8] = r9;
	((void(*)(void *))FindNative(0xE51B4C5A))(VMArgs);
	ResetStack();
}


void create_ambient_pickup2(int Hash, float x, float y, float z, int r4, int value, int modelHash, int r8, int r9) {
	SaveStack();
	VMArgs[2][0] = Hash;
	VMArgs[2][1] = *(DWORD *)(&x);
	VMArgs[2][2] = *(DWORD *)(&y);
	VMArgs[2][3] = *(DWORD *)(&z);
	VMArgs[2][4] = r4;
	VMArgs[2][5] = value;
	VMArgs[2][6] = modelHash;
	VMArgs[2][7] = r8;
	VMArgs[2][8] = r9;
	((void(*)(void *))FindNative(0xE51B4C5A))(VMArgs);
	ResetStack();
}

void apply_force_to_entity(int vehicle, unsigned int unknown0, float x, float y, float z, float spinX, float spinY, float spinZ, unsigned int unknown4, unsigned int unknown5_1, unsigned int unknown6_1, unsigned int unknown7_1, bool unk, bool unk1) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = unknown0;
	VMArgs[2][2] = *(DWORD *)(&x);
	VMArgs[2][3] = *(DWORD *)(&y);
	VMArgs[2][4] = *(DWORD *)(&z);
	VMArgs[2][5] = *(DWORD *)(&spinX);
	VMArgs[2][6] = *(DWORD *)(&spinY);
	VMArgs[2][7] = *(DWORD *)(&spinZ);
	VMArgs[2][8] = unknown4;
	VMArgs[2][9] = unknown5_1;
	VMArgs[2][10] = unknown6_1;
	VMArgs[2][11] = unknown7_1;
	VMArgs[2][12] = unk;
	VMArgs[2][13] = unk1;
	((void(*)(void *))FindNative(0xC1C0855A))(VMArgs);
	ResetStack();
}

bool unk_0xCD71F11B(int ped) {
	SaveStack();
	VMArgs[2][0] = ped;
	((void(*)(void *))FindNative(0xCD71F11B))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

bool has_streamed_texture_dict_loaded(char *str) {
	SaveStack();
	VMArgs[2][0] = (int)str;
	((void(*)(void *))FindNative(0x3F436EEF))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void request_ipl(char *str) {
	SaveStack();
	VMArgs[2][0] = (int)str;
	((void(*)(void *))FindNative(0x3B70D1DB))(VMArgs);
	ResetStack();
}


BOOL STAT_SET_BOOL(DWORD statName, BOOL value, BOOL save) {
	VMArgs[2][0] = statName;
	VMArgs[2][1] = value;
	VMArgs[2][2] = save;
	((VOID(*)(PVOID))FindNative(0x55D79DFB))(VMArgs);
	return VMArgs[0][0];
}

unsigned int GetPlayerHandle(int index) {
	SaveStack();
	VMArgs[2][0] = index;
	int(__cdecl *get_player_ped)(void *) = (int(__cdecl *)(void *))FindNative(0x6E31E993);
	get_player_ped(VMArgs);
	ResetStack();
	return (int)(*VMArgs[0]);
}

int PlayerId() {
	int(__cdecl *player_id)(void *) = (int(__cdecl *)(void *))FindNative(0x8AEA886C);

	player_id(VMArgs);

	return (int)(*VMArgs[0]);
}

bool DoesEntityExist(int entity) {
	SaveStack();
	VMArgs[2][0] = entity;

	int(__cdecl *does_entity_exist)(void *) = (int(__cdecl *)(void *))FindNative(0x3AC90869);
	does_entity_exist(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}


unsigned int PlayerPedId() {
	int(__cdecl *player_ped_id)(void *) = (int(__cdecl *)(void *))FindNative(0xFA92E226);
	player_ped_id(VMArgs);
	return (int)(*VMArgs[0]);
}

unsigned int GET_PLAYERS_LAST_VEHICLE() {
	int(__cdecl *get_players_last_vehicle)(void *) = (int(__cdecl *)(void *))FindNative(0xE2757AC1);
	get_players_last_vehicle(VMArgs);
	return (int)(*VMArgs[0]);
}

void _ADD_SPECFX_EXPLOSION(float x, float y, float z, int explosionType, int explosionFx, float damageScale, BOOL isAudible, BOOL isInvisible, float cameraShake) {
	VMArgs[2][1] = *(DWORD*)(&x);
	VMArgs[2][2] = *(DWORD*)(&y);
	VMArgs[2][3] = *(DWORD*)(&z);
	VMArgs[2][4] = explosionType;
	VMArgs[2][5] = explosionFx;
	VMArgs[2][6] = *(DWORD*)(&damageScale);
	VMArgs[2][7] = isAudible;
	VMArgs[2][8] = isInvisible;
	VMArgs[2][9] = *(DWORD*)(&cameraShake);
	((void(*)(void *))FindNative(0xCF358946))(VMArgs);
}

void ADD_OWNED_EXPLOSION(int ped, float x, float y, float z, int explosionType, float damageScale, BOOL isAudible, BOOL isInvisible, float cameraShake) {
	VMArgs[2][0] = ped;
	VMArgs[2][1] = *(DWORD*)(&x);
	VMArgs[2][2] = *(DWORD*)(&y);
	VMArgs[2][3] = *(DWORD*)(&z);
	VMArgs[2][4] = explosionType;
	VMArgs[2][5] = *(DWORD*)(&damageScale);
	VMArgs[2][6] = isAudible;
	VMArgs[2][7] = isInvisible;
	VMArgs[2][8] = *(DWORD*)(&cameraShake);
	((void(*)(void *))FindNative(0x27EE0D67))(VMArgs);
}

void GET_WORLD_POSITION_OF_ENTITY_BONE(int entity, int boneIndex, float* Out) {
	SaveStack();
	VMArgs[2][0] = entity;
	VMArgs[2][1] = boneIndex;
	VMArgs[2][2] = 1;
	((void(*)(void *))FindNative(0x7C6339DF))(VMArgs);
	ResetStack();
	memcpy(Out, VMArgs[0], 0xC);
}

void GetEntityCoords(int PedID, float* Out) {
	SaveStack();
	VMArgs[2][0] = PedID;
	VMArgs[2][1] = 1;
	((void(*)(void *))FindNative(0x1647F1CB))(VMArgs);
	ResetStack();
	memcpy(Out, VMArgs[0], 0xC);
}

void request_streamed_texture_dict(char *str, int unk) {
	SaveStack();
	VMArgs[2][0] = (int)str;
	VMArgs[2][1] = unk;
	((void(*)(void *))FindNative(0x4C9B035F))(VMArgs);
	ResetStack();

}

void draw_sprite(char *str, char *str2, float f1, float f2, float f3, float f4, float f5, int r, int g, int b, int a) {
	SaveStack();
	VMArgs[2][0] = (int)str;
	VMArgs[2][1] = (int)str2;
	VMArgs[2][2] = *(DWORD *)(&f1);
	VMArgs[2][3] = *(DWORD *)(&f2);
	VMArgs[2][4] = *(DWORD *)(&f3);
	VMArgs[2][5] = *(DWORD *)(&f4);
	VMArgs[2][6] = *(DWORD *)(&f5);
	VMArgs[2][7] = r;
	VMArgs[2][8] = g;
	VMArgs[2][9] = b;
	VMArgs[2][10] = a;
	((void(*)(void *))FindNative(0x1FEC16B0))(VMArgs);
	ResetStack();

}



void create_model_swap(float x, float y, float z, float unk, int modeltoswap, int swapto, int unk1) {
	SaveStack();
	VMArgs[2][0] = *(DWORD *)(&x);
	VMArgs[2][1] = *(DWORD *)(&y);
	VMArgs[2][2] = *(DWORD *)(&z);
	VMArgs[2][3] = *(DWORD *)(&unk);
	VMArgs[2][4] = modeltoswap;
	VMArgs[2][5] = swapto;
	VMArgs[2][6] = unk1;
	((void(*)(void *))FindNative(0x0BC12F9E))(VMArgs);
	ResetStack();

}

void attach_entity_to_entity(int car0, int car1, int unk, float x0, float y0, float z0, float x1, float y1, float z1,
	int unk1, int unk2, int unk3, int unk4, int unk5, int unk6) {
	SaveStack();
	VMArgs[2][0] = car0;
	VMArgs[2][1] = car1;
	VMArgs[2][2] = unk;
	VMArgs[2][3] = *(int *)&x0;
	VMArgs[2][4] = *(int *)&y0;
	VMArgs[2][5] = *(int *)&z0;
	VMArgs[2][6] = *(int *)&x1;
	VMArgs[2][7] = *(int *)&y1;
	VMArgs[2][8] = *(int *)&z1;
	VMArgs[2][9] = unk1;
	VMArgs[2][10] = unk2;
	VMArgs[2][11] = unk3;
	VMArgs[2][12] = unk4;
	VMArgs[2][13] = unk5;
	VMArgs[2][14] = unk5;
	((void(*)(void *))FindNative(0xEC024237))(VMArgs);
	ResetStack();
}

void attach_entity_to_entity420(int car0, int car1, int boneIndex, float x0, float y0, float z0, float x1, float y1, float z1,
	int unk1, int unk2, int unk3, int unk4, int unk5, int unk6) {
	SaveStack();
	VMArgs[2][0] = car0;
	VMArgs[2][1] = car1;
	VMArgs[2][2] = boneIndex;
	VMArgs[2][3] = *(int *)&x0;
	VMArgs[2][4] = *(int *)&y0;
	VMArgs[2][5] = *(int *)&z0;
	VMArgs[2][6] = *(int *)&x1;
	VMArgs[2][7] = *(int *)&y1;
	VMArgs[2][8] = *(int *)&z1;
	VMArgs[2][9] = unk1;
	VMArgs[2][10] = unk2;
	VMArgs[2][11] = unk3;
	VMArgs[2][12] = unk4;
	VMArgs[2][13] = unk5;
	VMArgs[2][14] = unk5;
	((void(*)(void *))FindNative(0xEC024237))(VMArgs);
	ResetStack();
}




bool IS_PED_MODEL(int ped, int modelHash) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = modelHash;
	((void(*)(void *))FindNative(0x5F1DDFCB))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}


void NETWORK_SEND_TEXT_MESSAGE(char *message, int player) {
	SaveStack();
	VMArgs[2][0] = (char)message;
	VMArgs[2][1] = player;
	((void(*)(void *))FindNative(0xAFFEA720))(VMArgs);
	ResetStack();
}

void detach_entity(int entity) {
	SaveStack();
	VMArgs[2][0] = entity;
	VMArgs[2][1] = 0;
	VMArgs[2][2] = 0;
	((void(*)(void *))FindNative(0xC8EFCB41))(VMArgs);
	ResetStack();
}

void DETACH_ENTITY_CUSTOM(int car0, int car1, BOOL p1, BOOL p2) {
	VMArgs[2][0] = car0;
	VMArgs[2][1] = car1;
	VMArgs[2][1] = p1;
	VMArgs[2][2] = p2;
	((void(*)(void *))FindNative(0xC8EFCB41))(VMArgs);
}

void set_swim_speed_multiplier(int index, float multiplier) {
	SaveStack();
	VMArgs[2][0] = index;
	VMArgs[2][1] = *(int *)&multiplier;
	((void(*)(void *))FindNative(0xB986FF47))(VMArgs);
	ResetStack();
}

void set_move_speed_multiplier(int index, float multiplier) {
	SaveStack();
	VMArgs[2][0] = index;
	VMArgs[2][1] = *(int *)&multiplier;
	((void(*)(void *))FindNative(0x825423C2))(VMArgs);
	ResetStack();
}

void set_explosive_ammo_this_frame(int index) {
	SaveStack();
	VMArgs[2][0] = index;
	int(__cdecl *set_explosive_ammo_this_frame)(void *) = (int(__cdecl *)(void *))FindNative(0x2EAFA1D1);
	set_explosive_ammo_this_frame(VMArgs);
	ResetStack();
}


void set_fire_ammo_this_frame(int index) {
	SaveStack();
	VMArgs[2][0] = index;
	int(__cdecl *set_fire_ammo_this_frame)(void *) = (int(__cdecl *)(void *))FindNative(0x7C18FC8A);
	set_fire_ammo_this_frame(VMArgs);
	ResetStack();
}

void set_cube_ammo_this_frame(int index) {
	SaveStack();
	VMArgs[2][0] = index;
	int(__cdecl *set_cube_ammo_this_frame)(void *) = (int(__cdecl *)(void *))FindNative(0xFFFFFFFFC3F13FCC);
	set_cube_ammo_this_frame(VMArgs);
	ResetStack();
}

void set_explosive_melee_this_frame(int index) {
	SaveStack();
	VMArgs[2][0] = index;
	int(__cdecl *set_explosive_melee_this_frame)(void *) = (int(__cdecl *)(void *))FindNative(0x96663D56);
	set_explosive_melee_this_frame(VMArgs);
	ResetStack();
}

void set_super_jump_this_frame(int index) {
	SaveStack();
	VMArgs[2][0] = index;
	int(__cdecl *set_super_jump_this_frame)(void *) = (int(__cdecl *)(void *))FindNative(0x86745EF3);
	set_super_jump_this_frame(VMArgs);
	ResetStack();
}

bool is_entity_attached(int entity) {
	SaveStack();
	VMArgs[2][0] = entity;
	((void(*)(void *))FindNative(0xEC1479D5))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

bool is_entity_in_water(int entity) {
	SaveStack();
	VMArgs[2][0] = entity;
	((void(*)(void *))FindNative(0x4C3C2508))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}


void wait(int time) {
	SaveStack();
	VMArgs[2][0] = time;
	((void(*)(void *))FindNative(0x7715C03B))(VMArgs);
	ResetStack();
}

bool is_entity_visible(int entity) {
	SaveStack();
	VMArgs[2][0] = entity;
	((void(*)(void *))FindNative(0x120B4ED5))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void set_vehicle_doors_locked(int entity, int LockStatus) {
	SaveStack();
	VMArgs[2][0] = entity;
	VMArgs[2][1] = LockStatus;
	((void(*)(void *))FindNative(0x4CDD35D0))(VMArgs);
	ResetStack();
}


void set_entity_collision(int entity, bool collision) {
	SaveStack();
	VMArgs[2][0] = entity;
	VMArgs[2][1] = collision;
	VMArgs[2][2] = 0;
	((void(*)(void *))FindNative(0x139FD37D))(VMArgs);
	ResetStack();
}

bool request_script(char* script) {
	SaveStack();
	VMArgs[2][0] = (DWORD)script;
	((void(*)(void *))FindNative(0xE26B2666))(VMArgs);
	ResetStack();
	return ((int)(*VMArgs[0]) != 0);
}

bool does_script_exist(char* script) {
	SaveStack();
	VMArgs[2][0] = (DWORD)script;
	((void(*)(void *))FindNative(0xDEAB87AB))(VMArgs);
	ResetStack();
	return ((int)(*VMArgs[0]) != 0);
}

void terminate_all_scripts_with_this_name(char* script) {
	SaveStack();
	VMArgs[2][0] = (DWORD)script;
	((void(*)(void *))FindNative(0x9F861FD4))(VMArgs);
	ResetStack();
}

bool has_script_loaded(char* script) {
	SaveStack();
	VMArgs[2][0] = (DWORD)script;
	((void(*)(void *))FindNative(0x5D67F751))(VMArgs);
	ResetStack();
	return ((int)(*VMArgs[0]) != 0);
}

bool start_new_script(char* script, int arg) {
	SaveStack();
	VMArgs[2][0] = (DWORD)script;
	VMArgs[2][1] = arg;
	((void(*)(void *))FindNative(0x3F166D0E))(VMArgs);
	ResetStack();
	return ((int)(*VMArgs[0]) != 0);
}

void set_script_as_no_longer_needed(char* script) {
	SaveStack();
	VMArgs[2][0] = (DWORD)script;
	((void(*)(void *))FindNative(0x6FCB7795))(VMArgs);
	ResetStack();
}

int get_vehicle_max_number_of_passengers(int vehicle) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	((void(*)(void *))FindNative(0x0A2FC08C))(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

bool is_vehicle_seat_free(int vehicle, int seat) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = seat;
	((void(*)(void *))FindNative(0xDAF42B02))(VMArgs);
	ResetStack();
	return ((int)(*VMArgs[0]) != 0);
}
void freeze_entity_position(int entity, bool frozen) {
	SaveStack();
	VMArgs[2][0] = entity;
	VMArgs[2][1] = frozen;
	((void(*)(void *))FindNative(0x65C16D57))(VMArgs);
	ResetStack();
}

int unk_0xDB718B21(int vehicle, char* string, int unk) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = (int)string;
	VMArgs[2][2] = unk;
	((void(*)(void *))FindNative(0xDB718B21))(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}
void task_warp_ped_into_vehicle(int ped, int vehicle, int seat) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = vehicle;
	VMArgs[2][2] = seat;
	((void(*)(void *))FindNative(0x65D4A35D))(VMArgs);
	ResetStack();
}



BOOL IS_PLAYER_TARGETTING_ENTITY(int player, int entity) {
	VMArgs[2][0] = player;
	VMArgs[2][1] = entity;
	((void(*)(void*))FindNative(0xF3240B77))(VMArgs);
	return VMArgs[0][0];
}


void GiveWeaponDelayed(int playerid, int weapon, int ammo, int unk) {
	SaveStack();
	VMArgs[2][0] = playerid;
	VMArgs[2][1] = weapon;
	VMArgs[2][2] = ammo;
	VMArgs[2][3] = unk;

	((void(*)(void *))FindNative(0x5868D20D))(VMArgs);
	ResetStack();
}

void unk_0xD3850671(int handle, int unk) {
	SaveStack();
	VMArgs[2][0] = handle;
	VMArgs[2][1] = unk;

	((void(*)(void *))FindNative(0xD3850671))(VMArgs);
	ResetStack();
}

void unk_0x06BB5CDA(char* Name) {
	SaveStack();
	VMArgs[2][0] = (int)Name;

	((void(*)(void *))FindNative(0x06BB5CDA))(VMArgs);
	ResetStack();
}

void unk_0x1D980479(char* Name, int unk, int unk2) {
	SaveStack();
	VMArgs[2][0] = (int)Name;
	VMArgs[2][1] = unk;
	VMArgs[2][2] = unk2;

	((void(*)(void *))FindNative(0x1D980479))(VMArgs);
	ResetStack();
}

void set_ped_component_variation(int ped, int unk, int unk1, int unk2, int unk3) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = unk;
	VMArgs[2][2] = unk1;
	VMArgs[2][3] = unk2;
	VMArgs[2][4] = unk3;

	((void(*)(void *))FindNative(0xD4F7B05C))(VMArgs);
	ResetStack();
}

void set_vehicle_door_open(int veh, int door) {
	SaveStack();
	VMArgs[2][0] = veh;
	VMArgs[2][1] = door;

	((void(*)(void *))FindNative(0xBB75D38B))(VMArgs);
	ResetStack();
}
void set_vehicle_window_tint(int veh, int tint) {
	SaveStack();
	VMArgs[2][0] = veh;
	VMArgs[2][1] = tint;

	((void(*)(void *))FindNative(0x497C8787))(VMArgs);
	ResetStack();
}
void set_vehicle_tyre_smoke_color(int vehicle, int r, int g, int b) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = r;
	VMArgs[2][2] = g;
	VMArgs[2][3] = b;
	((void(*)(void *))FindNative(0x3EDEC0DB))(VMArgs);
	ResetStack();
}

bool is_ped_shooting(int ped) {
	DWORD VM[1] = { ped };
	int Out;
	DWORD *VMArgsAlt[3] = {
	(DWORD*)&Out, // our return value
	(DWORD*)1, //num of args
	VM
	};
	((void(*)(void *))FindNative(0xE7C3405E))(VMArgsAlt);
	return Out != 0;
}

void get_gameplay_cam_rot(int rot, float* Out) {
	DWORD VM[1] = { rot };
	DWORD *VMArgsAlt[3] = {
	(DWORD*)Out, // our return value
	(DWORD*)1, //num of args
	VM
	};
	((void(*)(void *))FindNative(0x13A010B5))(VMArgsAlt);
}

void get_gameplay_cam_coord(float* Out) {
	DWORD VM[1] = { 0 };
	DWORD *VMArgsAlt[3] = {
	(DWORD*)Out, // our return value
	(DWORD*)1, //num of args
	VM
	};
	((void(*)(void *))FindNative(0x9388CF79))(VMArgsAlt);
}

float* get_coord_in_front_of_gameplaycam(float range, float* OutCoords) {
	float cam_rot[3],
		cam_coord[3],
		adj;

	get_gameplay_cam_rot(2, cam_rot);
	get_gameplay_cam_coord(cam_coord);
	adj = range * cos(cam_rot[0]);

	OutCoords[0] = (adj * sin(cam_rot[2] * -1.0f)) + cam_coord[0];//x plane
	OutCoords[1] = (adj * cos(cam_rot[2] * -1.0f)) + cam_coord[1];//y plane
	OutCoords[2] = (range * sin(cam_rot[0])) + cam_coord[2];//z plane
	return OutCoords;
}

void draw_light_with_range(float x, float y, float z, int r, int g, int b, float rangemin, float rangemax) {
	SaveStack();
	VMArgs[2][0] = *(DWORD *)&(x);
	VMArgs[2][1] = *(DWORD *)&(y);
	VMArgs[2][2] = *(DWORD *)&(z);
	VMArgs[2][3] = r;
	VMArgs[2][4] = g;
	VMArgs[2][5] = b;
	VMArgs[2][6] = *(DWORD *)&(rangemin);
	VMArgs[2][7] = *(DWORD *)&(rangemax);
	((void(*)(void *))FindNative(0x6A396E9A))(VMArgs);
	ResetStack();
}
void set_vehicle_door_broken(int vehicle, int unk, int unk2) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = unk;
	VMArgs[2][2] = unk2;

	((void(*)(void *))FindNative(0x8147FEA7))(VMArgs);
	ResetStack();
} // 
//

void toggle_vehicle_mod(int vehicle, int index, bool toggle) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = index;
	VMArgs[2][2] = toggle;
	((void(*)(void *))FindNative(0xD095F811))(VMArgs);
	ResetStack();
}

void REMOVE_WEAPON_FROM_PED(int ped, int weapon) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = weapon;
	((void(*)(void *))FindNative(0x9C37F220))(VMArgs);
	ResetStack();
}


void remove_vehicle_mod(int vehicle, int index) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = index;
	((void(*)(void *))FindNative(0x9CC80A43))(VMArgs);
	ResetStack();
}//

void set_vehicle_tyres_can_burst(int vehicle, bool pop) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = pop;
	((void(*)(void *))FindNative(0xA198DB54))(VMArgs);
	ResetStack();
}//

void set_vehicle_wheel_type(int vehicle, int type) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = type;
	((void(*)(void *))FindNative(0x64BDAAAD))(VMArgs);
	ResetStack();
}//

void set_vehicle_mod_kit(int vehicle, int unk) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = unk;

	((void(*)(void *))FindNative(0xB8132158))(VMArgs);
	ResetStack();
} // 

void set_vehicle_mod(int vehicle, int mod, int index, int var) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = mod;
	VMArgs[2][2] = index;
	VMArgs[2][3] = var;
	((void(*)(void *))FindNative(0xB52E5ED5))(VMArgs);
	ResetStack();
}

BOOL NETWORK_IS_PLAYER_TALKING_CUSTOM(int player) {
	VMArgs[2][0] = player;
	((void(*)(void*))FindNative(0xDA9FD9DB))(VMArgs);
	return VMArgs[0][0];
}

BOOL NETWORK_AM_I_MUTED_BY_PLAYER(int player) {
	VMArgs[2][0] = player;
	((void(*)(void*))FindNative(0xE128F2B0))(VMArgs);
	return VMArgs[0][0];
}

void SET_SEETHROUGH(BOOL Toggle) {
	VMArgs[2][0] = Toggle;
	((void(__cdecl *)(void *))FindNative(0x74D4995C))(VMArgs);
}

void SET_NIGHTVISION(BOOL Toggle) {
	VMArgs[2][0] = Toggle;
	((void(__cdecl *)(void *))FindNative(0xD1E5565F))(VMArgs);
}

void _CREATE_LIGHTNING_THUNDER() {}
void SetUpWhiteDraw() {
	SET_TEXT_OUTLINE(); //MAYBE NAH
	SET_TEXT_FONT(0);
	SET_TEXT_SCALE(0.50f, 0.50f);
	SET_TEXT_WRAP(0, 1);
	SET_TEXT_CENTRE(1);
	SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	SET_TEXT_EDGE(0, 0, 0, 0, 0);
}

VOID SET_TEXT_OUTLINE() {
	((VOID(*)(PVOID))FindNative(0xC753412F))(VMArgs);
}

VOID SET_TEXT_FONT(INT Font) {
	VMArgs[2][0] = Font;
	((VOID(*)(PVOID))FindNative(0x80BC530D))(VMArgs);
}

void CLEAR_ALL_PED_PROPS(int ped) {
	VMArgs[2][0] = ped;
	((VOID(*)(PVOID))FindNative(0x81DF8B43))(VMArgs);
}

void CLEAR_PED_PROP(int ped, int propId) {
	VMArgs[2][0] = ped;
	VMArgs[2][1] = propId;
	((VOID(*)(PVOID))FindNative(0x2D23D743))(VMArgs);
}


void DisplayText(char *text, float X2d, float Y2d) {
	SetUpWhiteDraw();
	SET_TEXT_FONT(0);
	_0x3E35563E("STRING");
	SET_TEXT_COLOUR(255, 255, 255, 255);
	_0x27A244D8(text);
	_0x6F8350CE(X2d, Y2d);
}

VOID SET_TEXT_SCALE(FLOAT X, FLOAT Y) {
	VMArgs[2][0] = *(DWORD*)(&X);
	VMArgs[2][1] = *(DWORD*)(&Y);
	((VOID(*)(PVOID))FindNative(0xB6E15B23))(VMArgs);
}

VOID SET_TEXT_WRAP(FLOAT X, FLOAT Y) {
	VMArgs[2][0] = *(DWORD*)(&X);
	VMArgs[2][1] = *(DWORD*)(&Y);
	((VOID(*)(PVOID))FindNative(0x6F60AB54))(VMArgs);
}

VOID SET_TEXT_CENTRE(INT Value) {
	VMArgs[2][0] = Value;
	((VOID(*)(PVOID))FindNative(0xE26D39A1))(VMArgs);
}

VOID SET_TEXT_DROPSHADOW(INT r1, INT r2, INT r3, INT r4, INT r5) {
	VMArgs[2][0] = r1;
	VMArgs[2][1] = r2;
	VMArgs[2][2] = r3;
	VMArgs[2][3] = r4;
	VMArgs[2][4] = r5;
	((VOID(*)(PVOID))FindNative(0xE6587517))(VMArgs);
}

VOID SET_TEXT_EDGE(INT r1, INT r2, INT r3, INT r4, INT r5) {
	VMArgs[2][0] = r1;
	VMArgs[2][1] = r2;
	VMArgs[2][2] = r3;
	VMArgs[2][3] = r4;
	VMArgs[2][4] = r5;
	((VOID(*)(PVOID))FindNative(0x3F1A5DAB))(VMArgs);
}


VOID SET_TEXT_COLOUR(BYTE R, BYTE G, BYTE B, BYTE A) {
	VMArgs[2][0] = R;
	VMArgs[2][1] = G;
	VMArgs[2][2] = G;
	VMArgs[2][3] = A;
	((VOID(*)(PVOID))FindNative(0xE54DD2C8))(VMArgs);
}



void set_entity_as_no_longer_needed(int entity) {
	SaveStack();
	VMArgs[2][0] = (DWORD)&entity;
	((void(*)(void *))FindNative(0x3F6B949F))(VMArgs);
	ResetStack();
}

void delete_vehicle(int vehicle) {
	SaveStack();
	VMArgs[2][0] = (DWORD)&vehicle;
	((void(*)(void *))FindNative(0x9803AF60))(VMArgs);
	ResetStack();
}

void delete_vehicle2(int *vehicle) {
	SaveStack();
	VMArgs[2][0] = (DWORD)vehicle;
	((void(*)(void *))FindNative(0x9803AF60))(VMArgs);
	ResetStack();
}

void delete_object(int object) {
	SaveStack();
	VMArgs[2][0] = (DWORD)&object;
	((void(*)(void *))FindNative(0xD6EF9DA7))(VMArgs);
	ResetStack();
}

void delete_object2(int *object) {
	SaveStack();
	VMArgs[2][0] = (DWORD)object;
	((void(*)(void *))FindNative(0xD6EF9DA7))(VMArgs);
	ResetStack();
}



//

void set_vehicle_as_no_longer_needed(int vehicle) {
	SaveStack();
	VMArgs[2][0] = (DWORD)&vehicle;
	((void(*)(void *))FindNative(0x9B0E10BE))(VMArgs);
	ResetStack();
}

void clear_weather_type_persist() {
	((void(*)())FindNative(0x6AB757D8))();
}

void PopCarTyre(int vehicle, int tyre, bool r2, float r3) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = tyre;
	VMArgs[2][2] = r2;
	VMArgs[2][3] = *(DWORD *)&(r3);
	((void(*)(void *))FindNative(0x89D28068))(VMArgs);
	ResetStack();
}

bool IS_VEHICLE_TYRE_BURST(int vehicle, int wheelID, bool p2) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = wheelID;
	VMArgs[2][2] = p2;
	((void(*)(void *))FindNative(0x48C80210))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void SET_VEHICLE_TYRES_CAN_BURST(int vehicle, BOOL value) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][0] = value;
	((void(*)(void *))FindNative(0xA198DB54))(VMArgs);
	ResetStack();
}
// 0xEB9DC3C7D8596C46 0xA198DB54

void set_weather_type_now_persist(char* weather) {
	SaveStack();
	VMArgs[2][0] = (int)weather;
	((void(*)(void *))FindNative(0xC869FE97))(VMArgs);
	ResetStack();
}

void delete_entity(int entity) {
	SaveStack();
	VMArgs[2][0] = (DWORD)&entity;
	((void(*)(void *))FindNative(0xFAA3D236))(VMArgs);
	ResetStack();
}

void ExplodeNetworkCar(int vehicle, boolean unknownTrue, boolean unknownFalse) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = unknownTrue;
	VMArgs[2][2] = unknownFalse;

	((void(*)(void *))FindNative(0x0E1B38AE))(VMArgs);
	ResetStack();
}

char *GetPlayerName(int index) {

	char* Return;
	DWORD VM[] = { index };

	DWORD *VMArgsAlt[3] = {
	(DWORD*)&Return, // our return value
	(DWORD*)1,//num of args
	VM
	};

	((void(*)(void *))FindNative(0x406B4B20))(VMArgsAlt);
	return Return;
}

int NetworkIsPlayerActive(int index) {
	return 0;
}


bool get_current_ped_weapon(int PedHandle, int* OutWeaponHash, bool unk) {
	SaveStack();
	VMArgs[2][0] = PedHandle;
	VMArgs[2][1] = (int)OutWeaponHash;
	VMArgs[2][2] = unk;
	((void(*)(void *))FindNative(0xB8278882))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

bool has_entity_been_damaged_by_entity(int PedHandle, int pedhandle2, bool unk) {
	SaveStack();
	VMArgs[2][0] = PedHandle;
	VMArgs[2][1] = pedhandle2;
	VMArgs[2][2] = unk;
	((void(*)(void *))FindNative(0x07FC77E0))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

int get_current_weapon_hash() {
	((void(__cdecl *)(void *))FindNative(0xE495B6DA))(VMArgs);
	return (int)VMArgs[0][0];
}

void GET_PED_LAST_WEAPON_IMPACT_COORD(int PedID, float* Out) {
	SaveStack();
	VMArgs[2][0] = PedID;
	VMArgs[2][1] = (int)Out;
	((void(*)(void *))FindNative(0x9B266079))(VMArgs);
	ResetStack();

	memcpy(Out, VMArgs[0], 0xC);
}

bool has_ped_been_damaged_by_weapon(int PedHandle, int weapon, bool unk) {
	SaveStack();
	VMArgs[2][0] = PedHandle;
	VMArgs[2][1] = weapon;
	VMArgs[2][2] = unk;
	((void(*)(void *))FindNative(0xCDFBBCC6))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void SET_PLAYER_TARGETING_MODE(int index) {
	SaveStack();
	VMArgs[2][0] = index;
	((void(*)(void *))FindNative(0x61CAE253))(VMArgs);
	ResetStack();
}
void SetPlayerInvincible(int index, bool active) {
	SaveStack();
	VMArgs[2][0] = index;
	VMArgs[2][1] = active;

	int(__cdecl *set_player_invincible)(void *) = (int(__cdecl *)(void *))FindNative(0xDFB9A2A2);
	set_player_invincible(VMArgs);
	ResetStack();
}

void set_entity_proofs(int entity, bool active, bool active2, bool active3, bool active4, bool active5, bool active6, bool active7, bool active8) {
	SaveStack();
	VMArgs[2][0] = entity;
	VMArgs[2][1] = active;
	VMArgs[2][2] = active2;
	VMArgs[2][3] = active3;
	VMArgs[2][4] = active4;
	VMArgs[2][5] = active5;
	VMArgs[2][6] = active6;
	VMArgs[2][7] = active7;
	VMArgs[2][8] = active8;

	((void(__cdecl *)(void *))FindNative(0x7E9EAB66))(VMArgs);
	ResetStack();
}

void set_ped_infinite_ammo(int index, bool active) {
	SaveStack();
	VMArgs[2][0] = index;
	VMArgs[2][1] = active;

	int(__cdecl *set_ped_infinite_ammo)(void *) = (int(__cdecl *)(void *))FindNative(0x9CB8D278);
	set_ped_infinite_ammo(VMArgs);
	ResetStack();
}

void set_ped_infinite_ammo_clip(int ped, bool active) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = active;

	int(__cdecl *set_ped_infinite_ammo_clip)(void *) = (int(__cdecl *)(void *))FindNative(0x5A5E3B67);
	set_ped_infinite_ammo_clip(VMArgs);
	ResetStack();
}



void FixCar(int carhandle) {
	SaveStack();
	VMArgs[2][0] = carhandle;

	int(__cdecl *set_vehicle_fixed)(void *) = (int(__cdecl *)(void *))FindNative(0x17469AA1);
	set_vehicle_fixed(VMArgs);
	ResetStack();
}

void unk_0x90D3A0D9(int vehicle, bool unk) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = unk;
	((void(__cdecl *)(void *))FindNative(0x90D3A0D9))(VMArgs);
	ResetStack();
}

void set_number_plate(int Vehicle, char* Text) {
	SaveStack();
	VMArgs[2][0] = Vehicle;
	VMArgs[2][1] = (DWORD)Text;

	((void(__cdecl *)(void *))FindNative(0x400F9556))(VMArgs);
	ResetStack();
}

bool is_string_null_or_empty(char* string) {
	SaveStack();
	VMArgs[2][0] = (DWORD)string;

	((void(__cdecl *)(void *))FindNative(0x42E9F2CA))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void display_onscreen_keyboard(int arg0, char* str0, char* str1, char* str2, char* str3, char* str4, int arg1) {
	SaveStack();
	VMArgs[2][0] = arg0;
	VMArgs[2][1] = (int)str0;
	VMArgs[2][2] = (int)str1;
	VMArgs[2][3] = (int)str2;
	VMArgs[2][4] = (int)str3;
	VMArgs[2][5] = (int)str4;
	VMArgs[2][6] = arg1;
	((void(__cdecl *)(void *))FindNative(0xAD99F2CE))(VMArgs);
	ResetStack();
}

void unk_0x27A244D8(char* String) {
	SaveStack();
	VMArgs[2][0] = (int)String;
	((void(__cdecl *)(void *))FindNative(0x27A244D8))(VMArgs);
	ResetStack();
}

void unk_0x38F82261(int Time, int unk) {
	SaveStack();
	VMArgs[2][0] = Time;
	VMArgs[2][1] = unk;
	((void(__cdecl *)(void *))FindNative(0x38F82261))(VMArgs);
	ResetStack();
}

void unk_0xF42C43C7(char* String) {
	SaveStack();
	VMArgs[2][0] = (int)String;
	((void(__cdecl *)(void *))FindNative(0xF42C43C7))(VMArgs);
	ResetStack();
}

void set_player_wanted_level(int playerid, int wantedstars) {
	SaveStack();
	VMArgs[2][0] = playerid;
	VMArgs[2][1] = wantedstars;
	VMArgs[2][2] = 0;
	((void(__cdecl *)(void *))FindNative(0xB7A0914B))(VMArgs);
	ResetStack();
}

void set_entity_invincible(int entity, bool invincible) {
	SaveStack();
	VMArgs[2][0] = entity;
	VMArgs[2][1] = invincible;
	((void(__cdecl *)(void *))FindNative(0xC1213A21))(VMArgs);
	ResetStack();
}

//set_entity_invincible

bool is_vehicle_on_all_wheels(int vehicle) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	((void(__cdecl *)(void *))FindNative(0x10089F8E))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void set_player_wanted_level_now(int playerid, int wantedstars) {
	SaveStack();
	VMArgs[2][0] = playerid;
	VMArgs[2][1] = wantedstars;
	VMArgs[2][2] = 0;
	((void(__cdecl *)(void *))FindNative(0xAF3AFD83))(VMArgs);
	ResetStack();
}
void set_cops_on_player(int player, int stars) {
	//48A18913
	SaveStack();
	VMArgs[2][0] = (int)player;
	VMArgs[2][1] = (int)stars;
	((void(__cdecl *)(void *))FindNative(0x48A18913))(VMArgs);
	ResetStack();
}

bool is_system_ui_being_displayed() {
	((void(__cdecl *)(void *))FindNative(0xE495B6DA))(VMArgs);
	return VMArgs[0][0] != 0;
}

char* get_onscreen_keyboard_result() {
	((void(__cdecl *)(void *))FindNative(0x44828FB3))(VMArgs);
	return (char*)VMArgs[0][0];
}
bool is_ped_in_any_vehicle(int ped) {
	int Return;
	DWORD VM[] = { ped, 0 };

	DWORD *VMArgsAlt[3] = {
	(DWORD*)&Return, // our return value
	(DWORD*)1,//num of args
	VM
	};
	((void(__cdecl *)(void *))FindNative(0x3AC90869))(VMArgsAlt);
	return VMArgs[0][0] != 0;
}

bool IsEntityVehicle(int entity) {
	SaveStack();
	VMArgs[2][0] = entity;

	int(__cdecl *is_entity_a_vehicle)(void *) = (int(__cdecl *)(void *))FindNative(0xBE800B01);
	is_entity_a_vehicle(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

bool IsEntityObject(int entity) {
	SaveStack();
	VMArgs[2][0] = entity;

	int(__cdecl *is_entity_a_object)(void *) = (int(__cdecl *)(void *))FindNative(0x3F52E561);
	is_entity_a_object(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void AddExplosion1(float X, float Y, float Z, int ExplosionType, float radius, bool playsound, bool novisual, float Camshake) {
	SaveStack();
	VMArgs[2][0] = *(DWORD *)&(X);
	VMArgs[2][1] = *(DWORD *)&(Y);
	VMArgs[2][2] = *(DWORD *)&(Z);
	VMArgs[2][3] = ExplosionType;
	VMArgs[2][4] = *(DWORD *)&(radius);
	VMArgs[2][5] = playsound ? 1 : 0;
	VMArgs[2][6] = novisual ? 1 : 0;
	VMArgs[2][7] = *(DWORD *)&(Camshake);
	((void(*)(void *))FindNative(0x10AF5258))(VMArgs);
	ResetStack();
}

void AddExplosion(float X, float Y, float Z, int ExplosionType, float radius, bool playsound, bool novisual, float camshake) {
	SaveStack();
	VMArgs[2][0] = *(DWORD *)&(X);
	VMArgs[2][1] = *(DWORD *)&(Y);
	VMArgs[2][2] = *(DWORD *)&(Z);
	VMArgs[2][3] = ExplosionType;
	VMArgs[2][4] = *(DWORD *)&(radius);
	VMArgs[2][5] = playsound ? 1 : 0;
	VMArgs[2][6] = novisual ? 1 : 0;
	VMArgs[2][7] = *(DWORD *)&(camshake);
	((void(*)(void *))FindNative(0x10AF5258))(VMArgs);
	ResetStack();
}

bool network_has_control_of_entity(int entity) {
	SaveStack();
	VMArgs[2][0] = entity;
	((void(*)(void *))FindNative(0x005FD797))(VMArgs);
	ResetStack();
	return ((int)(*VMArgs[0]) != 0);
}

bool network_has_control_of_network_id(int id) {
	SaveStack();
	VMArgs[2][0] = id;
	((void(*)(void *))FindNative(0x92E77D21))(VMArgs);
	ResetStack();
	return ((int)(*VMArgs[0]) != 0);
}

void network_session_kick_player(int playerindex) {
	SaveStack();
	VMArgs[2][0] = playerindex;
	((void(*)(void *))FindNative(0x1E20138A))(VMArgs);
	ResetStack();
}

bool network_does_network_id_exist(int id) {
	SaveStack();
	VMArgs[2][0] = id;
	((void(*)(void *))FindNative(0x1E2E3177))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void set_network_id_exists_on_all_machines(int netid, int unk) {
	SaveStack();
	VMArgs[2][0] = netid;
	VMArgs[2][1] = unk;
	((void(*)(void *))FindNative(0x68D486B2))(VMArgs);
	ResetStack();
}

void SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(int vehicle, int r, int g, int b) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = r;
	VMArgs[2][2] = g;
	VMArgs[2][3] = b;
	((void(*)(void *))FindNative(0x8DF9F9BC))(VMArgs);
	ResetStack();
}

void MODIFY_WATER(float x, float y, float z, float height) {
	SaveStack();
	VMArgs[2][0] = *(DWORD *)&(x);
	VMArgs[2][1] = *(DWORD *)&(y);
	VMArgs[2][2] = *(DWORD *)&(z);
	VMArgs[2][3] = *(DWORD *)&(height);
	((void(*)(void *))FindNative(0xC49E005A))(VMArgs);
	ResetStack();
}

void SET_PED_WEAPON_TINT_INDEX(int playerid, int weapon, int colorIndex) {
	SaveStack();
	VMArgs[2][0] = playerid;
	VMArgs[2][1] = weapon;
	VMArgs[2][2] = colorIndex;
	((void(*)(void *))FindNative(0xEB2A7B23))(VMArgs);
	ResetStack();
}
void TASK_START_SCENARIO_IN_PLACE(int playerid, char *scenarioName, int unk, bool playEnterAnim) {
	SaveStack();
	VMArgs[2][0] = playerid;
	VMArgs[2][1] = (int)scenarioName;
	VMArgs[2][2] = unk;
	VMArgs[2][3] = playEnterAnim;
	((void(*)(void *))FindNative(0xE50D6DDE))(VMArgs);
	ResetStack();
}

bool network_request_control_of_entity(int entity) {
	SaveStack();
	VMArgs[2][0] = entity;
	((void(*)(void *))FindNative(0xA05FEBD7))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

int network_request_control_of_network_id(int id) {
	SaveStack();
	VMArgs[2][0] = id;
	((void(*)(void *))FindNative(0x9262A60A))(VMArgs);
	ResetStack();
	return (int)VMArgs[0][0];
}

int network_get_network_id_from_entity(int entity) {
	SaveStack();
	VMArgs[2][0] = entity;
	((void(*)(void *))FindNative(0x9E35DAB6))(VMArgs);
	ResetStack();
	return (int)VMArgs[0][0];
}

bool network_is_player_active(int player) {
	SaveStack();
	VMArgs[2][0] = player;
	((void(*)(void *))FindNative(0x43657B17))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;

}

//task_follow_nav_mesh_to_coord(theirPedHandle, GetEntityCoords(myPedHandle, Pos), 1.0f, -1, 1048576000, 0, 1193033728);
void task_follow_nav_mesh_to_coord(int ped, float x, float y, float z, float unk, int unk1, int unk2, int unk3, int unk4) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = *(DWORD *)&(x);
	VMArgs[2][2] = *(DWORD *)&(y);
	VMArgs[2][3] = *(DWORD *)&(z);
	VMArgs[2][4] = *(DWORD *)&(unk);
	VMArgs[2][5] = unk1;
	VMArgs[2][6] = unk2;
	VMArgs[2][7] = unk3;
	VMArgs[2][8] = unk4;
	((void(*)(void *))FindNative(0xFE4A10D9))(VMArgs);
	ResetStack();
}

//task_play_anim(playerPedHandle, animDictName, animName, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0); 
bool set_ped_can_play_gesture_anims(int ped, bool active) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = active;

	int(__cdecl *set_ped_can_play_gesture_anims)(void *) = (int(__cdecl *)(void *))FindNative(0xE131E3B3);
	set_ped_can_play_gesture_anims(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

bool set_ped_can_play_ambient_anims(int ped, bool active) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = active;

	int(__cdecl *set_ped_can_play_ambient_anims)(void *) = (int(__cdecl *)(void *))FindNative(0xF8053081);
	set_ped_can_play_ambient_anims(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

bool set_ped_can_play_ambient_base_anims(int ped, bool active) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = active;

	int(__cdecl *set_ped_can_play_ambient_base_anims)(void *) = (int(__cdecl *)(void *))FindNative(0x5720A5DD);
	set_ped_can_play_ambient_base_anims(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void task_play_anim(int ped, char *animdict, char *animname, float unk, float unk1, int unk2, int unk3, int unk4, int unk5, int unk6, int unk7) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = (int)animdict;
	VMArgs[2][2] = (int)animname;
	VMArgs[2][3] = *(DWORD *)&(unk);
	VMArgs[2][4] = *(DWORD *)&(unk1);
	VMArgs[2][5] = unk2;
	VMArgs[2][6] = unk3;
	VMArgs[2][7] = unk4;
	VMArgs[2][8] = unk5;
	VMArgs[2][9] = unk6;
	VMArgs[2][10] = unk7;
	((void(*)(void *))FindNative(0x5AB552C6))(VMArgs);
	ResetStack();
}

bool request_anim_set(char *set) {
	SaveStack();
	VMArgs[2][0] = (int)set;
	int(__cdecl *request_anim_set)(void *) = (int(__cdecl *)(void *))FindNative(0x2988B3FC);
	request_anim_set(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}//

void set_override_weather(char *weather) {
	SaveStack();
	VMArgs[2][0] = (int)weather;
	int(__cdecl *set_override_weather)(void *) = (int(__cdecl *)(void *))FindNative(0xD9082BB5);
	set_override_weather(VMArgs);
	ResetStack();
}

bool has_anim_set_loaded(char *set) {
	SaveStack();
	VMArgs[2][0] = (int)set;
	int(__cdecl *has_anim_set_loaded)(void *) = (int(__cdecl *)(void *))FindNative(0x4FFF397D);
	has_anim_set_loaded(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

//unk_0xA817CDEB( player_ped_id(), param_0, 1048576000 );
void unk_0xA817CDEB(int ped, char *anim, int unk) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = (int)anim;
	VMArgs[2][2] = unk;
	int(__cdecl *unk_0xA817CDEB)(void *) = (int(__cdecl *)(void *))FindNative(0xA817CDEB);
	unk_0xA817CDEB(VMArgs);
	ResetStack();

}

void task_aim_gun_at_entity(int ped, int entity, int unk, int unk1) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = entity;
	VMArgs[2][2] = unk;
	VMArgs[2][3] = unk1;
	int(__cdecl *task_aim_gun_at_entity)(void *) = (int(__cdecl *)(void *))FindNative(0xBE32B3B6);
	task_aim_gun_at_entity(VMArgs);
	ResetStack();
}

bool has_entity_clear_los_to_entity(int ped, int entity, int unk) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = entity;
	VMArgs[2][2] = unk;
	int(__cdecl *has_entity_clear_los_to_entity)(void *) = (int(__cdecl *)(void *))FindNative(0x53576FA7);
	has_entity_clear_los_to_entity(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void clear_ped_tasks(int ped) {
	SaveStack();
	VMArgs[2][0] = ped;
	((void(*)(void *))FindNative(0xDE3316AB))(VMArgs);
	ResetStack();
}

void clear_ped_tasks_immediately(int ped) {
	SaveStack();
	VMArgs[2][0] = ped;
	((void(*)(void *))FindNative(0xBC045625))(VMArgs);
	ResetStack();
}


void GetEntityCoords(int entity, float *x, float *y, float *z) {
	float Out[3];
	GetEntityCoords(entity, Out);
	if (x)
		*x = *Out;
	if (y)
		*y = Out[1];
	if (z)
		*z = Out[2];
}



void set_entity_heading(int vehicle, float h) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = *(int *)&h;
	((void(*)(void *))FindNative(0xE0FF064D))(VMArgs);
	ResetStack();
}

void set_entity_coords(int PedID, float X, float Y, float Z, int unk1, int unk2, int unk3, int unk4) {
	SaveStack();
	VMArgs[2][0] = PedID;
	VMArgs[2][1] = *(int *)&X;
	VMArgs[2][2] = *(int *)&Y;
	VMArgs[2][3] = *(int *)&Z;
	VMArgs[2][4] = unk1;
	VMArgs[2][5] = unk2;
	VMArgs[2][6] = unk3;
	VMArgs[2][7] = unk4;

	((void(*)(void *))FindNative(0xDF70B41B))(VMArgs);
	ResetStack();
}

void set_entity_coords3(int PedID, float *x, float *y, float *z, int unk1, int unk2, int unk3, int unk4) {
	SaveStack();
	VMArgs[2][0] = PedID;
	VMArgs[2][1] = (DWORD)x;
	VMArgs[2][2] = (DWORD)y;
	VMArgs[2][3] = (DWORD)z;
	VMArgs[2][4] = unk1;
	VMArgs[2][5] = unk2;
	VMArgs[2][6] = unk3;
	VMArgs[2][7] = unk4;

	((void(*)(void *))FindNative(0xDF70B41B))(VMArgs);
	ResetStack();
}



void task_shuffle_to_next_vehicle_seat(int PedId, int VehId) {
	SaveStack();
	VMArgs[2][0] = PedId;
	VMArgs[2][1] = VehId;
	((void(*)(void *))FindNative(0xBEAF8F67))(VMArgs);
	ResetStack();
}

//set_entity_coords( Entity, x, y, z, 0, 1, 0, 1)

void SetTextFont(int font) {
	SaveStack();
	VMArgs[2][0] = font;

	int(__cdecl *set_text_font)(void *) = (int(__cdecl *)(void *))FindNative(0x80BC530D);
	set_text_font(VMArgs);
	ResetStack();
}

void SetTextScale(float x, float y) {
	SaveStack();
	VMArgs[2][0] = *(DWORD*)(&x);
	VMArgs[2][1] = *(DWORD*)(&y);

	int(__cdecl *set_text_scale)(void *) = (int(__cdecl *)(void *))FindNative(0xB6E15B23);
	set_text_scale(VMArgs);
	ResetStack();
}

void SetTextColor(int a, int r, int g, int b) {
	SaveStack();
	VMArgs[2][0] = a;
	VMArgs[2][1] = r;
	VMArgs[2][2] = g;
	VMArgs[2][3] = b;

	int(__cdecl *set_text_color)(void *) = (int(__cdecl *)(void *))FindNative(0xE54DD2C8);
	set_text_color(VMArgs);
	ResetStack();
}

void SetTextWrap(float x, float y) {
	SaveStack();
	VMArgs[2][0] = *(DWORD*)(&x);
	VMArgs[2][1] = *(DWORD*)(&y);

	int(__cdecl *set_text_wrap)(void *) = (int(__cdecl *)(void *))FindNative(0x6F60AB54);
	set_text_wrap(VMArgs);
	ResetStack();
}

void SetTextCenter(int value) {
	SaveStack();
	VMArgs[2][0] = value;

	int(__cdecl *set_text_center)(void *) = (int(__cdecl *)(void *))FindNative(0xE26D39A1);
	set_text_center(VMArgs);
	ResetStack();
}

void unk_0x3E35563E(char *str) {
	SaveStack();
	VMArgs[2][0] = (DWORD)str;

	int(__cdecl *unk)(void *) = (int(__cdecl *)(void *))FindNative(0x3E35563E);
	unk(VMArgs);
	ResetStack();
}

// Suppose to be the original print but all it did was print ints
void unk_0x12929BDF(DWORD a, DWORD b) {
	SaveStack();
	VMArgs[2][0] = a;
	VMArgs[2][1] = b;

	int(__cdecl *unk)(void *) = (int(__cdecl *)(void *))FindNative(0x12929BDF);
	unk(VMArgs);
	ResetStack();
}

void unk_0x6F8350CE(float x, float y) {
	SaveStack();
	VMArgs[2][0] = *(DWORD*)(&x);
	VMArgs[2][1] = *(DWORD*)(&y);

	int(__cdecl *unk)(void *) = (int(__cdecl *)(void *))FindNative(0x6F8350CE);
	unk(VMArgs);
	ResetStack();
}

void clear_area_of_vehicles(float* Location, float Unk, int Unk2, int Unk3, int Unk4, int Unk5, int Unk6) {
	SaveStack();
	memcpy(VMArgs[2], Location, 0xC);
	VMArgs[2][3] = *(int *)&Unk;
	VMArgs[2][4] = Unk2;
	VMArgs[2][5] = Unk3;
	VMArgs[2][6] = Unk4;
	VMArgs[2][7] = Unk5;
	VMArgs[2][8] = Unk6;

	((void(*)(void*))FindNative(0x63320F3C))(VMArgs);
	ResetStack();
}

bool can_register_mission_vehicles(int Unk) {
	int Return;
	DWORD VM[1] = { Unk };
	DWORD *VMArgsAlt[3] = {
	(DWORD*)&Return, // our return value
	(DWORD*)1,//num of args
	VM
	};
	((void(*)(void*))FindNative(0x818B6830))(VMArgsAlt);
	return Return != 0;
}

void set_ped_random_component_variation(int Ped, int Val) {
	SaveStack();
	VMArgs[2][0] = Ped;
	VMArgs[2][1] = Val;

	((void(*)(void*))FindNative(0x4111BA46))(VMArgs);
	ResetStack();
}
void set_vehicle_door_shut(int veh, int door) {
	SaveStack();
	VMArgs[2][0] = veh;
	VMArgs[2][1] = door;

	((void(*)(void*))FindNative(0x142606BD))(VMArgs);
	ResetStack();
}
void set_ped_into_vehicle(int Ped, int Vehicle, int Seat) {
	SaveStack();
	VMArgs[2][0] = Ped;
	VMArgs[2][1] = Vehicle;
	VMArgs[2][2] = Seat;

	((void(*)(void*))FindNative(0x7500C79))(VMArgs);
	ResetStack();
}
void _STOP_SCREEN_EFFECT(char *effectName) {
	SaveStack();
	VMArgs[2][0] = *effectName;
	((void(*)(void*))FindNative(0x06BB5CDA))(VMArgs);
	ResetStack();
}
//
void set_text_font(int font) {
	SaveStack();
	VMArgs[2][0] = font;
	((void(*)(void*))FindNative(0x80BC530D))(VMArgs);
	ResetStack();
}

void set_vehicle_undriveable(int veh, int driveable) {
	SaveStack();
	VMArgs[2][0] = veh;
	VMArgs[2][1] = driveable;

	((void(*)(void*))FindNative(0x48D02A4E))(VMArgs);
	ResetStack();
}

int GET_PED_PROP_INDEX(int ped, int componentId) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = componentId;
	((void(*)(void*))FindNative(0x746DDAC0))(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

int create_object(int ModelHash, float X, float Y, float Z, int Unk1, int Unk2, int Unk3)// returns the handle
{
	SaveStack();
	VMArgs[2][0] = ModelHash;
	VMArgs[2][1] = *(int *)&X;
	VMArgs[2][2] = *(int *)&Y;
	VMArgs[2][3] = *(int *)&Z;
	VMArgs[2][4] = Unk1;
	VMArgs[2][5] = Unk2;
	VMArgs[2][6] = Unk3;

	((void(*)(void*))FindNative(0x2F7AA05C))(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

bool network_handle_from_player(int player, int FreeMemory, int ArraySize) {
	SaveStack();
	VMArgs[2][0] = player;
	VMArgs[2][1] = (int)FreeMemory;
	VMArgs[2][2] = (int)ArraySize;
	((void(*)(void *))FindNative(0xD3498917));
	ResetStack();
	return VMArgs[0][0] != 0;
}
void network_send_text_message(char* Message, int FreeMemory) {
	SaveStack();
	VMArgs[2][0] = (int)Message;
	VMArgs[2][1] = (int)FreeMemory;
	((void(*)(void *))FindNative(0xAFFEA720));
	ResetStack();
}
int get_ped_bone_index(int ped, int bone) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = bone;
	int(__cdecl *get_ped_bone_index)(void *) = (int(__cdecl *)(void *))FindNative(0x259C6BA2);
	get_ped_bone_index(VMArgs);
	ResetStack();
	return (int)(*VMArgs[0]);
}

void PrintToScreen(char *str, float x, float y, int r, int g, int b, int a, float scaleX, float scaleY, int centerText, int font) {
	SaveStack();
	VMArgs[2][0] = (int)str;

	SetTextFont(font);
	SetTextColor(r, g, b, a);
	SetTextScale(scaleX, scaleY);
	((void(*)(void))FindNative(0xC753412F))();  // Draws outline
	//SetTextWrap(0.0f, 1.0f);
	SetTextCenter(centerText);

	unk_0x3E35563E("STRING");
	extern EncryptedDWORD *printToScreen;
	int(__cdecl *unk)(void *) = (int(__cdecl *)(void *))printToScreen->GetValue(); // isnt hashed so needs to be updated every TU!
	unk(str);

	unk_0x6F8350CE(x, y);
	ResetStack();
}

char printMessageBuffer[256];
void PrintToScreenNum(int number, float x, float y, int r, int g, int b, int a, float scaleX, float scaleY, int centerText, int font) {
	SaveStack();

	sprintf(printMessageBuffer, "%d", number);

	VMArgs[2][0] = (int)printMessageBuffer;

	SetTextFont(font);
	SetTextColor(r, g, b, a);
	SetTextScale(scaleX, scaleY);
	((void(*)(void))FindNative(0xC753412F))();  // Draws outline
	//SetTextWrap(0.0f, 1.0f);
	SetTextCenter(centerText);

	unk_0x3E35563E("STRING");

	extern EncryptedDWORD *printToScreen;
	int(__cdecl *unk)(void *) = (int(__cdecl *)(void *))printToScreen->GetValue(); // isnt hashed so needs to be updated every TU!
	unk(printMessageBuffer);

	unk_0x6F8350CE(x, y);
	ResetStack();
}

void PrintToScreenFloat(float number, float x, float y, int r, int g, int b, int a, float scaleX, float scaleY, int centerText, int font) {
	SaveStack();

	sprintf(printMessageBuffer, "%f", number);

	VMArgs[2][0] = (int)printMessageBuffer;

	SetTextFont(font);
	SetTextColor(r, g, b, a);
	SetTextScale(scaleX, scaleY);
	((void(*)(void))FindNative(0xC753412F))();  // Draws outline
	//SetTextWrap(0.0f, 1.0f);
	SetTextCenter(centerText);

	unk_0x3E35563E("STRING");

	extern EncryptedDWORD *printToScreen;
	int(__cdecl *unk)(void *) = (int(__cdecl *)(void *))printToScreen->GetValue(); // isnt hashed so needs to be updated every TU!
	unk(printMessageBuffer);

	unk_0x6F8350CE(x, y);
	ResetStack();
}


void PaintCar(int carhandle, int paint, int paint1) {
	SaveStack();
	VMArgs[2][0] = carhandle;
	VMArgs[2][1] = paint;
	VMArgs[2][2] = paint1;

	int(__cdecl *set_vehicle_colours)(void *) = (int(__cdecl *)(void *))FindNative(0x57F24253);
	set_vehicle_colours(VMArgs);
	ResetStack();
}


void PaintCarExtra(int carhandle, int paint, int paint1) {
	SaveStack();
	VMArgs[2][0] = carhandle;
	VMArgs[2][1] = paint;
	VMArgs[2][2] = paint1;

	int(__cdecl *set_vehicle_extra_colours)(void *) = (int(__cdecl *)(void *))FindNative(0x515DB2A0);
	set_vehicle_extra_colours(VMArgs);
	ResetStack();
}

int get_entity_model(int handle) {
	SaveStack();
	VMArgs[2][0] = handle;
	int(__cdecl *get_entity_model)(void *) = (int(__cdecl *)(void *))FindNative(0xDAFCB3EC);
	get_entity_model(VMArgs);
	ResetStack();
	return (int)(*VMArgs[0]);
}

int GET_ENTITY_ATTACHED_TO(int entity) {
	SaveStack();
	VMArgs[2][0] = entity;
	int(__cdecl *GET_ENTITY_ATTACHED_TO)(void *) = (int(__cdecl *)(void *))FindNative(0xFE1589F9);
	GET_ENTITY_ATTACHED_TO(VMArgs);
	ResetStack();
	return (int)(*VMArgs[0]);
}

bool is_control_just_pressed(int unk, int control) {
	SaveStack();
	VMArgs[2][0] = unk;
	VMArgs[2][1] = control;
	int(__cdecl *is_control_just_pressed)(void *) = (int(__cdecl *)(void *))FindNative(0x4487F579);
	is_control_just_pressed(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

bool is_vehicle_in_burnout(int veh) {
	SaveStack();
	VMArgs[2][0] = veh;
	int(__cdecl *is_vehicle_in_burnout)(void *) = (int(__cdecl *)(void *))FindNative(0x6632BC12);
	is_vehicle_in_burnout(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void SET_ENTITY_ROTATION2(int PedID, Vector3* Rot) {
	SaveStack();
	VMArgs[2][0] = PedID;
	VMArgs[2][1] = *(DWORD*)(&Rot[0]);
	VMArgs[2][2] = *(DWORD*)(&Rot[1]);
	VMArgs[2][3] = *(DWORD*)(&Rot[2]);

	((void(*)(void *))FindNative(0x0A345EFE))(VMArgs);
	ResetStack();
}

void set_entity_rotation3(int entity, float pitch, float roll, float yaw) {
	SaveStack();
	VMArgs[2][0] = entity;
	VMArgs[2][1] = *(int *)&pitch;
	VMArgs[2][2] = *(int *)&roll;
	VMArgs[2][3] = *(int *)&yaw;

	((void(*)(void *))FindNative(0x0A345EFE))(VMArgs);
	ResetStack();
}//get_entity_pitch

void set_entity_rotation(int entity, float pitch, float roll, float yaw, int unk2, int unk1) {
	SaveStack();
	VMArgs[2][0] = entity;
	VMArgs[2][1] = *(int *)&pitch;
	VMArgs[2][2] = *(int *)&roll;
	VMArgs[2][3] = *(int *)&yaw;
	VMArgs[2][4] = unk2;
	VMArgs[2][5] = unk1;
	((void(*)(void *))FindNative(0x0A345EFE))(VMArgs);
	ResetStack();
}//get_entity_pitch

float get_entity_pitch(int entity) {
	SaveStack();
	VMArgs[2][0] = entity;
	((void(*)(void *))FindNative(0xFCE6ECE5))(VMArgs);
	ResetStack();
	return *(float*)&VMArgs[0][0];
}//

float get_entity_roll(int entity) {
	SaveStack();
	VMArgs[2][0] = entity;
	((void(*)(void *))FindNative(0x36610842))(VMArgs);
	ResetStack();
	return *(float*)&VMArgs[0][0];
}//

static Vector3 retrunVal;

void get_offset_from_entity_in_world_coords(int Handle, float x, float y, float z, float* Out) {
	DWORD VM[4] = { Handle, *(int *)&x, *(int *)&y, *(int *)&z };
	DWORD *VMArgsAlt[3] = {
	(DWORD*)Out, // our return value
	(DWORD*)4,//num of args
	VM
	};

	((void(*)(void *))FindNative(0xABCF043A))(VMArgsAlt);
	//memcmp(Out, VMArgs[0], 0xC);
}

void get_offset_from_entity_in_world_coords2(int Handle, float x, float y, float z) {
	VMArgs[2][0] = Handle;
	VMArgs[2][1] = *(int *)&x;
	VMArgs[2][2] = *(int *)&y;
	VMArgs[2][3] = *(int *)&z;
	((void(*)(void *))FindNative(0xABCF043A))(VMArgs);
}

void TASK_LOOK_AT_COORD(int p0, float x, float y, float z, int p4, int p5, int p6) {
	VMArgs[2][0] = p0;
	VMArgs[2][1] = *(int *)&x;
	VMArgs[2][2] = *(int *)&y;
	VMArgs[2][3] = *(int *)&z;
	VMArgs[2][4] = p4;
	VMArgs[2][5] = p5;
	VMArgs[2][6] = p6;
	((void(*)(void *))FindNative(0x7B784DD8))(VMArgs);
}

float GET_CONTROL_NORMAL(int p0, int p1) {
	VMArgs[2][0] = p0;
	VMArgs[2][1] = p1;
	((void(*)(void *))FindNative(0x5DE226A5))(VMArgs);
	return VMArgs[0][0];
}

int GET_PLAYER_PED(int player) {
	VMArgs[2][0] = player;
	((void(*)(void *))FindNative(0x6E31E993))(VMArgs);
	return VMArgs[0][0];
}

int create_cam(char *cam, int unk) {
	SaveStack();
	VMArgs[2][0] = (int)cam;
	VMArgs[2][1] = unk;
	int(__cdecl *create_cam)(void *) = (int(__cdecl *)(void *))FindNative(0xE9BF2A7D);
	create_cam(VMArgs);
	ResetStack();
	return (int)(*VMArgs[0]);
}
//myCamera, PLAYER_PED_ID(), 31086, 0.0f, 0.15f, 0.002f, true);
void attach_cam_to_ped_bone(int cam, int ped, int boneid, float x, float y, float z, bool unk) {
	SaveStack();
	VMArgs[2][0] = cam;
	VMArgs[2][1] = ped;
	VMArgs[2][2] = boneid;
	VMArgs[2][3] = ped;
	VMArgs[2][4] = *(int *)&x;
	VMArgs[2][5] = *(int *)&y;
	VMArgs[2][6] = *(int *)&z;
	VMArgs[2][7] = unk;
	((void(*)(void *))FindNative(0x506BB35C))(VMArgs);
	ResetStack();
}

BOOL IS_PLAYER_FREE_AIMING_AT_ENTITY(int player, int entity) {
	VMArgs[2][0] = player;
	VMArgs[2][1] = entity;
	((void(*)(void*))FindNative(0x7D80EEAA))(VMArgs);
	return VMArgs[0][0];
}

void render_script_cams(int unk, int unk1, int unk2, int unk3, int unk4) {
	SaveStack();
	VMArgs[2][0] = unk;
	VMArgs[2][1] = unk1;
	VMArgs[2][2] = unk2;
	VMArgs[2][3] = unk3;
	VMArgs[2][4] = unk4;
	((void(*)(void *))FindNative(0x74337969))(VMArgs);
	ResetStack();
}

void set_cam_active(int cam, bool active) {
	SaveStack();
	VMArgs[2][0] = cam;
	VMArgs[2][1] = active;
	((void(*)(void *))FindNative(0x064659C2))(VMArgs);
	ResetStack();
}

void set_cam_rot(int cam, float *vec) {
	SaveStack();
	VMArgs[2][0] = cam;
	memcpy(&VMArgs[2][1], vec, 0xC);
	((void(*)(void *))FindNative(0xEE38B3C1))(VMArgs);
}

void shoot_single_bullet_between_coords(float *i, float *a, int unk, int unk1, int hash, int ped, int unk2, int unk3, float speed) {
	SaveStack();
	memcpy(&VMArgs[2][0], i, 0xC);
	memcpy(&VMArgs[2][3], a, 0xC);
	VMArgs[2][6] = unk;
	VMArgs[2][7] = unk1;
	VMArgs[2][8] = hash;
	VMArgs[2][9] = ped;
	VMArgs[2][10] = unk2;
	VMArgs[2][11] = unk3;
	VMArgs[2][12] = *(int *)&speed;
	((void(*)(void *))FindNative(0xCB7415AC))(VMArgs);
	ResetStack();
}

void SHOOT_SINGLE_BULLET_BETWEEN_COORDS1(float* x, float* y, int unk, int unk1, int hash, int ped, int unk2, int unk3, float speed) {
	SaveStack();
	VMArgs[2][0] = (int)x;
	VMArgs[2][1] = (int)y;
	VMArgs[2][6] = unk;
	VMArgs[2][7] = unk1;
	VMArgs[2][8] = hash;
	VMArgs[2][9] = ped;
	VMArgs[2][10] = unk2;
	VMArgs[2][11] = unk3;
	VMArgs[2][12] = *(int *)&speed;
	((void(*)(void *))FindNative(0xCB7415AC))(VMArgs);
	ResetStack();
}


float get_entity_speed(int handle) {
	SaveStack();
	VMArgs[2][0] = handle;
	int(__cdecl *get_entity_speed)(void *) = (int(__cdecl *)(void *))FindNative(0x9E1E4798);
	get_entity_speed(VMArgs);
	ResetStack();
	return *(float*)&VMArgs[0][0];
}

float get_vehicle_engine_health(int handle) {
	SaveStack();
	VMArgs[2][0] = handle;
	int(__cdecl *get_vehicle_engine_health)(void *) = (int(__cdecl *)(void *))FindNative(0x8880038A);
	get_vehicle_engine_health(VMArgs);
	ResetStack();
	return *(float*)&VMArgs[0][0];
}

bool unk_0x9ACC6446(char *type) {
	SaveStack();
	VMArgs[2][0] = (int)type;
	int(__cdecl *unk_0x9ACC6446)(void *) = (int(__cdecl *)(void *))FindNative(0x9ACC6446);
	unk_0x9ACC6446(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void unk_0xCFEA19A9(char *type) {
	SaveStack();
	VMArgs[2][0] = (int)type;
	int(__cdecl *unk_0xCFEA19A9)(void *) = (int(__cdecl *)(void *))FindNative(0xCFEA19A9);
	unk_0xCFEA19A9(VMArgs);
	ResetStack();
}

void unk_0x9C720B61(char *type) {
	SaveStack();
	VMArgs[2][0] = (int)type;
	int(__cdecl *unk_0x9C720B61)(void *) = (int(__cdecl *)(void *))FindNative(0x9C720B61);
	unk_0x9C720B61(VMArgs);
	ResetStack();
}

void unk_0x7B689E20(float f1, float f2, float f3) {
	SaveStack();
	VMArgs[2][0] = *(int *)&f1;
	VMArgs[2][1] = *(int *)&f2;
	VMArgs[2][2] = *(int *)&f3;
	int(__cdecl *unk_0x7B689E20)(void *) = (int(__cdecl *)(void *))FindNative(0x7B689E20);
	unk_0x7B689E20(VMArgs);
	ResetStack();
}
//unk_0x633F8C48("scr_indep_firework_shotburst", coords[0], coords[1], coords[2], 0.0f, 0.0f, 0.0f, 1.0f, 0, 0, 0);
void unk_0x633F8C48(char *type, float x, float y, float z, float f1, float f2, float f3, float f4, int unk, int unk1, int unk2) {
	SaveStack();
	VMArgs[2][0] = (int)type;
	VMArgs[2][1] = *(int *)&x;
	VMArgs[2][2] = *(int *)&y;
	VMArgs[2][3] = *(int *)&z;
	VMArgs[2][4] = *(int *)&f1;
	VMArgs[2][5] = *(int *)&f2;
	VMArgs[2][6] = *(int *)&f3;
	VMArgs[2][7] = *(int *)&f4;
	VMArgs[2][8] = unk;
	VMArgs[2][9] = unk1;
	VMArgs[2][10] = unk2;
	int(__cdecl *unk_0x633F8C48)(void *) = (int(__cdecl *)(void *))FindNative(0x633F8C48);
	unk_0x633F8C48(VMArgs);
	ResetStack();
}

bool is_control_pressed(int unk, int control) {
	SaveStack();
	VMArgs[2][0] = unk;
	VMArgs[2][1] = control;
	int(__cdecl *is_control_pressed)(void *) = (int(__cdecl *)(void *))FindNative(0x517A4384);
	is_control_pressed(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void task_arrest_ped(int ped, int aimped) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = aimped;
	int(__cdecl *task_arrest_ped)(void *) = (int(__cdecl *)(void *))FindNative(0xBC0F153D);
	task_arrest_ped(VMArgs);
	ResetStack();
}

bool is_control_just_released(int unk, int control) {
	SaveStack();
	VMArgs[2][0] = unk;
	VMArgs[2][1] = control;
	int(__cdecl *is_control_just_released)(void *) = (int(__cdecl *)(void *))FindNative(0x2314444B);
	is_control_just_released(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

//

void task_leave_vehicle(int ped, int veh, int unk) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = veh;
	VMArgs[2][2] = unk;
	int(__cdecl *task_leave_vehicle)(void *) = (int(__cdecl *)(void *))FindNative(0x7B1141C6);
	task_leave_vehicle(VMArgs);
	ResetStack();
}

bool request_anim_dict(char *dict) {
	SaveStack();
	VMArgs[2][0] = (int)dict;
	int(__cdecl *request_anim_dict)(void *) = (int(__cdecl *)(void *))FindNative(0xDCA96950);
	request_anim_dict(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void task_cower(int ped, int unk) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = unk;
	int(__cdecl *task_cower)(void *) = (int(__cdecl *)(void *))FindNative(0x9CF1C19B);
	task_cower(VMArgs);
	ResetStack();
}

bool has_anim_dict_loaded(char *dict) {
	SaveStack();
	VMArgs[2][0] = (int)dict;
	int(__cdecl *has_anim_dict_loaded)(void *) = (int(__cdecl *)(void *))FindNative(0x05E6763C);
	has_anim_dict_loaded(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void load_all_objects_now() {
	((int(*)())FindNative(0xC9DBDA90))();
}

bool get_ground_z_for_3d_coord(float x, float y, float z, float *OutZ) {
	DWORD Out;
	DWORD Args[] = { *(int *)&x, *(int *)&y, *(int *)&z, (int)OutZ };
	DWORD Pointer[] = { (DWORD)&Out, 4, (DWORD)Args };
	void(__cdecl *get_ground_z_for_3d_coord)(void *) = (void(__cdecl *)(void *))FindNative(0xA1BFD5E0);
	get_ground_z_for_3d_coord(Pointer);
	return Out != 0;
}


void Custom_get_model_dimensions(int model, float* Min, float* Max) {
	extern EncryptedDWORD *customGetModelDim;
	printf("%p\n", customGetModelDim);
	printf("%p\n", customGetModelDim->GetValue());
	int Temp = 0xFFFF;
	int ModelPointer = ((int(*)(int, int*))customGetModelDim->GetValue())(model, &Temp),
		r11 = 0x20,
		r10 = 0x30;
	printf("ModelPointer = %p\n", ModelPointer);
	if (ModelPointer == 0)
		return;
	memcpy(Min, (PVOID)(ModelPointer + r11), 0xC);
	memcpy(Max, (PVOID)(ModelPointer + r10), 0xC);
}

void get_model_dimensions(int model, float* Min, float* Max) {
	Custom_get_model_dimensions(model, Min, Max);


}

void reserve_network_mission_vehicles(int vehicles) {
	SaveStack();
	VMArgs[2][0] = vehicles;
	int(__cdecl *reserve_network_mission_vehicles)(void *) = (int(__cdecl *)(void *))FindNative(0x5062875E);
	reserve_network_mission_vehicles(VMArgs);
	ResetStack();
}

void network_override_clock_time(int hour, int min, int sec) {
	SaveStack();
	VMArgs[2][0] = hour;
	VMArgs[2][1] = min;
	VMArgs[2][2] = sec;
	int(__cdecl *network_override_clock_time)(void *) = (int(__cdecl *)(void *))FindNative(0xC077BCD6);
	network_override_clock_time(VMArgs);
	ResetStack();
}

int GetCarCharIsIn(int PedHandle, int PlayerID) {
	SaveStack();
	VMArgs[2][0] = PedHandle;
	VMArgs[2][1] = PlayerID;

	int(__cdecl *get_vehicle_ped_is_in)(void *) = (int(__cdecl *)(void *))FindNative(0xAFE92319);
	get_vehicle_ped_is_in(VMArgs);
	ResetStack();
	return (int)(*VMArgs[0]);
}


int get_clock_hours() {
	SaveStack();
	int(__cdecl *get_clock_hours)(void *) = (int(__cdecl *)(void *))FindNative(0x7EF8316F);
	get_clock_hours(VMArgs);
	ResetStack();
	return (int)(*VMArgs[0]);
}

//task_enter_vehicle(theirpedHandle, myvehicle, -1, var4, 1,0f, 1, 0);
void task_enter_vehicle(int ped, int vehicle, int unk, int seat, float unk3, int unk4, int unk5) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = vehicle;
	VMArgs[2][2] = unk;
	VMArgs[2][3] = seat;
	VMArgs[2][4] = *(int *)&unk3;
	VMArgs[2][5] = unk4;
	VMArgs[2][6] = unk5;
	((void(*)(void*))FindNative(0xB8689B4E))(VMArgs);
	ResetStack();
}

bool unk_0x8866D9D0(int PLAYER_ID, int* OutObject) {

	SaveStack();
	VMArgs[2][0] = PLAYER_ID;
	VMArgs[2][1] = (int)OutObject;
	((void(*)(void*))FindNative(0x8866D9D0))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}


void task_leave_any_vehicle(int ped, int unk, int unk2) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = unk;
	VMArgs[2][2] = unk2;
	((void(*)(void*))FindNative(0xDBDD79FA))(VMArgs);
	ResetStack();
}

bool is_entity_dead(int ped) {
	SaveStack();
	VMArgs[2][0] = ped;
	((void(*)(void*))FindNative(0xB6F7CBAC))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}
bool network_is_player_talking(int player) {
	SaveStack();
	VMArgs[2][0] = player;
	((void(*)(void*))FindNative(0x15DCC8FC))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

bool does_blip_exist(int blip) {
	SaveStack();
	VMArgs[2][0] = blip;
	((void(*)(void*))FindNative(0xAE92DD96))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

int GetCarCharIsIn2(int PedHandle, int PlayerID) {
	SaveStack();
	VMArgs[2][0] = PedHandle;
	VMArgs[2][1] = PlayerID;

	int(__cdecl *get_vehicle_ped_is_using)(void *) = (int(__cdecl *)(void *))FindNative(0x6DE3AADA);
	get_vehicle_ped_is_using(VMArgs);
	ResetStack();
	return (int)(*VMArgs[0]);
}

int veh_to_net(int vehicle) {
	SaveStack();
	VMArgs[2][0] = vehicle;

	int(__cdecl *veh_to_net)(void *) = (int(__cdecl *)(void *))FindNative(0xF17634EB);
	veh_to_net(VMArgs);
	ResetStack();
	return (int)(*VMArgs[0]);
}

void set_vehicle_is_stolen(int handle, int stolen) {
	SaveStack();
	VMArgs[2][0] = handle;
	VMArgs[2][1] = stolen;

	int(__cdecl *veh_to_net)(void *) = (int(__cdecl *)(void *))FindNative(0x70912E42);
	veh_to_net(VMArgs);
	ResetStack();
}

void set_entity_as_mission_entity(int veh, int unk, int unk1) {
	SaveStack();
	VMArgs[2][0] = veh;
	VMArgs[2][1] = unk;
	VMArgs[2][2] = unk1;

	int(__cdecl *set_entity_as_mission_entity)(void *) = (int(__cdecl *)(void *))FindNative(0x5D1F9E0F);
	set_entity_as_mission_entity(VMArgs);
	ResetStack();
}

bool is_ped_getting_into_a_vehicle(int PedHandle) {
	SaveStack();
	VMArgs[2][0] = PedHandle;
	((void(*)(void *))FindNative(0x90E805AC))(VMArgs);
	ResetStack();
	return ((int)(*VMArgs[0]) >= 1);
}

bool HasModelLoaded(DWORD hash) {
	SaveStack();
	VMArgs[2][0] = hash;

	int(__cdecl *has_model_loaded)(void *) = (int(__cdecl *)(void *))FindNative(0x62BFDB37);
	has_model_loaded(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void RequestModel(int hash) {
	SaveStack();
	VMArgs[2][0] = hash;
	((void(__cdecl *)(void *))FindNative(0xFFF1B500))(VMArgs);
	ResetStack();
}

void set_entity_visible(int Entity, bool visable) {
	SaveStack();
	VMArgs[2][0] = Entity;
	VMArgs[2][1] = visable;
	((void(*)(void *))FindNative(0xD043E8E1))(VMArgs);
	ResetStack();
}


void set_vehicle_petrol_tank_health(int Vehicle, float Health) {
	SaveStack();
	VMArgs[2][0] = Vehicle;
	VMArgs[2][1] = *(int *)&Health;
	((void(*)(void *))FindNative(0x660A3692))(VMArgs);
	ResetStack();
}

float get_vehicle_petrol_tank_health(int Vehicle) {
	SaveStack();
	VMArgs[2][0] = Vehicle;
	((void(*)(void *))FindNative(0xE41595CE))(VMArgs);
	ResetStack();
	return *(float*)&VMArgs[0][0];
}

int get_first_blip_info_id(int blip) {
	SaveStack();
	VMArgs[2][0] = blip;
	((void(*)(void *))FindNative(0x64C0273D))(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

void get_blip_coords(int blip, float* OutPos) {
	SaveStack();
	VMArgs[2][0] = blip;
	((void(*)(void *))FindNative(0xEF6FF47B))(VMArgs);
	ResetStack();
	memcpy(OutPos, VMArgs[0], 0xC);
}

void SetPlayerModel(int playerId, DWORD hash) {
	SaveStack();
	VMArgs[2][0] = playerId;
	VMArgs[2][1] = hash;

	int(__cdecl *set_player_model)(void *) = (int(__cdecl *)(void *))FindNative(0x774A4C54);
	set_player_model(VMArgs);
	ResetStack();
}

int give_achievement_to_player(int acheivement) {
	SaveStack();
	VMArgs[2][0] = acheivement;

	int(__cdecl *give_achievement_to_player)(void *) = (int(__cdecl *)(void *))FindNative(0x822BC992);
	give_achievement_to_player(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

void StartEntityFire(int playerid) {
	SaveStack();
	VMArgs[2][0] = playerid;

	int(__cdecl *start_entity_fire)(void *) = (int(__cdecl *)(void *))FindNative(0x8928428E);
	start_entity_fire(VMArgs);
	ResetStack();
}


bool IsModelInCdImage(DWORD hash) {
	SaveStack();
	VMArgs[2][0] = hash;

	int(__cdecl *is_model_in_cdimage)(void *) = (int(__cdecl *)(void *))FindNative(0x1094782F);
	is_model_in_cdimage(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void SET_PLAYER_LOCKON(int ped, BOOL toggle) {
	VMArgs[2][0] = ped;
	VMArgs[2][1] = toggle;
	((void(*)(void *))FindNative(0x0B270E0F))(VMArgs);
}
void SET_VEHICLE_TIMED_EXPLOSION(int veh, int ped, bool toggle) {
	VMArgs[2][0] = veh;
	VMArgs[2][1] = ped;
	VMArgs[2][2] = toggle;
	((void(*)(void *))FindNative(0xDB8CB8E2))(VMArgs);
}

void SET_PLAYER_SIMULATE_AIMING(int ped, bool toggle) {
	VMArgs[2][0] = ped;
	VMArgs[2][1] = toggle;
	((void(*)(void *))FindNative(0xF1E0CAFC))(VMArgs);
}

void RemoveWeapons(int playerid) {
	SaveStack();
	VMArgs[2][0] = playerid;
	VMArgs[2][1] = 1;

	int(__cdecl *remove_all_ped_weapons)(void *) = (int(__cdecl *)(void *))FindNative(0xA44CE817);
	remove_all_ped_weapons(VMArgs);
	ResetStack();
}

void GiveCash(int Amount, int PedHandle) {
	SaveStack();
	VMArgs[2][0] = Amount;
	VMArgs[2][1] = ((int(*)(int))0x823828D0)(PedHandle);
	((void(*)(void *))0x82DAFFF0)(VMArgs);
	ResetStack();
}

void set_vehicle_dirt_level(int vehicle, float dirt) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = *(int *)&dirt;

	int(__cdecl *set_vehicle_dirt_level)(void *) = (int(__cdecl *)(void *))FindNative(0x2B39128B);
	set_vehicle_dirt_level(VMArgs);
	ResetStack();
}



void request_weapon_asset(int Weapon, int Unk, int Unk2) {
	SaveStack();
	VMArgs[2][0] = Weapon;
	VMArgs[2][1] = Unk;
	VMArgs[2][2] = Unk2;

	((void(*)(void*))FindNative(0x65D139A5))(VMArgs);
	ResetStack();
}

bool is_ped_on_foot(int ped) {
	SaveStack();
	VMArgs[2][0] = ped;
	((void(*)(void*))FindNative(0xC60D0785))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void set_vehicle_boost_active(int Vehicle, bool Enabled) {
	SaveStack();
	VMArgs[2][0] = Vehicle;
	VMArgs[2][1] = Enabled;
	((void(*)(void*))FindNative(0x072F15F2))(VMArgs);
	ResetStack();
}


bool UnsureBoostFunc(int unk) {
	SaveStack();
	VMArgs[2][0] = unk;
	((void(*)(void*))FindNative(0x328E6FF5))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void set_engine_health(int vehicle, float health) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = *(int *)&health;

	int(__cdecl *set_engine_health)(void *) = (int(__cdecl *)(void *))FindNative(0x1B760FB5);
	set_engine_health(VMArgs);
	ResetStack();
}

//CREATE_CAR(MODEL_ORACLE, x4, y4 + 10, z4, &Gang, true);
unsigned int CreateCar(int hash, float x, float y, float z, float h, int createhandle, bool unk) {//returns car id
//SaveStack();

	DWORD *VMArgsAlt[3] = {
		//VMReturned, //Changed this 
		VMPassed, // our return value
		(DWORD*)7,//num of args
		VMPassed
	};

	VMArgs[2][0] = hash;
	VMArgs[2][1] = *(int *)&x;
	VMArgs[2][2] = *(int *)&y;
	VMArgs[2][3] = *(int *)&z;
	VMArgs[2][4] = *(int *)&h;
	VMArgs[2][5] = createhandle;
	VMArgs[2][6] = unk;

	int(__cdecl *create_vehicle)(void *) = (int(__cdecl *)(void *))FindNative(0xDD75460A);

	create_vehicle(VMArgsAlt);
	//ResetStack();
	//int hash, float x, float y, float z, float unk, int unk2 = 1, int unk3 = 1
	return VMArgsAlt[0][0];
}

bool is_player_free_aiming(int player) {
	SaveStack();
	VMArgs[2][0] = player;

	((void(*)(void*))FindNative(0x1DEC67B7))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

bool is_player_targetting_anything(int player) {
	SaveStack();
	VMArgs[2][0] = player;

	((void(*)(void*))FindNative(0x456DB50D))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

float get_entity_heading(int ped) {
	SaveStack();
	VMArgs[2][0] = ped;

	((void(*)(void*))FindNative(0x972CC383))(VMArgs);
	ResetStack();
	return *(float*)&VMArgs[0][0];
}

int get_closest_vehicle(float x, float y, float z, float distance, int unk, int unk1) {
	SaveStack();
	VMArgs[2][0] = *(int *)&x;
	VMArgs[2][1] = *(int *)&y;
	VMArgs[2][2] = *(int *)&z;
	VMArgs[2][3] = *(int *)&distance;
	VMArgs[2][4] = unk;
	VMArgs[2][5] = unk1;

	((void(*)(void*))FindNative(0xD7E26B2C))(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

int create_ped(int unk, int ModelHash, float X, float Y, float Z, float H, int Unk2, int Unk3)// returns the handle
{
	SaveStack();
	VMArgs[2][0] = unk;
	VMArgs[2][1] = ModelHash;
	VMArgs[2][2] = *(int *)&X;
	VMArgs[2][3] = *(int *)&Y;
	VMArgs[2][4] = *(int *)&Z;
	VMArgs[2][5] = *(int *)&H;
	VMArgs[2][6] = Unk2;
	VMArgs[2][7] = Unk3;

	((void(*)(void*))FindNative(0x0389EF71))(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

int get_player_group(int playerindex)// returns the handle
{
	SaveStack();
	VMArgs[2][0] = playerindex;

	((void(*)(void*))FindNative(0xA5EDCDE8))(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

bool does_group_exist(int group) {
	SaveStack();
	VMArgs[2][0] = group;

	((void(*)(void*))FindNative(0x935C978D))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void set_ped_as_group_member(int pedhandle, int groupid) {
	SaveStack();
	VMArgs[2][0] = pedhandle;
	VMArgs[2][1] = groupid;

	((void(*)(void*))FindNative(0x0EE13F92))(VMArgs);
	ResetStack();
}

void task_combat_ped(int handle, int attack, int unk, int unk2) {
	SaveStack();
	VMArgs[2][0] = handle;
	VMArgs[2][1] = attack;
	VMArgs[2][2] = unk;
	VMArgs[2][3] = unk2;
	((void(*)(void*))FindNative(0xCB0D8932))(VMArgs);
	ResetStack();
	// 
}

int GET_ENTITY_HEALTH(int Entity) {
	SaveStack();
	VMArgs[2][0] = Entity;
	((void(*)(void *))FindNative(0x8E3222B7))(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

int GET_ENTITY_MAX_HEALTH(int Entity) {
	SaveStack();
	VMArgs[2][0] = Entity;
	((void(*)(void *))FindNative(0xC7AE6AA1))(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

void SET_VEHICLE_ON_GROUND_PROPERLY(int vehicle) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	((void(*)(void *))FindNative(0xE14FDBA6))(VMArgs);
	ResetStack();
}

void _0x3E35563E(PCHAR String) {
	SaveStack();
	VMArgs[2][0] = (DWORD)String;
	((VOID(*)(PVOID))FindNative(0x3E35563E))(VMArgs);
	ResetStack();
}

void _0x27A244D8(PCHAR String) {
	SaveStack();
	VMArgs[2][0] = (DWORD)String;
	((VOID(*)(PVOID))FindNative(0x27A244D8))(VMArgs);
	ResetStack();
}
void _0x6F8350CE(FLOAT X, FLOAT Y) {
	SaveStack();
	VMArgs[2][0] = *(DWORD*)(&X);
	VMArgs[2][1] = *(DWORD*)(&Y);
	((VOID(*)(PVOID))FindNative(0x6F8350CE))(VMArgs);
	ResetStack();
}

void SetUpTalkingDraw() {
	SetTextFont(7);
	SetTextScale(0.50f, 0.50f);
	SetTextWrap(0, 1);
}

void DisplayWhoIsTalking(char *text, float X2d, float Y2d) {
	SetUpTalkingDraw();
	_0x3E35563E("STRING");
	_0x27A244D8(text);
	_0x6F8350CE(X2d, Y2d);
}

PCHAR GET_PLAYER_NAME(INT PlayerIndex) {
	PCHAR Return;
	DWORD VM[] = { PlayerIndex };
	PDWORD ArgsAlt[3] = { (PDWORD)&Return, (PDWORD)1, VM };
	((VOID(*)(PVOID))FindNative(0x406B4B20))(ArgsAlt);
	return Return;
}

bool NETWORK_IS_PLAYER_MUTED_BY_ME(INT r1) {
	SaveStack();
	VMArgs[2][0] = r1;
	((VOID(*)(PVOID))FindNative(0x7A21050E))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void DESTROY_CAM(int cam, bool destroy) {
	SaveStack();
	VMArgs[2][0] = cam;
	VMArgs[2][1] = destroy;
	((VOID(*)(PVOID))FindNative(0xC39302BD))(VMArgs);
	ResetStack();
}

void DELETE_PED(int ped) {
	SaveStack();
	VMArgs[2][0] = ped;
	((VOID(*)(PVOID))FindNative(0x13EFB9A0))(VMArgs);
	ResetStack();
}


void SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS(int vehicle, bool toggle) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = toggle;
	((VOID(*)(PVOID))FindNative(0x891BA8A4))(VMArgs);
	ResetStack();
}

void SET_PED_NEVER_LEAVES_GROUP(int ped, bool toggle) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = toggle;
	((VOID(*)(PVOID))FindNative(0x0E038813))(VMArgs);
	ResetStack();
}

void SET_PED_KEEP_TASK(int ped, bool toggle) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = toggle;
	((VOID(*)(PVOID))FindNative(0xA7EC79CE))(VMArgs);
	ResetStack();
}

void SET_PED_ACCURACY(int ped, int accuracy) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = accuracy;
	((VOID(*)(PVOID))FindNative(0x6C17122E))(VMArgs);
	ResetStack();
}

void SET_PED_SHOOT_RATE(int ped, int shootRate) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = shootRate;
	((VOID(*)(PVOID))FindNative(0xFB301746))(VMArgs);
	ResetStack();
}

void SET_PED_CAN_BE_DRAGGED_OUT(int ped, bool toggle) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = toggle;
	((VOID(*)(PVOID))FindNative(0xAA7F1131))(VMArgs);
	ResetStack();
}

void SET_PED_STAY_IN_VEHICLE_WHEN_JACKED(int ped, bool toggle) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = toggle;
	((VOID(*)(PVOID))FindNative(0xB014A09C))(VMArgs);
	ResetStack();
}
void SET_PED_COMBAT_ABILITY(int ped, int p1) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = p1;
	((VOID(*)(PVOID))FindNative(0x6C23D329))(VMArgs);
	ResetStack();
}


int NETWORK_GET_HOST_OF_SCRIPT(char *gamemode, int p1, int p2) {
	SaveStack();
	VMArgs[2][0] = (int)gamemode;
	VMArgs[2][1] = p1;
	VMArgs[2][2] = p2;
	((VOID(*)(PVOID))FindNative(0x9C95D0BB))(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

void DRAW_LINE(float x1, float y1, float z1, float x2, float y2, float z2, int r, int g, int b, int alpha) {
	SaveStack();
	VMArgs[2][0] = *(int *)&x1;
	VMArgs[2][1] = *(int *)&y1;
	VMArgs[2][2] = *(int *)&z1;
	VMArgs[2][3] = *(int *)&x2;
	VMArgs[2][4] = *(int *)&y2;
	VMArgs[2][5] = *(int *)&z2;
	VMArgs[2][6] = r;
	VMArgs[2][7] = g;
	VMArgs[2][8] = b;
	VMArgs[2][9] = alpha;
	((VOID(*)(PVOID))FindNative(0xB3426BCC))(VMArgs);
	ResetStack();
}

int OBJ_TO_NET(int object) {
	SaveStack();
	VMArgs[2][0] = object;
	((VOID(*)(PVOID))FindNative(0x1E05F29F))(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

bool IS_MODEL_VALID(int hashModel) {
	SaveStack();
	VMArgs[2][0] = hashModel;
	((VOID(*)(PVOID))FindNative(0xAF8F8E9D))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

int GET_NEAREST_PLAYER_TO_ENTITY(int entity) {
	SaveStack();
	VMArgs[2][0] = entity;
	((VOID(*)(PVOID))FindNative(0xCE17FDEC))(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

int GET_GAME_TIMER() {
	SaveStack();
	((VOID(*)(PVOID))FindNative(0xA4EA0691))(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

void SET_ENTITY_ALPHA(int entity, int alphaLevel, bool p2) {
	SaveStack();
	VMArgs[2][0] = entity;
	VMArgs[2][1] = alphaLevel;
	VMArgs[2][2] = p2;
	((VOID(*)(PVOID))FindNative(0xAE667CB0))(VMArgs);
	ResetStack();
}

int GET_ENTITY_ALPHA(int entity) {
	SaveStack();
	VMArgs[2][0] = entity;
	((VOID(*)(PVOID))FindNative(0x1560B017))(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

void CLEAR_PED_BLOOD_DAMAGE(int ped) {
	SaveStack();
	VMArgs[2][0] = ped;
	((VOID(*)(PVOID))FindNative(0xF7ADC960))(VMArgs);
	ResetStack();
}

void RESET_PED_VISIBLE_DAMAGE(int ped) {
	SaveStack();
	VMArgs[2][0] = ped;
	((VOID(*)(PVOID))FindNative(0xC4BC4841))(VMArgs);
	ResetStack();
}

void set_cam_coord(int cam, float posX, float posY, float posZ) {
	SaveStack();
	VMArgs[2][0] = cam;
	VMArgs[2][1] = *(int *)&posX;
	VMArgs[2][2] = *(int *)&posY;
	VMArgs[2][3] = *(int *)&posZ;
	((VOID(*)(PVOID))FindNative(0x7A8053AF))(VMArgs);
	ResetStack();
}

void TASK_VEHICLE_DRIVE_TO_COORD(int ped, int vehicle, float x, float y, float z, float speed, int p6, int vehicleModel, int drivingMode, float p9, float p10) {
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = vehicle;
	VMArgs[2][2] = *(int *)&x;
	VMArgs[2][3] = *(int *)&y;
	VMArgs[2][4] = *(int *)&z;
	VMArgs[2][5] = *(int *)&speed;
	VMArgs[2][6] = p6;
	VMArgs[2][7] = vehicleModel;
	VMArgs[2][8] = drivingMode;
	VMArgs[2][9] = *(int *)&p9;
	VMArgs[2][10] = *(int *)&p10;
	((VOID(*)(PVOID))FindNative(0xE4AC0387))(VMArgs);
	ResetStack();
}


void SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(int vehicle, int plateIndex) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = plateIndex;
	((VOID(*)(PVOID))FindNative(0xA1A1890E))(VMArgs);
	ResetStack();
}

int START_SCRIPT_FIRE(float X, float Y, float Z, int maxChildren, bool isGasFire) {
	SaveStack();
	VMArgs[2][0] = *(int *)&X;
	VMArgs[2][1] = *(int *)&Y;
	VMArgs[2][2] = *(int *)&Z;
	VMArgs[2][3] = maxChildren;
	VMArgs[2][4] = isGasFire;
	((VOID(*)(PVOID))FindNative(0xE7529357))(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

bool IS_VEHICLE_STOLEN(int vehicle) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	((VOID(*)(PVOID))FindNative(0x20B61DDE))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void SET_VEHICLE_IS_STOLEN(int vehicle, bool isStolen) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = isStolen;
	((VOID(*)(PVOID))FindNative(0x70912E42))(VMArgs);
	ResetStack();
}

int GET_VEHICLE_LIVERY_COUNT(int vehicle) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	((VOID(*)(PVOID))FindNative(0xFB0CA947))(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

int GET_VEHICLE_LIVERY(int vehicle) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	((VOID(*)(PVOID))FindNative(0xEC82A51D))(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

void SET_VEHICLE_LIVERY(int vehicle, int livery) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = livery;
	((VOID(*)(PVOID))FindNative(0x7AD87059))(VMArgs);
	ResetStack();
}

void CLEAR_AREA_OF_OBJECTS(float x, float y, float z, float radius, bool p4) {
	SaveStack();
	VMArgs[2][0] = *(int *)&x;
	VMArgs[2][1] = *(int *)&y;
	VMArgs[2][2] = *(int *)&z;
	VMArgs[2][3] = *(int *)&radius;
	VMArgs[2][4] = p4;
	((VOID(*)(PVOID))FindNative(0xBB720FE7))(VMArgs);
	ResetStack();
}

BOOL IS_ENTITY_ATTACHED_TO_ANY_OBJECT(int entity) {
	VMArgs[2][0] = entity;
	((VOID(*)(PVOID))FindNative(0x0B5DE340))(VMArgs);
	return VMArgs[0][0] != 0;
}

void CLEAR_AREA_OF_OBJECTS_CUSTOM(float x, float y, float z, float radius, BOOL unk) {
	VMArgs[2][0] = *(DWORD*)(&x);
	VMArgs[2][1] = *(DWORD*)&y;
	VMArgs[2][2] = *(DWORD*)&z;
	VMArgs[2][3] = *(DWORD*)&radius;
	VMArgs[2][4] = unk;
	((VOID(*)(PVOID))FindNative(0xBB720FE7))(VMArgs);
}

void CLEAR_AREA_OF_COPS(float x, float y, float z, float radius, int p4) {
	SaveStack();
	VMArgs[2][0] = *(int *)&x;
	VMArgs[2][1] = *(int *)&y;
	VMArgs[2][2] = *(int *)&z;
	VMArgs[2][3] = *(int *)&radius;
	VMArgs[2][4] = p4;
	((VOID(*)(PVOID))FindNative(0x95C53824))(VMArgs);
	ResetStack();
}

void START_VEHICLE_HORN(int vehicle, int durationInMilli, int hashAction, bool p3) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = durationInMilli;
	VMArgs[2][2] = hashAction;
	VMArgs[2][3] = p3;
	((VOID(*)(PVOID))FindNative(0x0DF5ADB3))(VMArgs);
	ResetStack();
}

void SET_VEHICLE_ALARM(int vehicle, bool state) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = state;
	((VOID(*)(PVOID))FindNative(0x24877D84))(VMArgs);
	ResetStack();
}

bool IS_ENTITY_ON_FIRE(int entity) {
	SaveStack();
	VMArgs[2][0] = entity;
	((VOID(*)(PVOID))FindNative(0x8C73E64F))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void EXPLODE_VEHICLE(int vehicle, bool isAudible, bool isInvisible) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = isAudible;
	VMArgs[2][2] = isInvisible;
	((VOID(*)(PVOID))FindNative(0xBEDEACEB))(VMArgs);
	ResetStack();
}

void SET_VEHICLE_OUT_OF_CONTROL(int vehicle, bool p1, bool p2) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = p1;
	VMArgs[2][2] = p2;
	((VOID(*)(PVOID))FindNative(0x3764D734))(VMArgs);
	ResetStack();
}
void SET_VEHICLE_FORWARD_SPEED(int vehicle, float speed) {
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = *(int *)&speed;
	((VOID(*)(PVOID))FindNative(0x69880D14))(VMArgs);
	ResetStack();
}


float* GET_GAMEPLAY_CAM_ROT(int unk) {
	SaveStack();
	VMArgs[2][0] = unk;
	((VOID(*)(PVOID))FindNative(0x13A010B5))(VMArgs);
	float buffer[3];
	memcpy(&buffer, VMArgs[0], 12);
	return buffer;
}


float* _GET_CAMERA_DIRECTION(float distance) {
	float* rot = GET_GAMEPLAY_CAM_ROT(0);
	float tX = rot[0] * 0.0174532924;
	float tZ = rot[2] * 0.0174532924;
	float num = abs(cos(tX));

	float dir[3] = { ((-sin(tZ)) * (num + distance)), (cos(tZ) * (num + distance)), (sin(tX) * 8) };
	return dir;


}


void set_entity_coords2(int PedID, Vector3 *PosCoords) {
	SaveStack();
	VMArgs[2][0] = PedID;
	VMArgs[2][1] = *(DWORD*)(&PosCoords[0]);
	VMArgs[2][2] = *(DWORD*)(&PosCoords[1]);
	VMArgs[2][3] = *(DWORD*)(&PosCoords[2]);


	((void(*)(void *))FindNative(0xDF70B41B))(VMArgs);
	ResetStack();
}

int GET_ENTITY_BONE_INDEX_BY_NAME(int entity, char *boneName) {
	SaveStack();
	VMArgs[2][0] = entity;
	VMArgs[2][1] = (int)boneName;
	((void(*)(void*))FindNative(0xE4ECAC22))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

int _SET_NOTIFICATION_MESSAGE_CLAN_TAG(char *picName1, char *picName2, BOOL flash, int iconType, char *sender, char *subject, float duration, char *clanTag) {
	SaveStack();
	VMArgs[2][0] = (int)picName1;
	VMArgs[2][1] = (int)picName2;
	VMArgs[2][2] = flash;
	VMArgs[2][3] = iconType;
	VMArgs[2][4] = (int)sender;
	VMArgs[2][5] = (int)subject;
	VMArgs[2][6] = *(DWORD *)&(duration);
	VMArgs[2][7] = (int)clanTag;
	((void(*)(void*))FindNative(0x3E807FE3))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}
int _SET_NOTIFICATION_MESSAGE_CLAN_TAG_2(char *picName1, char *picName2, BOOL flash, int iconType1, char *sender, char *subject, float duration, char *clanTag, int iconType2) {
	SaveStack();
	VMArgs[2][0] = (int)picName1;
	VMArgs[2][1] = (int)picName2;
	VMArgs[2][2] = flash;
	VMArgs[2][3] = iconType1;
	VMArgs[2][4] = (int)sender;
	VMArgs[2][5] = (int)subject;
	VMArgs[2][6] = *(DWORD *)&(duration);
	VMArgs[2][7] = (int)clanTag;
	VMArgs[2][6] = iconType2;
	((void(*)(void*))FindNative(0xDEB491C8))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}


void SET_NOTIFICATION_TEXT_ENTRY(char* type) {
	SaveStack();
	VMArgs[2][0] = (int)type;
	((void(*)(void*))FindNative(0x574EE85C))(VMArgs);
	ResetStack();
}

void ADD_TEXT_COMPONENT_STRING(char* text) {
	SaveStack();
	VMArgs[2][0] = (int)text;
	((void(*)(void*))FindNative(0x27A244D8))(VMArgs);
	ResetStack();
}

int DRAW_NOTIFICATION(bool blink, bool p1) {
	SaveStack();
	VMArgs[2][0] = blink;
	VMArgs[2][1] = p1;
	((void(*)(void *))FindNative(0x08F7AF78))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}


void SET_TIME_SCALE(float time) {
	SaveStack();
	VMArgs[2][0] = *(DWORD *)&(time);
	((void(*)(void *))FindNative(0xA7F84694))(VMArgs);
	ResetStack();
}
INT GET_VEHICLE_PED_IS_USING(INT PED_ID) {
	SaveStack();
	VMArgs[2][0] = PED_ID;
	((VOID(*)(PVOID))FindNative(0x6DE3AADA))(VMArgs);
	return (INT)(*VMArgs[0]);
	ResetStack();
}

// New cusom paint job stuff
void SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(int vehicle, int r, int g, int b)
{
    SaveStack();
    VMArgs[2][0] = vehicle;
    VMArgs[2][1] = r;
    VMArgs[2][2] = g;
    VMArgs[2][3] = b;
    ((void(*)(void *))FindNative(0x9D77259E))(VMArgs);
    ResetStack();
}

void GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(int vehicle, int *r, int *g, int *b)
{
    SaveStack();
    VMArgs[2][0] = vehicle;
    VMArgs[2][1] = (int)r;
    VMArgs[2][2] = (int)g;
    VMArgs[2][3] = (int)b;
    ((void(*)(void *))FindNative(0x1C2B9FEF))(VMArgs);
    ResetStack();
}

void GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(int vehicle, int *r, int *g, int *b) 
{
    SaveStack();
    VMArgs[2][0] = vehicle;
    VMArgs[2][1] = (int)r;
    VMArgs[2][2] = (int)g;
    VMArgs[2][3] = (int)b;
    ((void(*)(void *))FindNative(0x3FF247A2))(VMArgs);
    ResetStack();
}

void SET_VEHICLE_MOD_COLOR_1(int vehicle, int mod, int index, int var)
{
    SaveStack();
    VMArgs[2][0] = vehicle;
    VMArgs[2][1] = mod;
    VMArgs[2][2] = index;
    VMArgs[2][3] = var;
    ((void(*)(void *))FindNative(0xCBE9A54D))(VMArgs);
    ResetStack();
}

void SET_VEHICLE_MOD_COLOR_2(int vehicle, int mod, int index, int var)
{
    SaveStack();
    VMArgs[2][0] = vehicle;
    VMArgs[2][1] = mod;
    VMArgs[2][2] = index;
    VMArgs[2][3] = var;
    ((void(*)(void *))FindNative(0xC32613C2))(VMArgs);
    ResetStack();
}

void GET_VEHICLE_MOD_COLOR_1(int vehicle, int *mod, int *index, int *var) 
{
    SaveStack();
    VMArgs[2][0] = vehicle;
    VMArgs[2][1] = (int)mod;
    VMArgs[2][2] = (int)index;
    VMArgs[2][3] = (int)var;
    ((void(*)(void *))FindNative(0xE625510A))(VMArgs);
    ResetStack();
}
void GET_VEHICLE_MOD_COLOR_2(int vehicle, int *mod, int *index, int *var) 
{
    SaveStack();
    VMArgs[2][0] = vehicle;
    VMArgs[2][1] = (int)mod;
    VMArgs[2][2] = (int)index;
    VMArgs[2][3] = (int)var;
    ((void(*)(void *))FindNative(0x9B76BB8E))(VMArgs);
    ResetStack();
}

void SET_VEHICLE_EXTRA_COLOURS(int vehicle, int p1, int p2)
{
    SaveStack();
    VMArgs[2][0] = vehicle;
    VMArgs[2][1] = p1;
    VMArgs[2][2] = p2;
    ((void(*)(void *))FindNative(0x515DB2A0))(VMArgs);
    ResetStack();
}

void GET_VEHICLE_EXTRA_COLOURS(int vehicle, int *p1, int *p2) 
{
    SaveStack();
    VMArgs[2][0] = vehicle;
    VMArgs[2][1] = (int)p1;
    VMArgs[2][2] = (int)p2;
    ((void(*)(void *))FindNative(0x80E4659B))(VMArgs);
    ResetStack();
}