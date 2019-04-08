#include "InputHandler.h"

InputHandler::InputHandler() {
	
}

//create input event handler to handle messages from main that 
void InputHandler::GetInput(UINT uMsg, EventManager eventManager, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_KEYDOWN:
	
		//Input->GetKeyDown((UINT)wParam);
		break;
	
	case WM_KEYUP:
	
		//Input->GetKeyUp((UINT)wParam);
		break;
	
	case WM_LBUTTONDOWN:
	
		OutputDebugStringW(L"Left Mouse Down Output. \n");
		//Input->LeftMouseDown((UINT)wParam);
		break;
	
	case WM_LBUTTONUP:
	
		OutputDebugStringW(L"Left Mouse Up Output. \n");
		//Input->LeftMouseUp((UINT)wParam);
		break;
	
	}

}

InputHandler::~InputHandler() {
}