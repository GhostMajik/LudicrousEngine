#include "SceneGraph.h"

//Add gameobjects to the scene, init and update them

//static int to keep track of gameobject ID for each gameobject
int SceneGraph::nextObjectId = 0;

//create new gameobject, push to list of gameobjects and add components to it
GameObject* SceneGraph::CreateGameObject(sf::Texture texture, Vector2 position, bool isKinematic) {
	
	GameObject* gameObj = new GameObject(nextObjectId, texture, isKinematic, position);
	m_GameObjects.insert(make_pair(nextObjectId, gameObj));
	nextObjectId++;

	renderComponents.push_back(gameObj->m_renderer);

	//Add rigid body to gameobject once physics component is updated

	return gameObj;
}

void SceneGraph::Start() {
	for (std::map<int, GameObject*>::iterator i = m_GameObjects.begin(); i != m_GameObjects.end(); ++i)
	{
		(i->second)->Start();
	}
}

void SceneGraph::Update(sf::Time deltaTime)
{
	for (std::map<int, GameObject*>::iterator i = m_GameObjects.begin(); i != m_GameObjects.end(); ++i)
	{
		(i->second)->Update(deltaTime);
	}
}