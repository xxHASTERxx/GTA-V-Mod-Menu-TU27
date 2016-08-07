#ifndef __INPUT_H_
#define __INPUT_H_


#pragma once

#include <xtl.h>
#include <vector>
using namespace std;

class Input {

public:
bool rightBumperDown;
bool leftBumperDown;
bool xButtonDown;
bool dPadLeftDown;
bool aButtonDown;
bool bButtonDown;
bool bButtonLSDown;
bool bButtonRSDown;
bool dPadUp;
bool dPadDown;
bool dPadRightDown;

Input();
~Input();

XINPUT_STATE xstate;

void UpdateInput();

bool LeftBumperDown();
bool RightBumperDown();
bool DpadRightDown();
bool XButtonDown();
bool DPadLeftDown();
bool AButtonDown();
bool BButtonDown();
bool BButtonLSDown();
bool BButtonRSDown();
bool DpadDown();
bool DpadUp();
};

#endif
