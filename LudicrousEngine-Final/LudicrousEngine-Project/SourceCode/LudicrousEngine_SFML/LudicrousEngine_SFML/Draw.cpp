#include "LudicrousEngine.h"

float splashTimer = 100.0f;

//DRAW FUNC
void LudicrousEngine::draw()
{
	m_Window.clear(Color::White);
	m_Window.draw(m_SplashScreenSprite);
	splashTimer-= 0.01f;
	if (splashTimer <= 0.0f)
	{
		m_Window.draw(m_BackgroundSprite);
		m_Window.draw(m_actor.getSprite());
		m_Window.draw(infoText);
	}
	m_Window.display();
}