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

void InputInterfaceClass::GetKeyDown(UINT keyCode, LPARAM lParam) {
	
	LPSTR keyStr = new char[10];
	GetKeyNameTextA(lParam, keyStr, 10);
	keyStates[keyCode] = true;
	GetKeyState(keyCode);
	std::string keyOutput = "Key Down = ";
	keyOutput.append(keyStr);
}

void InputInterfaceClass::GetKeyUp(UINT keyCode, LPARAM lParam) {
	LPSTR keyStr = new char[10];
	GetKeyNameTextA(lParam, keyStr, 10);
	keyStates[keyCode] = false;
	GetKeyState(keyCode);
	std::string keyOutput = "Key Up = ";
	keyOutput.append(keyStr);
}

bool InputInterfaceClass::IsKeyPressed(UINT keyCode) {
	return keyStates[keyCode];
}

//void MouseDown(UINT mouseButtonNum, LPARAM lParam) {}
//void MouseUp(UINT mouseButtonNum, LPARAM lParam) {}

void InputInterfaceClass::ShutDown() {
}
