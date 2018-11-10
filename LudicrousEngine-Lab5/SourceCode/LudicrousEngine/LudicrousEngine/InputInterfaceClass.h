#pragma once
#include <Windows.h>
#include <sstream>
class InputInterfaceClass
{
public:
	InputInterfaceClass();
	~InputInterfaceClass();

	void Initialize();
	void GetKeyDown(UINT keyCode, LPARAM lParam);
	void GetKeyUp(UINT keyCode, LPARAM lParam);
	void ShutDown();
	bool IsKeyPressed(UINT keyCode);

private:
	bool keyStates[256];
};

