#include "Input.h"

Input::Input() {
}

Input::~Input() {
}

void Input::UpdateInput() {
	if (XInputGetState(0, &xstate) == ERROR_SUCCESS)
	{
		dPadLeftDown = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) > 0;
		xButtonDown = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_X) > 0;
		rightBumperDown = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) > 0;
		leftBumperDown = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) > 0;
		aButtonDown = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_A) > 0;
		bButtonDown = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_B) > 0;
		bButtonLSDown = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) > 0;
		bButtonRSDown = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) > 0;
		dPadUp = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) > 0;
		dPadDown = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) > 0;
		dPadRightDown = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) > 0;
	}
}

bool Input::LeftBumperDown() {
	return leftBumperDown;
}

bool Input::DpadRightDown() {
	return dPadRightDown;
}

bool Input::DpadDown() {
	return dPadDown;
}

bool Input::DpadUp() {
	return dPadUp;
}

bool Input::RightBumperDown() {
	return rightBumperDown;
}

bool Input::XButtonDown() {
	return xButtonDown;
}

bool Input::DPadLeftDown() {
	return dPadLeftDown;
}

bool Input::AButtonDown() {
	return aButtonDown;
}

bool Input::BButtonDown() {
	return bButtonDown;
}

bool Input::BButtonLSDown() {
	return bButtonLSDown;
}

bool Input::BButtonRSDown() {
	return bButtonRSDown;
}
