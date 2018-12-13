// Ludicrous Engine By Naveen Prasad, Colin Pugh and Christian Lee
// Assingment1 - Game Engine Development 1 - Semester 5

using namespace std;

#ifndef UNICODE
#define UNICODE
#endif 

#include <Windows.h>
#include <winnt.h>
#include <iostream>
#include <string>
extern "C" {
#include <Powrprof.h>
}
#pragma comment(lib, "Powrprof.lib")

bool IsInstanceRunning(LPCWSTR className, LPCWSTR windowTitle);
void checkSystemCompatability();

bool IsInstanceRunning(LPCWSTR className, LPCWSTR windowTitle)
{
	HANDLE handle = CreateMutex(NULL, true, windowTitle);
	if (GetLastError() != ERROR_SUCCESS)
	{
		HWND hWnd = FindWindow(className, windowTitle);
		if (hWnd)
		{
			ShowWindow(hWnd, SW_SHOWNORMAL);
			SetFocus(hWnd);
			SetForegroundWindow(hWnd);
			SetActiveWindow(hWnd);

			int msgboxID = MessageBox(
				hWnd,
				L"An Instance of the Application is already running",
				L"Multiple Instances Detected",
				MB_ICONWARNING
			);
			return true;
		}
	}
	return false;
}

typedef struct _PROCESSOR_POWER_INFORMATION {
	ULONG num;
	ULONG maxMhz;
	ULONG currMhz;
	ULONG limitMhz;
	ULONG maxIdle;
	ULONG currIdle;
} PROCESSOR_POWER_INFORMATION, *PPROCESSOR_POWER_INFORMATION;

int main()
{
	cout << "*****************************************************************" << endl;
	cout << "Ludicrous Engine - By Colin Pugh, Naveen Prasad and Christian Lee" << endl;
	cout << "*****************************************************************" << endl;
	checkSystemCompatability();
	cout << "*****************************************************************" << endl;
	cin.ignore();
	return 0;
}

void checkSystemCompatability()
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	ULARGE_INTEGER ulFreeSpace;
	ULARGE_INTEGER ulTotalSpace;
	ULARGE_INTEGER ulTotalFreeSpace;
	GetDiskFreeSpaceEx(L"C:", &ulFreeSpace, &ulTotalSpace, &ulTotalFreeSpace);

	if (300 > (ulTotalFreeSpace.QuadPart / 1024 * 1024))
		cout << "Insufficient Disk Space \nDisk Space Required Is: 300MB \nDisk Space Available: " << ulTotalFreeSpace.QuadPart / (1024 * 1024) << "MB" << endl;

	else
		cout << "Sufficient Disk Space \nDisk Space Required Is: 300MB \nDisk Space Available: " << ulTotalFreeSpace.QuadPart / (1024 * 1024) << "MB" << endl;

	MEMORYSTATUSEX memoryStruct = {};
	memoryStruct.dwLength = sizeof(memoryStruct);
	GlobalMemoryStatusEx(&memoryStruct);

	cout << "" << endl;
	cout << "Physical Memory Available: " << memoryStruct.ullAvailPhys / (800 * 800) << "MB" << endl;
	cout << "Virtual Memory Available : " << memoryStruct.ullAvailVirtual / (1024 * 1024) << "MB" << endl;
	
	const int size = sysInfo.dwNumberOfProcessors * sizeof(PROCESSOR_POWER_INFORMATION);
	LPBYTE pBuffer = new BYTE[size];
	CallNtPowerInformation(ProcessorInformation, NULL, 0, pBuffer, size);
	PPROCESSOR_POWER_INFORMATION ppi = (PPROCESSOR_POWER_INFORMATION)pBuffer;
	
	cout << "" << endl;
	cout << "Proccesor Speed: " << ppi->maxMhz << endl;
	cout << "CPU Architecture: "<< sysInfo.wProcessorArchitecture << endl;	
}