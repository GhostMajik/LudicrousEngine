#include "SceneGraph.h"

int SceneGraph::nextObjectID = 0;

GameObject* SceneGraph::CreateObject(sf::Texture texture, bool isKinematic, Vector2 pos)
{
	std::cout << "Scene Graph is Creating GameObject" << std::endl;

	GameObject* obj = new GameObject(nextObjectID, texture, isKinematic, pos);
	m_Objects.insert(std::make_pair(nextObjectID, obj));

	nextObjectID++;

	renderComponents.push_back(obj->m_Render);

	return obj;
}

void SceneGraph::Start()
{
	for (std::map<int, GameObject*>::iterator i = m_Objects.begin(); i != m_Objects.end(); ++i)
	{
		(i->second)->Start();
	}
}

void SceneGraph::Update(sf::Time deltaTime)
{
	for (std::map<int, GameObject*>::iterator i = m_Objects.begin(); i != m_Objects.end(); ++i)
	{
		(i->second)->Update(deltaTime);
	}
}