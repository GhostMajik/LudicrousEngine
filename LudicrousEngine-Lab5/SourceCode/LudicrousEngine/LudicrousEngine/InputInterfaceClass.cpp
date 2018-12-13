#include "InputInterfaceClass.h"

InputInterfaceClass::InputInterfaceClass()
{
}


InputInterfaceClass::~InputInterfaceClass()
{
}

void InputInterfaceClass::Initialize() {
	for (int x = 0; x < 256; x++) {
		keyStates[x] = false;
	}
}

void InputInterfaceClass::GetKeyDown(UINT keyCode) {
	keyStates[keyCode] = true;
}

void InputInterfaceClass::GetKeyUp(UINT keyCode) {
	keyStates[keyCode] = false;
}

bool InputInterfaceClass::IsKeyPressed(UINT keyCode) {
	return keyStates[keyCode];
}

bool InputInterfaceClass::IsButtonPressed(UINT keyCode)
{
	return false;
}

LPSTR InputInterfaceClass::LeftMouseDown(UINT mouseButtonNum) {
	if (GetKeyState((VK_LBUTTON) & 0x100) == true) {
		return "LeftMouse";
	}

}
LPSTR InputInterfaceClass::LeftMouseUp(UINT mouseButtonNum) {
	if (GetKeyState((VK_RBUTTON) & 0x100) == true) {
		return "RightMouse";
	}
}

void InputInterfaceClass::ShutDown() {

}
