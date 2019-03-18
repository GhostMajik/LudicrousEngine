#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class MyActor {

private:
	Sprite m_Sprite;
	Texture m_Texture;
	bool m_LeftPressed;
	bool m_RightPressed;
	bool m_UpPressed;
	bool m_DownPressed;
	float m_Speed;
	sf::RectangleShape rectangle;

public:
	MyActor();
	Vector2f m_Position;
	Sprite getSprite();
	void moveLeft();
	void moveRight();
	void moveUp();
	void shotFired();
	void moveDown();
	void stopUp();
	void stopDown();
	void stopLeft();
	void stopRight();
	void update(float elapsedTime);
};