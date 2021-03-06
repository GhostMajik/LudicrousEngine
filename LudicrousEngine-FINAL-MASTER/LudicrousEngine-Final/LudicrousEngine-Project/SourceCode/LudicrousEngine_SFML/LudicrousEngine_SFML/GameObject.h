#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#pragma once
#include <list>
#include <vector>
#include <iterator>

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Vector2.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "PhysicsRBody.h"


class GameObject
{
public:
	TransformComponent* m_Transform;
	//PhysicsRBody* m_RigidBody;
	RenderComponent* m_Render;

	int m_ID; // made this public for physics component, can remove GetObjID()

private:
	GameObject* m_Parent;
	std::vector<GameObject*> m_Children;

	sf::Transform identityMatrix;
	sf::Transform worldTransform;

	sf::Texture m_texture;

public:
	GameObject() {}
	GameObject(int objID, sf::Texture texture, bool isKinematic, Vector2 pos) : m_ID(objID), m_Parent(NULL), m_texture(texture)
	{
		m_Transform = new TransformComponent();
		m_Transform->m_Position = pos;
		m_Transform->Start();
		m_Render = new RenderComponent(m_Transform, m_texture);
		m_Render->Start();
		//m_RigidBody = new PhysicsRBody(m_Transform, m_Render, isKinematic, m_ID);
		//m_RigidBody->Start();
	}

	// Get/Set
	int GetObjID() { return m_ID; }

	void SetParent(GameObject& parent);
	void AddChild(GameObject* child);

	void Start();
	void Update(sf::Time deltaTime);

private:

};

#endif