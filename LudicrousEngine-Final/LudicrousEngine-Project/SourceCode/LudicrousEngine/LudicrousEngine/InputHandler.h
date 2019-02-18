#pragma once
#include <windows.h>  
#include <stdlib.h>  
#include <string.h>  
#include <tchar.h>
#include "EventManager.h"

class InputHandler {

public:
	bool buttons[256] = { false };
	InputHandler();
	void GetInput(UINT uMsg, EventManager eventManager, WPARAM wParam, LPARAM lParam);
	~InputHandler();


};