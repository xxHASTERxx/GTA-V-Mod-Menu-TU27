#ifndef __ENCRYPTEDCHAR_H_
#define __ENCRYPTEDCHAR_H_

#pragma once
#include <stdio.h>
#include <time.h>
#include <xtl.h>

class EncryptedCHAR {
private:
	WCHAR XORValue;
	WCHAR Value;

	WCHAR RandFuncXOR;
	int (__cdecl *RandFunc)();
	void (__cdecl *SRandFunc)(int);
	int (__cdecl *TimeFunc)(int);

public:
	EncryptedCHAR() {

		RandFunc = (int (__cdecl *)())(rand);
		SRandFunc = (void (__cdecl *)(int))(srand);
		TimeFunc = (int (__cdecl *)(int))(time);

		// use time value as seed
		int time = CallFunc(2, 0);

		//srand - seed our random number
		CallFunc(1, time);
		
		RandFuncXOR = CallFunc(0, 0);
		XORValue = CallFunc(0, 0);
	}

	~EncryptedCHAR() {
	}

	virtual void SetValue(WCHAR val) {
		__asm {
			mr	  r6, r7
			insrwi	  r6, r7, 16,0
			rlwinm	  r5, r7, 24,16,23
			extlwi	  r4, r6, 16,8
			or	  r5, r4, r5
			or	  r11, r3, r9
		}

		Value = val ^ XORValue;

		__asm {
			mr	  r7, r9
			insrwi	  r7, r9, 16,0
			rlwinm	  r6, r9, 24,16,23
			extlwi	  r5, r7, 16,8
			or	  r4, r5, r6
			or	  r5, r4, r10
		}
	}

	virtual char GetValue() {

		__asm {
			mullw	  r11, r11, r30
			addi	  r11, r11, 1
			mullw	  r10, r11, r30
			srwi	  r5, r11, 8
			addi	  r11, r10, 1
			mullw	  r10, r11, r30
		}

		WCHAR val = Value ^ XORValue;

		//swap out the xor value every time
		XORValue = CallFunc(0, 0);
		Value = val ^ XORValue;

		__asm {
			srwi	  r4, r11, 8
			addi	  r11, r10, 1
			mullw	  r10, r11, r30
			addi	  r10, r10, 1
			srwi	  r5, r11, 8
			srwi	  r7, r10, 8
		}

		return val;
	}

	virtual int CallFunc(WCHAR FuncNum, WCHAR arg1) {

		int returnVal = RandFunc();

		switch (FuncNum) {
		case 0:
			returnVal = RandFunc();
			break;
		case 1:
			SRandFunc(arg1);
			break;
		case 2:
			returnVal = TimeFunc(arg1);
			break;
		default:
			returnVal = RandFunc();
			break;
		}

		return returnVal;
	}
};

#endif
