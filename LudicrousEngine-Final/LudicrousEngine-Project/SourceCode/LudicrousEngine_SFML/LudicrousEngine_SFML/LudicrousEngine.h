#pragma once
#include <SFML/Graphics.hpp>
#include "MyActor.h";

using namespace sf;

class LudicrousEngine
{
private:
	RenderWindow m_Window;
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;
	MyActor m_actor;
	void input();
	void update(float dtAsSeconds);
	void draw();
public:
	LudicrousEngine();
	void start();
};