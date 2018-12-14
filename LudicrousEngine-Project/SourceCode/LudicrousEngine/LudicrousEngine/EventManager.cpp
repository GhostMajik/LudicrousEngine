#include "EventManager.h"
//matthew/viktors method they helped us set up
map < EventType, vector <fastdelegate::FastDelegate0<>>> dataMap;

EventManager::EventManager() {
	
}

void EventManager::AddListener(EventType event_t, fastdelegate::FastDelegate0<>function) {
	dataMap[event_t].push_back(function);
}

void EventManager::TriggerEvent(EventType event_t) {
	// go through list of listers of (event name) and call the call back functions
	for (vector <fastdelegate::FastDelegate0<>>::const_iterator b = dataMap[event_t].begin(); b != dataMap[event_t].end(); ++b)
	{
		OutputDebugStringW(L"Debug Output String. \n");
		b;
	}
}


void EventManager::KeyPressEvent(LPARAM lParam)
{ 
	LPSTR temp = new char[1];
	GetKeyNameTextA(lParam, temp, 10);
	
	OutputDebugString(temp);
	OutputDebugString("\n");
}

EventManager::~EventManager() {
}