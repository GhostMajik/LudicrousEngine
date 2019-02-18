#include "GameObject.h"

void GameObject::Start() {
	for (std::vector<GameObject*>::iterator i = m_Children.begin(); i != m_Children.end(); i++) {
		(*i)->Start();
	}
}

void GameObject::Update(sf::Time deltaTime) {
	if (m_Parent) {
		worldMatrix = m_Parent->worldMatrix * m_transform->transformMatrix;
	}
	else
		worldMatrix = m_transform->transformMatrix;

	m_transform->Update();
	m_renderer->UpdatePosition();
	for (std::vector<GameObject*>::iterator i = m_Children.begin(); i != m_Children.end(); i++) {
		(*i)->Update(deltaTime);
	}
}

//set parent of gameobject
void GameObject::SetParent(GameObject& parent) {
	m_Parent = &parent;
}

//add child to gameobject
void GameObject::AddChild(GameObject* child) {
	m_Children.push_back(child);
}