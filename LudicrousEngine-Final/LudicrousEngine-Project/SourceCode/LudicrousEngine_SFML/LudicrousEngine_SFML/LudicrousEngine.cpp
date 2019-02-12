#include "LudicrousEngine.h"
#include "AudioComponent.h"
#include "ParticleSystem.h"
#include <random>
#include <functional>
#include <cstdlib>
#include <cmath>
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

float splashTimer = 100.0f;
Vector2f resolution;

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
	m_BackgroundTexture.loadFromFile("../Assets/background.jpg");
	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	m_SplashScreen.loadFromFile("../Assets/splash.png");
	m_SplashScreenSprite.setTexture(m_SplashScreen);
	
	//ALL TEXT RELATED
	font.loadFromFile("sansation.ttf");
	infoText.setFont(font);
	infoText.setString("Press 'Esc' to EXIT");
	infoText.setCharacterSize(80);
	infoText.setFillColor(Color::White);



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
	AudioComponent::PlayMusic("music.wav");
	ParticleSystem pSystem(5000);

	const float ball_radius = 30.0f;
	const int bpp = 32;

	std::random_device seed_device;
	std::default_random_engine engine(seed_device());
	std::uniform_int_distribution<int> distribution(-16, 16);
	auto random = std::bind(distribution, std::ref(engine));

	sf::Vector2f direction(random(), random());
	const float velocity = std::sqrt(direction.x * direction.x + direction.y * direction.y);


	sf::CircleShape ball(ball_radius - 4);
	ball.setOutlineThickness(4);
	ball.setOutlineColor(sf::Color::Black);
	ball.setFillColor(sf::Color::Red);
	ball.setOrigin(ball.getRadius(), ball.getRadius());
	ball.setPosition(500, 500);

	sf::Clock clock;
	sf::Time elapsed = clock.restart();
	const sf::Time update_ms = sf::seconds(1.f / 100.f);

	while (m_Window.isOpen())
	{
		sf::Vector2i mouse = sf::Mouse::getPosition(m_Window);
		pSystem.setEmitter(m_Window.mapPixelToCoords(mouse));
		float dtAsSeconds = elapsed.asSeconds();
		input();
		update(dtAsSeconds);
		pSystem.update(elapsed);
		elapsed += clock.restart();
		while (elapsed >= update_ms) {
			const auto pos = ball.getPosition();
			const auto delta = update_ms.asSeconds() * velocity;
			sf::Vector2f new_pos(pos.x + direction.x * delta, pos.y + direction.y * delta);

			if (new_pos.x - ball_radius < 0) { // left window edge
				direction.x *= -1;
				new_pos.x = 0 + ball_radius;
			}
			else if (new_pos.x + ball_radius >= resolution.x) { // right window edge
				direction.x *= -1;
				new_pos.x = resolution.x - ball_radius;
			}
			else if (new_pos.y - ball_radius < 0) { // top of window
				direction.y *= -1;
				new_pos.y = 0 + ball_radius;
			}
			else if (new_pos.y + ball_radius >= resolution.y) { // bottom of window
				direction.y *= -1;
				new_pos.y = resolution.y - ball_radius;
			}
			ball.setPosition(new_pos);

			elapsed -= update_ms;
		}
		m_Window.clear(Color::White);
		//m_Window.draw(m_SplashScreenSprite);
		//splashTimer -= 0.01f;

		//if (splashTimer <= 0.0f)
		//{
			m_Window.draw(m_BackgroundSprite);
			m_Window.draw(pSystem);
			m_Window.draw(m_actor.getSprite());
			m_Window.draw(infoText);
			m_Window.draw(ball);


		//}
		m_Window.display();
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
