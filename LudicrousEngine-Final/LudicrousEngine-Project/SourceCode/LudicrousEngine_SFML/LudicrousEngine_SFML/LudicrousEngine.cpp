#include "LudicrousEngine.h"

using namespace std;

#include <windows.h>
#include <winnt.h>
#include <iostream>
#include <string>
#include <sstream>
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
	
	m_Window.setMouseCursorVisible(false);

	//TEST WINDOW
	//m_Window.create(sf::VideoMode(800, 200), "Hello from SFML");

	//ALL TEXTURE RELATED
	m_BackgroundTexture.loadFromFile("background.jpg");
	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	m_SplashScreen.loadFromFile("splash.png");
	m_SplashScreenSprite.setTexture(m_SplashScreen);
	
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
	checkSystemRequirements();	
	cout << "*******************************************************************" << endl;

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

void LudicrousEngine::checkSystemRequirements()
{
	int requiredSpace = 300;
	SYSTEM_INFO sysInfo;
	ULARGE_INTEGER ulFreeSpace;
	ULARGE_INTEGER ulTotalSpace;
	ULARGE_INTEGER ulTotalFreeSpace;
	std::string msgTxt;

	GetDiskFreeSpaceEx("C:", &ulFreeSpace, &ulTotalSpace, &ulTotalFreeSpace);

	int totalFreeSpaceInMb = (ulTotalFreeSpace.QuadPart / (1024 * 1024));

	if (requiredSpace < totalFreeSpaceInMb)
	{
		cout << "Sufficient space. \nDisk space required: " << requiredSpace << "MB" << ".\nDisk space available: " << totalFreeSpaceInMb << "MB" << endl;
	}
	else
	{
		cout << "Insufficient space. \nDisk space required: " << requiredSpace << "MB" << ".\nDisk space available: " << totalFreeSpaceInMb << "MB" << endl;
	}
}
