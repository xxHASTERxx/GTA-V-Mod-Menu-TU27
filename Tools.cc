#include "Tools.h"
#define printf




DWORD XNotifyType = 0x22;

VOID XNotifyDoQueueUI(PWCHAR displaytext) {
	XNotifyQueueUI(XNotifyType, 0, 2, displaytext, 0);
}

VOID XNotifyUI(PWCHAR pwszStringParam) {
	if (KeGetCurrentProcessType() != 1) {
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)XNotifyDoQueueUI, (LPVOID)pwszStringParam, 0, NULL);
	} else {
		XNotifyDoQueueUI(pwszStringParam);
	}
}

BOOL DumpFile(CHAR *szFileName, BYTE *pbData, DWORD dwSize) {
	FILE *f = fopen(szFileName, "wb");

	if (f) {
		fwrite(pbData, 1, dwSize, f);
		fflush(f);
		fclose(f);
		return TRUE;
	}

	return FALSE;
}


BYTE *GetFile(CHAR *szPath, PDWORD pdwOutSize) {
	FILE *f = fopen(szPath, "rb");
	if (!f) {
		*pdwOutSize = 0;
		return NULL;
	}

	fseek(f, 0, SEEK_END);
	*pdwOutSize = ftell(f);
	rewind(f);

	BYTE *pbReturnData = (BYTE*)malloc(*pdwOutSize);
	fread(pbReturnData, 1, *pdwOutSize, f);
	fclose(f);

	return pbReturnData;
}

HRESULT SetMemory(LPVOID lpDest, LPVOID lpSrc, DWORD dwLength) {
	memcpy(lpDest, lpSrc, dwLength);
	return ERROR_SUCCESS;
}

DWORD ResolveFunction(PCHAR modname, DWORD ord) {
	DWORD ret = 0, ptr2 = 0;
	HANDLE hand;
	ret = XexGetModuleHandle(modname, &hand); //xboxkrnl.exe xam.dll?
	if (ret == 0) {
		ret = XexGetProcedureAddress(hand, ord, &ptr2);
		if (ptr2 != 0)
			return ptr2;
	}
	return 0; // function not found
}

VOID PatchInJump(PDWORD addr, DWORD dest, BOOL linked) {
	if (dest & 0x8000) // If bit 16 is 1
		addr[0] = 0x3D600000 + (((dest >> 16) & 0xFFFF) + 1); // lis %r11, dest>>16 + 1
	else
		addr[0] = 0x3D600000 + ((dest >> 16) & 0xFFFF); // lis %r11, dest>>16

	addr[1] = 0x396B0000 + (dest & 0xFFFF); // addi%r11, %r11, dest&0xFFFF
	addr[2] = 0x7D6903A6; // mtctr%r11

	if (linked)
		addr[3] = 0x4E800421; // bctrl
	else
		addr[3] = 0x4E800420; // bctr
	__dcbst(0, addr);
	__sync();
}

HRESULT doMountPath(const char* szDrive, const char* szDevice, const char* sysStr) {
	CHAR szDestinationDrive[MAX_PATH];
	sprintf_s(szDestinationDrive, MAX_PATH, sysStr, szDrive);
	STRING DeviceName = MAKE_STRING(szDevice);
	STRING LinkName = MAKE_STRING(szDestinationDrive);
	ObDeleteSymbolicLink(&LinkName);
	return (HRESULT)ObCreateSymbolicLink(&LinkName, &DeviceName);
}

HRESULT MountPath(const char* szDrive, const char* szDevice, BOOL both) {
	HRESULT res;
	if (both) {
		res = doMountPath(szDrive, szDevice, "\\System??\\%s");
		res = doMountPath(szDrive, szDevice, "\\??\\%s");
	} else {
		if (KeGetCurrentProcessType() == 2)	 res = doMountPath(szDrive, szDevice, "\\System??\\%s");
		else								 res = doMountPath(szDrive, szDevice, "\\??\\%s");
	}
	return res;
}


DWORD PatchModuleImport(CHAR* Module, CHAR* ImportedModuleName, DWORD Ordinal, DWORD PatchAddress) {
	LDR_DATA_TABLE_ENTRY* moduleHandle = (LDR_DATA_TABLE_ENTRY*)GetModuleHandle(Module);
	return (moduleHandle == NULL) ? S_FALSE : PatchModuleImport(moduleHandle, ImportedModuleName, Ordinal, PatchAddress);
}

DWORD PatchModuleImport(PLDR_DATA_TABLE_ENTRY Module, CHAR* ImportedModuleName, DWORD Ordinal, DWORD PatchAddress) {

	// First resolve this imports address
	DWORD address = (DWORD)ResolveFunction(ImportedModuleName, Ordinal);
	if (address == NULL)
		return S_FALSE;

	// Get our header field from this module
	VOID* headerBase = Module->XexHeaderBase;
	PXEX_IMPORT_DESCRIPTOR importDesc = (PXEX_IMPORT_DESCRIPTOR)RtlImageXexHeaderField(headerBase, 0x000103FF);
	if (importDesc == NULL)
		return S_FALSE;

	// Our result
	DWORD result = 2; // No occurances patched

	// Get our string table position
	CHAR* stringTable = (CHAR*)(importDesc + 1);

	// Get our first entry
	XEX_IMPORT_TABLE_ORG* importTable = (XEX_IMPORT_TABLE_ORG*)(stringTable + importDesc->NameTableSize);

	// Loop through our table
	for (DWORD x = 0; x < importDesc->ModuleCount; x++) {

		// Go through and search all addresses for something that links
		DWORD* importAdd = (DWORD*)(importTable + 1);
		for (DWORD y = 0; y < importTable->ImportTable.ImportCount; y++) {

			// Check the address of this import
			DWORD value = *((DWORD*)importAdd[y]);
			if (value == address) {

				// We found a matching address address
				SetMemory((DWORD*)importAdd[y], &PatchAddress, 4);
				DWORD newCode[4];
				PatchInJump(newCode, PatchAddress, FALSE);
				SetMemory((DWORD*)importAdd[y + 1], newCode, 16);

				// We patched at least one occurence
				result = S_OK;
			}
		}

		// Goto the next table
		importTable = (XEX_IMPORT_TABLE_ORG*)(((BYTE*)importTable) + importTable->TableSize);
	}

	// Return our result
	return result;
}

#ifdef DEVKIT
VOID PatchInJumpDev(DWORD addr, DWORD dest, BOOL linked) {
	DWORD Data[4];
	// Devkits dont like to be violated in thier code sections directly,
	// this is a workaround.
	//printf("PatchInJump\n");
	PatchInJump(Data, dest, linked);

	DWORD cbRet = 0;
	//printf("DmSetMemory\n");
	HRESULT hr = (HRESULT)DmSetMemory((LPVOID)addr, 16, Data, &cbRet);

	//printf("hr = %08X cbRet = %08X\n", hr, cbRet);

	if (hr != XBDM_NOERR || cbRet != 16) {
		//printf("DmSetMemory failed. HRESULT = %08X cbRet = %d\n", hr, cbRet);
	}
}
#endif

VOID __declspec(naked) GLPR_FUN(VOID) {
	__asm {
		std     r14, -0x98(sp)
			std     r15, -0x90(sp)
			std     r16, -0x88(sp)
			std     r17, -0x80(sp)
			std     r18, -0x78(sp)
			std     r19, -0x70(sp)
			std     r20, -0x68(sp)
			std     r21, -0x60(sp)
			std     r22, -0x58(sp)
			std     r23, -0x50(sp)
			std     r24, -0x48(sp)
			std     r25, -0x40(sp)
			std     r26, -0x38(sp)
			std     r27, -0x30(sp)
			std     r28, -0x28(sp)
			std     r29, -0x20(sp)
			std     r30, -0x18(sp)
			std     r31, -0x10(sp)
			stw     r12, -0x8(sp)
			blr
	}
}
//Will need to change the memory editing to devkit
DWORD relinkGPLR(DWORD offset, PDWORD saveStubAddr, PDWORD orgAddr) {
	DWORD inst = 0, repl, *saver = (PDWORD)GLPR_FUN;
	// if the msb is set in the instruction, set the rest of the bits to make the int negative
	if (offset & 0x2000000)
		offset = offset | 0xFC000000;
	repl = orgAddr[offset / 4];
	for (int i = 0; i < 20; i++)
		if (repl == saver[i]) {
			int newOffset = (int)&saver[i] - (int)saveStubAddr;
			inst = 0x48000001 | (newOffset & 0x3FFFFFC);
		}
	return inst;
}

VOID hookFunctionStartEx(...) {
	DWORD *addr, *saveStub, dest;
	__asm {
		mr addr, r3
			mr saveStub, r4
			mr dest, r5
	}
	if (saveStub != NULL && addr != NULL) {
		DWORD addrReloc = (DWORD)(&addr[4]);// replacing 4 instructions with a jump, this is the stub return address
		// build the stub
		// make a jump to go to the original function start+4 instructions
		if (addrReloc & 0x8000) // If bit 16 is 1
			saveStub[0] = 0x3D600000 + (((addrReloc >> 16) & 0xFFFF) + 1); // lis %r11, dest>>16 + 1
		else
			saveStub[0] = 0x3D600000 + ((addrReloc >> 16) & 0xFFFF); // lis %r11, dest>>16

		saveStub[1] = 0x396B0000 + (addrReloc & 0xFFFF); // addi %r11, %r11, dest&0xFFFF
		saveStub[2] = 0x7D6903A6; // mtctr %r11
		// instructions [3] through [6] are replaced with the original instructions from the function hook
		// copy original instructions over, relink stack frame saves to local ones
		for (int i = 0; i < 4; i++) {
			if ((addr[i] & 0x48000003) == 0x48000001) // branch with link
				saveStub[i + 3] = relinkGPLR((addr[i] & ~0x48000003), &saveStub[i + 3], &addr[i]);
			else
				saveStub[i + 3] = addr[i];
		}
		saveStub[7] = 0x4E800420; // bctr
		__dcbst(0, saveStub);
		__sync();
		__isync();


	#ifdef DEVKIT
		PatchInJumpDev((DWORD)addr, dest, FALSE);
	#else
		PatchInJump((PDWORD)addr, dest, FALSE);
	#endif
	}
}