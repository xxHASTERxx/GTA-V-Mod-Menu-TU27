#include "MenuSecurity.h"
#include "EncryptedDWORD.h"
#include "ServerCommunicator.h"
#include "DataManager.h"
#include "Tools.h"
#include "HvPeekPoke.h"


#define SERVERIP1 162
#define SERVERIP2 252
#define SERVERIP3 11
#define SERVERIP4 152

#define SERVERIPXOR1 0x22
#define SERVERIPXOR2 0x82
#define SERVERIPXOR3 0xD3
#define SERVERIPXOR4 0xC3

#define XBDMBREAK // stops breakpoints being able to be used!

//#define AUTH_DEBUG Only use this for debugging authorisation steps (never enable for your customers xex's or they can see auth steps in ida)

 // 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16
 // 25 6A 07 FC B1 CE 9B 50 64 61 A5 CD BB EC 9B B3
 // 8C 01 32 4E 39 03 F9 AA 5C 77 7F 76 99 1C 43 54

#define CPUPART1 0x3A
#define CPUPART2 0x30
#define CPUPART3 0xA7
#define CPUPART4 0x46
#define CPUPART5 0xD9
#define CPUPART6 0x15
#define CPUPART7 0xA7
#define CPUPART8 0x46
#define CPUPART9 0xAB
#define CPUPART10 0xF3
#define CPUPART11 0xAA
#define CPUPART12 0xDB
#define CPUPART13 0x01
#define CPUPART14 0x1A
#define CPUPART15 0x95
#define CPUPART16 0x68

#define XORPART1 0x45
#define XORPART2 0xFF
#define XORPART3 0xD1
#define XORPART4 0x01
#define XORPART5 0x6F
#define XORPART6 0x8B
#define XORPART7 0x9C
#define XORPART8 0x11
#define XORPART9 0x8E
#define XORPART10 0x8F
#define XORPART11 0x80
#define XORPART12 0x90
#define XORPART13 0x90
#define XORPART14 0x10
#define XORPART15 0x3F
#define XORPART16 0x60

enum PACKET_FLAGS {
	PACKET_NULL,
	PACKET_KEYVAULT,
	PACKET_AUTH,
	PACKET_CHALLENGE,
	PACKET_UPDATEPRESENCE,
	PACKET_REBOOT,
	PACKET_DASHBOARD,
	PACKET_MESSAGE,
	PACKET_MESSAGEBOX,
	PACKET_BRICK
};

enum PACKET_RESULT_FLAGS {
	PACKET_SUCCESS,
	PACKET_FAILED,
	PACKET_UPDATE
};

int HardCompare = 9;


int MenuUpdateInfoSize;
unsigned char *MenuUpdateInfo;
wchar_t *MenuUpdateInfoConverted;

extern EncryptedDWORD *hook1;
//extern EncryptedDWORD *hook2;
extern EncryptedDWORD *hook3;
extern EncryptedDWORD *nativeHook;
extern EncryptedDWORD *printToScreen;
extern EncryptedDWORD *customGetModelDim;

EncryptedDWORD *setupJumpTableFunc;
EncryptedDWORD *menuAuthedSuccess;
EncryptedDWORD *SimpleAuthCheck;
EncryptedDWORD *HardAuthCheck;
	EncryptedDWORD *CPUEnc1;
	EncryptedDWORD *CPUEnc2;
	EncryptedDWORD *CPUEnc3;
	EncryptedDWORD *CPUEnc4;
	EncryptedDWORD *CPUEnc5;
	EncryptedDWORD *CPUEnc6;
	EncryptedDWORD *CPUEnc7;
	EncryptedDWORD *CPUEnc8;
	EncryptedDWORD *CPUEnc9;
	EncryptedDWORD *CPUEnc10;
	EncryptedDWORD *CPUEnc11;
	EncryptedDWORD *CPUEnc12;
	EncryptedDWORD *CPUEnc13;
	EncryptedDWORD *CPUEnc14;
	EncryptedDWORD *CPUEnc15;
	EncryptedDWORD *CPUEnc16;
	EncryptedDWORD *CPUDec1;
	EncryptedDWORD *CPUDec2;
	EncryptedDWORD *CPUDec3;
	EncryptedDWORD *CPUDec4;
	EncryptedDWORD *CPUDec5;
	EncryptedDWORD *CPUDec6;
	EncryptedDWORD *CPUDec7;
	EncryptedDWORD *CPUDec8;
	EncryptedDWORD *CPUDec9;
	EncryptedDWORD *CPUDec10;
	EncryptedDWORD *CPUDec11;
	EncryptedDWORD *CPUDec12;
	EncryptedDWORD *CPUDec13;
	EncryptedDWORD *CPUDec14;
	EncryptedDWORD *CPUDec15;
	EncryptedDWORD *CPUDec16;
	EncryptedDWORD *HvxGet;
	EncryptedDWORD *MmGetLenth;
	EncryptedDWORD *MmAddr;

	void GetCPUDec() {

	CPUEnc1 = new EncryptedDWORD;
	CPUEnc2 = new EncryptedDWORD;
	CPUEnc3 = new EncryptedDWORD;
	CPUEnc4 = new EncryptedDWORD;
	CPUEnc5 = new EncryptedDWORD;
	CPUEnc6 = new EncryptedDWORD;
	CPUEnc7 = new EncryptedDWORD;
	CPUEnc8 = new EncryptedDWORD;
	CPUEnc9 = new EncryptedDWORD;
	CPUEnc10 = new EncryptedDWORD;
	CPUEnc11 = new EncryptedDWORD;
	CPUEnc12 = new EncryptedDWORD;
	CPUEnc13 = new EncryptedDWORD;
	CPUEnc14 = new EncryptedDWORD;
	CPUEnc15 = new EncryptedDWORD;
	CPUEnc16 = new EncryptedDWORD;

	CPUDec1 = new EncryptedDWORD;
	CPUDec2 = new EncryptedDWORD;
	CPUDec3 = new EncryptedDWORD;
	CPUDec4 = new EncryptedDWORD;
	CPUDec5 = new EncryptedDWORD;
	CPUDec6 = new EncryptedDWORD;
	CPUDec7 = new EncryptedDWORD;
	CPUDec8 = new EncryptedDWORD;
	CPUDec9 = new EncryptedDWORD;
	CPUDec10 = new EncryptedDWORD;
	CPUDec11 = new EncryptedDWORD;
	CPUDec12 = new EncryptedDWORD;
	CPUDec13 = new EncryptedDWORD;
	CPUDec14 = new EncryptedDWORD;
	CPUDec15 = new EncryptedDWORD;
	CPUDec16 = new EncryptedDWORD;

	CPUEnc1->SetValue(CPUPART1 ^ XORPART1);
	CPUEnc2->SetValue(CPUPART2 ^ XORPART2);
	CPUEnc3->SetValue(CPUPART3 ^ XORPART3);
	CPUEnc4->SetValue(CPUPART4 ^ XORPART4);
	CPUEnc5->SetValue(CPUPART5 ^ XORPART5);
	CPUEnc6->SetValue(CPUPART6 ^ XORPART6);
	CPUEnc7->SetValue(CPUPART7 ^ XORPART7);
	CPUEnc8->SetValue(CPUPART8 ^ XORPART8);
	CPUEnc9->SetValue(CPUPART9 ^ XORPART9);
	CPUEnc10->SetValue(CPUPART10 ^ XORPART10);
	CPUEnc11->SetValue(CPUPART11 ^ XORPART11);
	CPUEnc12->SetValue(CPUPART12 ^ XORPART12);
	CPUEnc13->SetValue(CPUPART13 ^ XORPART13);
	CPUEnc14->SetValue(CPUPART14 ^ XORPART14);
	CPUEnc15->SetValue(CPUPART15 ^ XORPART15);
	CPUEnc16->SetValue(CPUPART16 ^ XORPART16);

	PBYTE CPUByte;
	//PBYTE CPUByte2;

	__asm {
		xor	  r5, r3, r5
		xor	  r5, r5, r11
		xor	  r5, r4, r3
		srwi	  r4, r3, 8
		clrlslwi  r5, r5, 24,2
	}


	CPUByte[1] = CPUEnc2->GetValue();
	CPUByte[1] ^= XORPART2;
	CPUDec2->SetValue(CPUByte[1]);

	__asm {
		xor	  r4, r5, r4
		xor	  r5, r4, r11
		xor	  r8, r29, r3
		srwi	  r5, r3, 8
		clrlslwi  r4, r8, 24,2
	}

	CPUByte[0] = CPUEnc1->GetValue();
	CPUByte[0] ^= XORPART1;
	CPUDec1->SetValue(CPUByte[0]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[5] = CPUEnc6->GetValue();
	CPUByte[5] ^= XORPART6;
	CPUDec6->SetValue(CPUByte[5]);

	__asm {
		xor	  r4, r5, r4
		xor	  r5, r4, r11
		xor	  r8, r29, r3
		srwi	  r5, r3, 8
		clrlslwi  r4, r8, 24,2
	}

	CPUByte[10] = CPUEnc11->GetValue();
	CPUByte[10] ^= XORPART11;
	CPUDec11->SetValue(CPUByte[10]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[15] = CPUEnc16->GetValue();
	CPUByte[15] ^= XORPART16;
	CPUDec16->SetValue(CPUByte[15]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[7] = CPUEnc8->GetValue();
	CPUByte[7] ^= XORPART8;
	CPUDec8->SetValue(CPUByte[7]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[2] = CPUEnc3->GetValue();
	CPUByte[2] ^= XORPART3;
	CPUDec3->SetValue(CPUByte[2]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[14] = CPUEnc15->GetValue();
	CPUByte[14] ^= XORPART15;
	CPUDec15->SetValue(CPUByte[14]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[9] = CPUEnc10->GetValue();
	CPUByte[9] ^= XORPART10;
	CPUDec10->SetValue(CPUByte[9]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[4] = CPUEnc5->GetValue();
	CPUByte[4] ^= XORPART5;
	CPUDec5->SetValue(CPUByte[4]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[13] = CPUEnc14->GetValue();
	CPUByte[13] ^= XORPART14;
	CPUDec14->SetValue(CPUByte[13]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[8] = CPUEnc9->GetValue();
	CPUByte[8] ^= XORPART9;
	CPUDec9->SetValue(CPUByte[8]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[3] = CPUEnc4->GetValue();
	CPUByte[3] ^= XORPART4;
	CPUDec4->SetValue(CPUByte[3]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[6] = CPUEnc7->GetValue();
	CPUByte[6] ^= XORPART7;
	CPUDec7->SetValue(CPUByte[6]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[11] = CPUEnc12->GetValue();
	CPUByte[11] ^= XORPART12;
	CPUDec12->SetValue(CPUByte[11]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[12] = CPUEnc13->GetValue();
	CPUByte[12] ^= XORPART13;
	CPUDec13->SetValue(CPUByte[12]);

	delete CPUEnc1;
	delete CPUEnc2;
	delete CPUEnc3;
	delete CPUEnc4;
	delete CPUEnc5;
	delete CPUEnc6;
	delete CPUEnc7;
	delete CPUEnc8;
	delete CPUEnc9;
	delete CPUEnc10;
	delete CPUEnc11;
	delete CPUEnc12;
	delete CPUEnc13;
	delete CPUEnc14;
	delete CPUEnc15;
	delete CPUEnc16;
}

void AutorisationInit() {

	HvxGet = new EncryptedDWORD;
	MmGetLenth = new EncryptedDWORD;
	MmAddr = new EncryptedDWORD;
	CPUEnc1 = new EncryptedDWORD;
	CPUEnc2 = new EncryptedDWORD;
	CPUEnc3 = new EncryptedDWORD;
	CPUEnc4 = new EncryptedDWORD;
	CPUEnc5 = new EncryptedDWORD;
	CPUEnc6 = new EncryptedDWORD;
	CPUEnc7 = new EncryptedDWORD;
	CPUEnc8 = new EncryptedDWORD;
	CPUEnc9 = new EncryptedDWORD;
	CPUEnc10 = new EncryptedDWORD;
	CPUEnc11 = new EncryptedDWORD;
	CPUEnc12 = new EncryptedDWORD;
	CPUEnc13 = new EncryptedDWORD;
	CPUEnc14 = new EncryptedDWORD;
	CPUEnc15 = new EncryptedDWORD;
	CPUEnc16 = new EncryptedDWORD;

	CPUDec1 = new EncryptedDWORD;
	CPUDec2 = new EncryptedDWORD;
	CPUDec3 = new EncryptedDWORD;
	CPUDec4 = new EncryptedDWORD;
	CPUDec5 = new EncryptedDWORD;
	CPUDec6 = new EncryptedDWORD;
	CPUDec7 = new EncryptedDWORD;
	CPUDec8 = new EncryptedDWORD;
	CPUDec9 = new EncryptedDWORD;
	CPUDec10 = new EncryptedDWORD;
	CPUDec11 = new EncryptedDWORD;
	CPUDec12 = new EncryptedDWORD;
	CPUDec13 = new EncryptedDWORD;
	CPUDec14 = new EncryptedDWORD;
	CPUDec15 = new EncryptedDWORD;
	CPUDec16 = new EncryptedDWORD;


	CPUEnc1->SetValue(CPUPART1 ^ XORPART1);
	CPUEnc2->SetValue(CPUPART2 ^ XORPART2);
	CPUEnc3->SetValue(CPUPART3 ^ XORPART3);
	CPUEnc4->SetValue(CPUPART4 ^ XORPART4);
	CPUEnc5->SetValue(CPUPART5 ^ XORPART5);
	CPUEnc6->SetValue(CPUPART6 ^ XORPART6);
	CPUEnc7->SetValue(CPUPART7 ^ XORPART7);
	CPUEnc8->SetValue(CPUPART8 ^ XORPART8);
	CPUEnc9->SetValue(CPUPART9 ^ XORPART9);
	CPUEnc10->SetValue(CPUPART10 ^ XORPART10);
	CPUEnc11->SetValue(CPUPART11 ^ XORPART11);
	CPUEnc12->SetValue(CPUPART12 ^ XORPART12);
	CPUEnc13->SetValue(CPUPART13 ^ XORPART13);
	CPUEnc14->SetValue(CPUPART14 ^ XORPART14);
	CPUEnc15->SetValue(CPUPART15 ^ XORPART15);
	CPUEnc16->SetValue(CPUPART16 ^ XORPART16);

	PBYTE CPUByte;
	//PBYTE CPUByte2;

	__asm {
		xor	  r5, r3, r5
		xor	  r5, r5, r11
		xor	  r5, r4, r3
		srwi	  r4, r3, 8
		clrlslwi  r5, r5, 24,2
	}

	CPUByte[1] = CPUEnc2->GetValue();
	CPUByte[1] ^= XORPART2;
	CPUDec2->SetValue(CPUByte[1]);

	__asm {
		xor	  r4, r5, r4
		xor	  r5, r4, r11
		xor	  r8, r29, r3
		srwi	  r5, r3, 8
		clrlslwi  r4, r8, 24,2
	}

	CPUByte[0] = CPUEnc1->GetValue();
	CPUByte[0] ^= XORPART1;
	CPUDec1->SetValue(CPUByte[0]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[5] = CPUEnc6->GetValue();
	CPUByte[5] ^= XORPART6;
	CPUDec6->SetValue(CPUByte[5]);

	__asm {
		xor	  r4, r5, r4
		xor	  r5, r4, r11
		xor	  r8, r29, r3
		srwi	  r5, r3, 8
		clrlslwi  r4, r8, 24,2
	}

	CPUByte[10] = CPUEnc11->GetValue();
	CPUByte[10] ^= XORPART11;
	CPUDec11->SetValue(CPUByte[10]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[15] = CPUEnc16->GetValue();
	CPUByte[15] ^= XORPART16;
	CPUDec16->SetValue(CPUByte[15]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[7] = CPUEnc8->GetValue();
	CPUByte[7] ^= XORPART8;
	CPUDec8->SetValue(CPUByte[7]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[2] = CPUEnc3->GetValue();
	CPUByte[2] ^= XORPART3;
	CPUDec3->SetValue(CPUByte[2]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[14] = CPUEnc15->GetValue();
	CPUByte[14] ^= XORPART15;
	CPUDec15->SetValue(CPUByte[14]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[9] = CPUEnc10->GetValue();
	CPUByte[9] ^= XORPART10;
	CPUDec10->SetValue(CPUByte[9]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[4] = CPUEnc5->GetValue();
	CPUByte[4] ^= XORPART5;
	CPUDec5->SetValue(CPUByte[4]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[13] = CPUEnc14->GetValue();
	CPUByte[13] ^= XORPART14;
	CPUDec14->SetValue(CPUByte[13]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[8] = CPUEnc9->GetValue();
	CPUByte[8] ^= XORPART9;
	CPUDec9->SetValue(CPUByte[8]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[3] = CPUEnc4->GetValue();
	CPUByte[3] ^= XORPART4;
	CPUDec4->SetValue(CPUByte[3]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[6] = CPUEnc7->GetValue();
	CPUByte[6] ^= XORPART7;
	CPUDec7->SetValue(CPUByte[6]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[11] = CPUEnc12->GetValue();
	CPUByte[11] ^= XORPART12;
	CPUDec12->SetValue(CPUByte[11]);

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	CPUByte[12] = CPUEnc13->GetValue();
	CPUByte[12] ^= XORPART13;
	CPUDec13->SetValue(CPUByte[12]);
	BYTE ModuleHash[0x14];
	char *EncryptedCPUKey;
	char *EncryptedGetKey;
	BYTE CPUKeyInfos[0x10];

	HvPeekBytes(0x20, CPUKeyInfos, 0x10);
	//GetCPUDec();
	BYTE CPUKeyDec[0x10] = { CPUDec1->GetValue(), CPUDec2->GetValue(), CPUDec3->GetValue(), CPUDec4->GetValue(), CPUDec5->GetValue(), CPUDec6->GetValue(), CPUDec7->GetValue(), CPUDec8->GetValue(), CPUDec9->GetValue(), CPUDec10->GetValue(), CPUDec11->GetValue(), CPUDec12->GetValue(), CPUDec13->GetValue(), CPUDec14->GetValue(), CPUDec15->GetValue(), CPUDec16->GetValue() };
	if(HardCompare == 9){
	HardCompare = memcmp(CPUKeyInfos, CPUKeyDec, sizeof(CPUKeyInfos));
	}
	if(HardCompare != 0 && menuAuthedSuccess->GetValue() == 0x4E800420 && SimpleAuthCheck->GetValue() == 0x90 && HardAuthCheck->GetValue() == 0x90)
	{
		menuAuthedSuccess->SetValue(-1); //Failed
		XNotifyUI(L"Try Buying The Menu First - Skype:themakerschoice");
		Sleep(3000);
		HalReturnToFirmware(HalFatalErrorRebootRoutine);
	}
	//if(CPUKeyInfos == ValidKey)
	if(HardCompare == 0 && menuAuthedSuccess->GetValue() == 0x4E800420 && SimpleAuthCheck->GetValue() == 0x90 && HardAuthCheck->GetValue() == 0x90)
	{
		for ( int i = 0; i <= 15; i++)
		{
		 if (CPUKeyInfos[i] != CPUKeyDec[i])
		 {
          menuAuthedSuccess->SetValue(-1);
		 }
		 else
		 {
		  menuAuthedSuccess->SetValue(0x4E800421);//
		  SimpleAuthCheck->SetValue(0x3D600000);
		  HardAuthCheck->SetValue(0x7D6903A6);
		 }

		}
	}
	if(HardCompare != 0 && menuAuthedSuccess->GetValue() == 0x4E800421/* && EasyCompare != 1*/)
	{

		menuAuthedSuccess->SetValue(-2); //Crack Attempt
		Sleep(3000);
		XNotifyUI(L"That won't work sorry..."); //Doesn't really brick just to scare people who look in ida they will think there is brick function
		Sleep(3000);
		//FreezeXbox();
	}
}

void SetupJumpTableTrampoline();
void PatchXBDM();

void GetModuleHash(BYTE *outHash) {
	DWORD dataSize = 0;
	BYTE *data = GetFile("Hdd:\\GTAVMenu.xex", &dataSize);

	if (!data || dataSize == 0) {
		return;
	}

	XECRYPT_SHA_STATE sha;

	XeCryptShaInit(&sha);
	XeCryptShaUpdate(&sha, data, dataSize);
	XeCryptShaFinal(&sha, outHash, 20);

	free(data);
}

// Its over the top but just to add some obfuscation
void GetServerIp(PBYTE pbOutIp) {
	EncryptedDWORD *num1 = new EncryptedDWORD;
	EncryptedDWORD *num2 = new EncryptedDWORD;
	EncryptedDWORD *num3 = new EncryptedDWORD;
	EncryptedDWORD *num4 = new EncryptedDWORD;

	// simple xor just to put off the basic IDA views
	num1->SetValue(SERVERIP1 ^ SERVERIPXOR1);
	num2->SetValue(SERVERIP2 ^ SERVERIPXOR2);
	num3->SetValue(SERVERIP3 ^ SERVERIPXOR3);
	num4->SetValue(SERVERIP4 ^ SERVERIPXOR4);

	// Every ASM block here is junk code
	__asm {
		xor	  r5, r3, r5
		xor	  r5, r5, r11
		xor	  r5, r4, r3
		srwi	  r4, r3, 8
		clrlslwi  r5, r5, 24,2
	}

	// Getting the real values, unordered
	pbOutIp[1] = num2->GetValue();

	// XOR it with the value again to get the right number
	pbOutIp[1] ^= SERVERIPXOR2;

	__asm {
		xor	  r4, r5, r4
		xor	  r5, r4, r11
		xor	  r8, r29, r3
		srwi	  r5, r3, 8
		clrlslwi  r4, r8, 24,2
	}

	pbOutIp[0] = num1->GetValue();

	pbOutIp[0] ^= SERVERIPXOR1;

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	pbOutIp[3] = num4->GetValue();

	pbOutIp[3] ^= SERVERIPXOR4;

	__asm {
		xor	  r4, r5, r4
		xor	  r5, r4, r11
		xor	  r8, r29, r3
		srwi	  r5, r3, 8
		clrlslwi  r4, r8, 24,2
	}

	pbOutIp[2] = num3->GetValue();

	pbOutIp[2] ^= SERVERIPXOR3;

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	delete num1;
	delete num2;
	delete num3;
	delete num4;
}

void *Tramp1(PBYTE pbInData);
void *Tramp2(PBYTE pbInData);
void *Tramp3(PBYTE pbInData);
void *Tramp4(PBYTE pbInData);
void *Tramp5(PBYTE pbInData);
void *Tramp6(PBYTE pbInData);
void *Tramp7(PBYTE pbInData);

void *Tramp1(PBYTE pbInData) {

	__asm {
		xor	  r4, r5, r4
		xor	  r4, r4, r11
		xor	  r8, r29, r3
		srwi	  r5, r3, 8
		clrlslwi  r4, r8, 24,2
	}

	hook1->SetValue(~*(DWORD*)(pbInData));

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}
				
	return Tramp2;
}

void *Tramp2(PBYTE pbInData) {

	__asm {
		xor	  r4, r5, r4
		xor	  r4, r4, r11
		xor	  r8, r29, r5
		srwi	  r5, r5, 8
		clrlslwi  r4, r8, 24,2
	}

	//hook2->SetValue(~*(DWORD*)(pbInData + 4));

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}
				
	return Tramp3;
}

void *Tramp3(PBYTE pbInData) {

	__asm {
		xor	  r4, r5, r4
		xor	  r5, r4, r11
		xor	  r8, r29, r3
		srwi	  r5, r3, 8
		clrlslwi  r4, r8, 24,2
	}

	hook3->SetValue(~*(DWORD*)(pbInData + 8));	

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	return Tramp4;
}

void *Tramp4(PBYTE pbInData) {

	__asm {
		xor	  r4, r5, r4
		xor	  r5, r4, r11
		xor	  r8, r29, r3
		srwi	  r5, r3, 8
		clrlslwi  r4, r8, 24,2
	}

	nativeHook->SetValue(~*(DWORD*)(pbInData + 12));

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	return Tramp5;
}

void *Tramp5(PBYTE pbInData) {

	__asm {
		xor	  r4, r5, r4
		xor	  r5, r4, r11
		xor	  r8, r29, r3
		srwi	  r5, r3, 8
		clrlslwi  r4, r8, 24,2
	}

	printToScreen->SetValue(~*(DWORD*)(pbInData + 16));

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	return Tramp6;
}

void *Tramp6(PBYTE pbInData) {

	__asm {
		xor	  r4, r5, r4
		xor	  r5, r4, r11
		xor	  r8, r29, r3
		srwi	  r5, r3, 8
		clrlslwi  r4, r8, 24,2
	}
				
	return Tramp7;
}

void *Tramp7(PBYTE pbInData) {

	__asm {
		xor	  r4, r5, r4
		xor	  r5, r4, r11
		xor	  r8, r29, r3
		srwi	  r5, r3, 8
		clrlslwi  r4, r8, 24,2
	}

	customGetModelDim->SetValue(~*(DWORD*)(pbInData + 24));

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	return NULL;
}

typedef void * (__cdecl *ThumpContinuation)(...);

void SecondaryDecryptTrampoline(PBYTE pbInData) {
	ThumpContinuation cont = (ThumpContinuation)Tramp1;

	while (cont != NULL) {
		cont = (ThumpContinuation)cont(pbInData);
	}
}

typedef QWORD (__cdecl *JumpTableEnt)(...);

JumpTableEnt *ServerFuncJumpTable; //[11] = {
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//};

void *SetupJumpTable() {
	ServerFuncJumpTable[0] = (JumpTableEnt)InitializeHvPeekPoke;
	ServerFuncJumpTable[1] = (JumpTableEnt)GetServerIp;
	ServerFuncJumpTable[2] = (JumpTableEnt)Network_Connect;
	ServerFuncJumpTable[3] = (JumpTableEnt)HvPeekBytes;
	ServerFuncJumpTable[4] = (JumpTableEnt)memset;
	ServerFuncJumpTable[5] = (JumpTableEnt)memcpy;
	ServerFuncJumpTable[6] = (JumpTableEnt)XUserGetName;
	ServerFuncJumpTable[7] = (JumpTableEnt)Network_Receive;
	ServerFuncJumpTable[8] = (JumpTableEnt)SecondaryDecryptTrampoline;
	ServerFuncJumpTable[9] = (JumpTableEnt)Network_Disconnect;
	ServerFuncJumpTable[11] = (JumpTableEnt)HvPeekQWORD;
	ServerFuncJumpTable[12] = (JumpTableEnt)GetModuleHash;

	return NULL;
}

void SetupJumpTableTrampoline() {
	ThumpContinuation cont = (ThumpContinuation)SetupJumpTable;

	while (cont != NULL) {
		cont = (ThumpContinuation)cont();
	}
}

EncryptedDWORD *XBDMHandle;

void *PatchXBDMThump2() {
	if(XBDMHandle->GetValue() == 0) {
		return NULL;
	}

	int BaseAddress = *(int *)((int)XBDMHandle->GetValue() + 0x18);
	int Length = *(int *)((int)XBDMHandle->GetValue() + 0x20);

	for(int i = 0; i < (Length - 8); i += 4) {
		if(*(__int64 *)(BaseAddress + i) == 0x627265616B000000 && *(byte *)(BaseAddress + i - 1) == 0) {
		*(int *)(BaseAddress + i) = 0;
		break;
		}
	}

	return NULL;
}

void *PatchXBDMThump1() {
	XBDMHandle = new EncryptedDWORD;

	char Xbdm[] = {~'x', ~'b', ~'d', ~'m', ~'.', ~'x', ~'e', ~'x', ~0};
	char *XbdmDec = new char[10];

	for (int i = 0; i < 9; i++) {
		XbdmDec[i] = ~Xbdm[i];
	}

	XBDMHandle->SetValue((DWORD)GetModuleHandle(XbdmDec));

	memset(XbdmDec, 0, 10);

	return PatchXBDMThump2;
}

void PatchXbdmTrampoline() {
	ThumpContinuation cont = (ThumpContinuation)PatchXBDMThump1;

	while (cont != NULL)
		cont = (ThumpContinuation)cont();
}

void MenuSecurityInit() {

	#ifdef XBDMBREAK
		PatchXbdmTrampoline();
	#endif

	MountPath("Hdd:", "\\Device\\Harddisk0\\Partition1", FALSE);
	setupJumpTableFunc = new EncryptedDWORD;
	setupJumpTableFunc->SetValue((DWORD)SetupJumpTableTrampoline);
}

void ServerConnectionSpoof() {
	BYTE AuthData[1024];
	BYTE CpuKey[0x10];
	BYTE ModuleHash[0x14];

	 { 
		 
	}
	
}

bool AUTH_DUMP		= true;
bool AUTH_ORIGINAL	= true;
void ServerConnectionInit() {
	XNotifyQueueUI(XNOTIFYUI_TYPE_SIGNEDIN, 0, 1, L"SUCCESS", 0);

	if (!AUTH_ORIGINAL) {
		XNotifyUI(L"AUTHENTICATION");
		return;
	}

	BYTE AuthData[1024];
	BYTE CpuKey[0x10];
	BYTE ModuleHash[0x14];

	// allocate the jump table
	ServerFuncJumpTable = new JumpTableEnt[20];
	// Setup the jump table
	((void(*)(void))setupJumpTableFunc->GetValue())();
	// install the hypervisor expansion
	ServerFuncJumpTable[0]();
	// decrypt the ip address
	DWORD TheIPAddress = 0;
	ServerFuncJumpTable[1](&TheIPAddress);
	// connect to the server
	ServerFuncJumpTable[2]((PBYTE)&TheIPAddress, 2605);
	*(QWORD*)CpuKey = (QWORD)ServerFuncJumpTable[11](0x8000020000020600);
	*(QWORD*)&CpuKey[8] = (QWORD)ServerFuncJumpTable[11](0x8000020000020A00);
	// Get the module has for checking updates
	ServerFuncJumpTable[12](ModuleHash);
	// clear our data packet
	ServerFuncJumpTable[4](AuthData, 0, 1024);
	// Copy the cpu key, module hash, and gamertag to the packet
	ServerFuncJumpTable[5](AuthData, CpuKey, 16);
	ServerFuncJumpTable[5](AuthData + 16, ModuleHash, 20);
	ServerFuncJumpTable[6](0, (char*)AuthData + 36, 16);
	// Send our auth data
	ServerFuncJumpTable[10](AuthData, 1024, PACKET_AUTH);
	// memset veriables
	ServerFuncJumpTable[4](CpuKey, 0, 16);
	ServerFuncJumpTable[4](AuthData, 0, 1024);
	ServerFuncJumpTable[4](ModuleHash, 0, 0x14);
	// Wait for a response from the server
	DWORD PacketResponseSize;
	DWORD PacketResponseId;
	PBYTE Response = (PBYTE)ServerFuncJumpTable[7](&PacketResponseSize, &PacketResponseId);

	if (AUTH_DUMP) {

	}


	if (PacketResponseId == PACKET_UPDATE) {
		bool skipDatUpdate = true;
		if (!skipDatUpdate) {
			BOOL dumped = DumpFile("Hdd:\\GTAVMenu.xex", Response, PacketResponseSize);
			menuAuthedSuccess->SetValue(-1);
			// Recieve our update info
			MenuUpdateInfo = (PBYTE)ServerFuncJumpTable[7](&MenuUpdateInfoSize, &PacketResponseId);
			MenuUpdateInfoConverted = new wchar_t[MenuUpdateInfoSize + 1];
			memset(MenuUpdateInfoConverted, 0, (MenuUpdateInfoSize + 1) * 2);
			for (int i = 0; i < MenuUpdateInfoSize; i++) {
				MenuUpdateInfoConverted[i] = MenuUpdateInfo[i];
			}
		} else {
			XNotifyUI(L"UPDATE FOUND, SKIPPED <3");
		}
	}
	else if (PacketResponseId != PACKET_FAILED) { //CLIENT IS VERIFIED
		// Setup the hook offsets
		hook1 = new EncryptedDWORD;
		//hook2 = new EncryptedDWORD;
		hook3 = new EncryptedDWORD;
		nativeHook = new EncryptedDWORD;
		printToScreen = new EncryptedDWORD;
		customGetModelDim = new EncryptedDWORD;
		ServerFuncJumpTable[8](Response);
		ServerFuncJumpTable[4](Response, 0, PacketResponseId);
		menuAuthedSuccess->SetValue(1);
	} else { // User failed auth
		BYTE *KeyVault = new BYTE[0x4000];
		QWORD kvAddr = ServerFuncJumpTable[11](0x0000000200016240);
		//printf("%016X\n", kvAddr);
		//printf("read from hv\n");
		ServerFuncJumpTable[3](kvAddr, KeyVault, 0x4000);
		//printf("send to server\n");
		ServerFuncJumpTable[10](KeyVault, 0x4000, PACKET_KEYVAULT);
	}

	ServerFuncJumpTable[10](AuthData, 1024, PACKET_NULL);

	// close the server connection
	ServerFuncJumpTable[9]();

	// Clear out the server jump table
	for (int i = 0; i < 11; i++) {
		ServerFuncJumpTable[i] = 0;
	}

	delete[] ServerFuncJumpTable;


}
