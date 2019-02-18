#pragma once
#include <iostream>
#include <map>
#include <list>

#include "GameObject.h"
using namespace std;
class SceneGraph
{
public:
	GameObject* CreateGameObject(sf::Texture texture, Vector2 position, bool isKinematic);
	void Start();
	void Update(sf::Time deltaTime);

	list<RenderComponent*> renderComponents;

private:
	map<int, GameObject*> m_GameObjects;
	static int nextObjectId;
};

