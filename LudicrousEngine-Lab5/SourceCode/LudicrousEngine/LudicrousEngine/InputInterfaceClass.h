#pragma once
#include <Windows.h>
#include <sstream>
class InputInterfaceClass
{
public:
	InputInterfaceClass();
	~InputInterfaceClass();

	void Initialize();
	void GetKeyDown(UINT keyCode);
	void GetKeyUp(UINT keyCode);
	void ShutDown();
	bool IsKeyPressed(UINT keyCode);
	bool IsButtonPressed(UINT keyCode);
	LPSTR LeftMouseDown(UINT mouseButtonNum);
	LPSTR LeftMouseUp(UINT mouseButtonNum);

private:
	bool keyStates[256];
};

