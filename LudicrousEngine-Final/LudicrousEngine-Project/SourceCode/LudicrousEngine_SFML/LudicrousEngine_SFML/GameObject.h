#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "PhysicsRBody.h"

class GameObject
{
public:
	TransformComponent* m_transform;
	PhysicsRBody* m_rBody;
	RenderComponent* m_renderer;

	GameObject() {}
	GameObject(int objId, sf::Texture texture, bool isKinematic, Vector2 position)
		: m_ObjectId(objId),m_Parent(NULL), m_texture(texture) {
		m_transform = new TransformComponent();
		m_transform->m_Position = position;
		m_transform->Start();
		m_renderer = new RenderComponent(m_transform, m_texture);
		m_renderer->Start();
		//need to update physics rigidbody class to implement components
		//m_rBody = new PhysicsRBody(m_transform, m_renderer, isKinematic, m_ObjectId);
		//m_rBody->Start();
	}

	void SetParent(GameObject& parent);
	void AddChild(GameObject* child);

	void Start();
	void Update(sf::Time deltaTime);

	//gameobject ID#
	int m_ObjectId;

	~GameObject() {}
private:
	GameObject* m_Parent;
	std::vector<GameObject*> m_Children;

	sf::Transform worldMatrix;
	sf::Transform idMatrix;
	sf::Texture m_texture;
};

