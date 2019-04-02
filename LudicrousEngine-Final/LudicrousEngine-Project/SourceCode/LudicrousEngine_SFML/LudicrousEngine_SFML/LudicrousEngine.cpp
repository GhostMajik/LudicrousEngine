#pragma region INCLUDES
#include "LudicrousEngine.h"
#include "AudioComponent.h"
#include "ParticleSystem.h"
#include <random>
#include <functional>
#include <cstdlib>
#include <cmath>
using namespace std;
#include "ball.h"
#include <windows.h>
#include <winnt.h>
#include <iostream>
#include <string>
#include <sstream>
#include "SceneManager.h"
const int NUM_BALLS = 10;
const int NUM_WALLS = 5;
const int BT = 8;

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

#pragma endregion INCLUDES

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
	infoText.setString("Score: ");
	infoText.setCharacterSize(50);
	infoText.setFillColor(Color::White);
	infoText.setPosition(20, 10);

	MenuHeader.setFont(font);
	MenuHeader.setString("BALLS OF FURY");
	MenuHeader.setCharacterSize(150);
	MenuHeader.setFillColor(Color::White);
	MenuHeader.setPosition(resolution.x/2-600, 100);

	MenuIntro.setFont(font);
	MenuIntro.setString("PRESS 'ENTER' TO PLAY");
	MenuIntro.setCharacterSize(50);
	MenuIntro.setFillColor(Color::White);
	MenuIntro.setPosition(resolution.x/2-270, resolution.y/2+400);

	ResultsHeader.setFont(font);
	ResultsHeader.setString("Your Score: ");
	ResultsHeader.setCharacterSize(150);
	ResultsHeader.setFillColor(Color::White);
	ResultsHeader.setPosition(resolution.x / 2 - 600, 100);

	ResultsIntro.setFont(font);
	ResultsIntro.setString("PRESS 'ENTER' FOR MENU");
	ResultsIntro.setCharacterSize(50);
	ResultsIntro.setFillColor(Color::White);
	ResultsIntro.setPosition(resolution.x / 2 - 270, resolution.y / 2 + 400);


	AudioComponent::PlayMusic("menuNew.ogg");

}
//INIT FUNC
void LudicrousEngine::initialize()
{
	cout << "*******************************************************************" << endl;
	cout << "*Ludicrous Engine - By Colin Pugh, Naveen Prasad and Christian Lee*" << endl;
	cout << "*******************************************************************" << endl;
	checkSystemRequirements();	
	cout << "xResolution: " << resolution.x << " yResolution: " << resolution.y << endl;
	cout << "*******************************************************************" << endl;

}
//START FUNC
void LudicrousEngine::start()
{
	ParticleSystem pSystem(5000);
	SCENE scene = SPLASH;
	int GAME_STATE = SPLASH;
	sf::Texture tex;
	tex.create(resolution.x, resolution.y);
	sf::Sprite spr(tex);

	sf::Shader shader;
	shader.loadFromFile("fire.glsl", sf::Shader::Fragment); // load the shader

	if (!shader.isAvailable()) {
		std::cout << "The shader is not available\n";
	}
	shader.setUniform("resolution", sf::Vector2f(resolution.x / 1.5, resolution.y));

	const float ball_radius = 30.0f;
	const int bpp = 32;

	std::random_device seed_device;
	std::default_random_engine engine(seed_device());
	std::uniform_int_distribution<int> distribution(-16, 16);
	auto random = std::bind(distribution, std::ref(engine));

	sf::Vector2f direction(random(), random());
	const float velocity = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(150, 190));
	rectangle.setOutlineColor(sf::Color::Green);
	rectangle.setOutlineThickness(1);
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOrigin(0,0);

	sf::RectangleShape border;
	border.setPosition(sf::Vector2f(BT, BT));
	border.setSize(sf::Vector2f(1900, 1060));
	border.setOutlineThickness(BT);
	border.setOutlineColor(sf::Color::Cyan);
	border.setFillColor(sf::Color::Transparent);

	Ball bs[NUM_BALLS];
	Wall ws[NUM_WALLS];

	bs[0] = Ball();
	bs[1] = Ball(sf::Vector2f(700, 300), sf::Vector2f(-120, -200), 20, GOLD);
	bs[2] = Ball(sf::Vector2f(500, 500), sf::Vector2f(250, 100), 25, STONE);
	bs[3] = Ball(sf::Vector2f(400, 100), 130, 280, 35, WOOD);
	bs[4] = Ball(sf::Vector2f(700, 200), 130, 280, 35, GOLD);
	bs[5] = Ball(sf::Vector2f(900, 50), 130, 280, 35, WOOD);

	bs[0].set_position(40, 280);
	bs[0].set_radius(25);
	bs[0].set_angle(280);
	bs[0].set_speed(-600);

	ws[0] = Wall(sf::Vector2f(180, 260), sf::Vector2f(310, 180));
	ws[1] = Wall(sf::Vector2f(540, 400), ws[0]);
	ws[2] = Wall(sf::Vector2f(840, 600), ws[0]);
	ws[3] = Wall(sf::Vector2f(1040, 900), ws[0]);

	int i, j;
	float r;
	sf::Vector2f pos, vel;


	sf::Clock clock;
	sf::Clock clk;
	sf::Clock fpsClock;
	float lastTime;
	clk.restart();
	sf::Time elapsed = clock.restart();
	const sf::Time update_ms = sf::seconds(1.f / 120.f);

	int score = 0;


	while (m_Window.isOpen())
	{

		//Calculate FPS
		float currentTime = clock.restart().asSeconds();
		float fps = 1.f / currentTime;
		lastTime = currentTime;

		sf::Vector2i mouse = sf::Mouse::getPosition(m_Window);
		pSystem.setEmitter(m_Window.mapPixelToCoords(mouse));
		float dtAsSeconds = elapsed.asSeconds();
		input();
		update(dtAsSeconds);
		pSystem.update(elapsed);
		elapsed += clock.restart();
		while (elapsed >= update_ms) {

			rectangle.setPosition(m_actor.m_Position.x, m_actor.m_Position.y);
			elapsed -= update_ms;
		}


		for (i = 0; i < NUM_BALLS; i++)
		{
			bs[i].update_position(elapsed);
			pos = bs[i].get_position();
			vel = bs[i].get_velocity();
			r = bs[i].get_radius();

			if ((pos.x < BT + r && vel.x < 0) || (pos.x > resolution.x + BT - r && vel.x > 0))
				bs[i].bounce(0);
			if ((pos.y < BT + r && vel.y < 0) || (pos.y > resolution.y + BT - r && vel.y > 0))
				bs[i].bounce(90);

			for (j = 0; j < i; j++)
			{
				if (bs[i].is_colliding_with(bs[j]))
					collide(bs[i], bs[j]);
			}
			for (j = 0; j < NUM_WALLS; j++)
			{
				if (bs[i].is_colliding_with(ws[j]))
					collide(bs[i], ws[j]);
			}
		}
		shader.setUniform("time", clk.getElapsedTime().asSeconds());
		shader.setUniform("mouse", sf::Vector2f(resolution.x / 2, resolution.y / 2));
		m_Window.clear(Color::White);
		
		
		if (GAME_STATE == SPLASH)
		{
			m_Window.draw(m_SplashScreenSprite);
			splashTimer -= 0.05f;
			if (splashTimer <= 0.0f)
			{
				GAME_STATE = MENU;
			}
		}
		if (GAME_STATE == MENU)
		{
			m_Window.draw(m_BackgroundSprite);
			m_Window.draw(MenuHeader);
			m_Window.draw(MenuIntro);
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{			
				GAME_STATE = GAME;
				AudioComponent::PlayMusic("music.wav");
			}

		}
		if (GAME_STATE == GAME)
		{
			score = 0;
			//m_Window.draw(m_BackgroundSprite);
			m_Window.draw(spr, &shader);	
			m_Window.draw(border);

			for (i = 0; i < NUM_WALLS; i++)
				m_Window.draw(ws[i].get_rectangleShape());

			for (i = 0; i < NUM_BALLS; i++)
				m_Window.draw(bs[i].get_circleShape());

			score++;

			std::stringstream ss;
			ss << "Score: " << score;
			infoText.setString(ss.str());

			m_Window.draw(pSystem);

			m_Window.draw(m_actor.getSprite());
			m_Window.draw(infoText);
			m_Window.draw(rectangle);

			if (Keyboard::isKeyPressed(Keyboard::L))
			{
				GAME_STATE = RESULTS;
			}

		}

		if (GAME_STATE == RESULTS)
		{
			std::stringstream aa;
			aa << "Final Score: " << score;
			ResultsHeader.setString(aa.str());

			m_Window.draw(m_BackgroundSprite);
			m_Window.draw(ResultsHeader);
			m_Window.draw(ResultsIntro);
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				GAME_STATE = MENU;
				AudioComponent::PlayMusic("music.wav");
			}
		}

		
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
