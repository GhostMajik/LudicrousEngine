#include "LudicrousEngine.h"

using namespace sf;

//UPDATE LOOP
void LudicrousEngine::update(float dtAsSeconds)
{
	m_actor.update(dtAsSeconds);
}