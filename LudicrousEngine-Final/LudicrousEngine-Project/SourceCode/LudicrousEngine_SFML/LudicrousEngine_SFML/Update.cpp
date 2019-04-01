#include "LudicrousEngine.h"
#include "SceneManager.h"

using namespace sf;

void LudicrousEngine::update(float dtAsSeconds)
{
	m_actor.update(dtAsSeconds);
}