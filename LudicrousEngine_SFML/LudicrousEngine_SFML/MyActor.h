#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

using namespace sf;

class MyActor:GameObject {

private:

	Sprite m_Sprite;
	Texture m_Texture;

	bool m_LeftPressed;
	bool m_RightPressed;
	bool m_UpPressed;
	bool m_DownPressed;


	float m_Speed;

public:

	MyActor();

	Sprite getSprite();

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void stopUp();
	void stopDown();
	void stopLeft();
	void stopRight();

	void update(float elapsedTime);



};