#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MyActor.h";

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
	Font font;
	MyActor m_actor;
	Music m_Music;
	void input();
	void update(float dtAsSeconds);
	void draw();
public:
	LudicrousEngine();
	void initialize();
	void start();
	void checkSystemRequirements();
};