#include "LudicrousEngine.h"

using namespace std;

#include <Windows.h>
#include <winnt.h>
#include <iostream>
#include <string>
extern "C" {
#include <Powrprof.h>
}
#pragma comment(lib, "Powrprof.lib")

typedef struct _PROCESSOR_POWER_INFORMATION 
{
	ULONG num;
	ULONG maxMhz;
	ULONG currMhz;
	ULONG limitMhz;
	ULONG maxIdle;
	ULONG currIdle;
} PROCESSOR_POWER_INFORMATION, *PPROCESSOR_POWER_INFORMATION;

LudicrousEngine::LudicrousEngine()
{
	//GET RESOLUTION
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	//INIT WINDOW
	m_Window.create(VideoMode(resolution.x, resolution.y),
		"Ludicrous Engine by Not Fast, Just Furious!",
		Style::Fullscreen);
	
	//TEST WINDOW
	//m_Window.create(sf::VideoMode(800, 200), "Hello from SFML");

	//ALL TEXTURE RELATED
	m_BackgroundTexture.loadFromFile("background.jpg");
	m_BackgroundSprite.setTexture(m_BackgroundTexture);
	
	//ALL TEXT RELATED
	font.loadFromFile("sansation.ttf");
	infoText.setFont(font);
	infoText.setString("Press 'Esc' to EXIT");
	infoText.setCharacterSize(80);
	infoText.setFillColor(Color::White);
	
	//ALL MUSIC RELATED
	m_Music.openFromFile("music.wav");
	m_Music.setVolume(30.f);
	m_Music.setLoop(true);
	m_Music.play();

}
//INIT FUNC
void LudicrousEngine::initialize()
{
	cout << "*******************************************************************" << endl;
	cout << "*Ludicrous Engine - By Colin Pugh, Naveen Prasad and Christian Lee*" << endl;
	cout << "*******************************************************************" << endl;
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	ULARGE_INTEGER ulFreeSpace;
	ULARGE_INTEGER ulTotalSpace;
	ULARGE_INTEGER ulTotalFreeSpace;
	GetDiskFreeSpaceEx("C:", &ulFreeSpace, &ulTotalSpace, &ulTotalFreeSpace);

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
	cout << "CPU Architecture: " << sysInfo.wProcessorArchitecture << endl;
}

//START FUNC
void LudicrousEngine::start()
{
	Clock clock;

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();

		float dtAsSeconds = dt.asSeconds();

		input();
		update(dtAsSeconds);
		draw();
	}
}
