#pragma once
#include <windows.h>  
#include <stdlib.h>  
#include <string.h>  
#include <tchar.h> 
#include <map>
#include <vector>
#include  "FastDelegate.h"

using namespace std;

enum EventType {
	Event_KeyDown,
	Event_KeyUp,
	Event_MouseDown,
	Event_MouseMove,
};

class EventManager {
public:
	EventManager();
	void TriggerEvent(EventType event_t);
	void AddListener(EventType event_t, fastdelegate::FastDelegate0<> function);
	void KeyPressEvent(LPARAM lParam);
	void MouseEvent(int mouseButton);
	~EventManager();

};