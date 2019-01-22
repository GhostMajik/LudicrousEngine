#include "LudicrousEngine.h"

void LudicrousEngine::draw()
{
	m_Window.clear(Color::White);
	m_Window.draw(m_BackgroundSprite);
	m_Window.draw(m_actor.getSprite());
	m_Window.draw(infoText);
	m_Window.display();
}