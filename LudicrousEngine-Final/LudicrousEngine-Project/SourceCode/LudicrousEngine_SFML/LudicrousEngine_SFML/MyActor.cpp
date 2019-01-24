#include "MyActor.h"

MyActor::MyActor()
{
	m_Speed = 800;

	m_Texture.loadFromFile("actor.png");
	m_Sprite.setTexture(m_Texture);

	m_Position.x = 800;
	m_Position.y = 800;

}

Sprite MyActor::getSprite()
{
	return m_Sprite;
}

void MyActor::moveLeft()
{
	m_LeftPressed = true;
}

void MyActor::moveRight()
{
	m_RightPressed = true;
}
void MyActor::moveUp()
{
	m_UpPressed = true;
}
void MyActor::moveDown()
{
	m_DownPressed = true;
}
void MyActor::stopLeft()
{
	m_LeftPressed = false;
}

void MyActor::stopRight()
{
	m_RightPressed = false;
}
void MyActor::stopUp()
{
	m_UpPressed = false;
}
void MyActor::stopDown()
{
	m_DownPressed = false;
}
void MyActor::update(float elapsedTime)
{
	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
	}

	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
	}

	if (m_UpPressed)
	{
		m_Position.y -= m_Speed * elapsedTime;
	}

	if (m_DownPressed)
	{
		m_Position.y += m_Speed * elapsedTime;
	}

	m_Sprite.setPosition(m_Position);

}