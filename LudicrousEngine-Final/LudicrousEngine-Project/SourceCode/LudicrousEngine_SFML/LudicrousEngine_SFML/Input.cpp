#include "LudicrousEngine.h"
#include <iostream>
void LudicrousEngine::input()
{
	
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		m_Window.close();
	}

	if (Keyboard::isKeyPressed(Keyboard::Left)|| Keyboard::isKeyPressed(Keyboard::A))
	{
		m_actor.moveLeft();
	}
	else
	{
		m_actor.stopLeft();
	}

	if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
	{
		m_actor.moveRight();
	}
	else
	{
		m_actor.stopRight();
	}
	if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
	{
		m_actor.moveUp();
		std::cout << "UP PRESSED" << std::endl;
	}
	else
	{
		m_actor.stopUp();
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
	{
		m_actor.moveDown();
		std::cout << "DOWN PRESSED" << std::endl;
	}
	else
	{
		m_actor.stopDown();
	}

}