#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MyActor.h";
#include "ParticleSystem.h"
#include "SceneManager.h"
using namespace sf;

class LudicrousEngine
{
private:
	RenderWindow m_Window;
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;
	Texture m_SplashScreen;
	Sprite m_SplashScreenSprite;
	Text infoText;
	Text MenuHeader;
	Text MenuIntro;
	Font font;
	MyActor m_actor;
	Music m_Music;
	Music m_menuMusic;
	ParticleSystem pSystem(int count);
	void input();
	void update(float dtAsSeconds);
	void draw();
	float score;
	SCENE scene = SPLASH;
	int GAME_STATE = SPLASH;
public:
	LudicrousEngine();
	void initialize();
	void start();
	void checkSystemRequirements();
};