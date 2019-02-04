#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MyActor.h"
#include "GameObject.h"

using namespace sf;

class LudicrousEngine
{
private:
	RenderWindow m_Window;
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;
	Text infoText;
	Font font;
	MyActor m_actor;
	Music m_Music;
	GameObject m_GameObject;
	void input();
	void update(float dtAsSeconds);
	void draw();
public:
	LudicrousEngine();
	void initialize();
	void start();
};