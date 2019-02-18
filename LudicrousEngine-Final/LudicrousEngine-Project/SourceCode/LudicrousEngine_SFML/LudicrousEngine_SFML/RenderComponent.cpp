#include "RenderComponent.h"
#include <iostream>


void RenderComponent::Start() {
	m_sprite = sf::Sprite(m_texture);
	SetBounds();
	m_sprite.setPosition(m_renderTransform->m_Position.x, m_renderTransform->m_Position.y);

	std::cout << "New sprite created" << std::endl;
}

void RenderComponent::UpdatePosition() {
	m_sprite.setPosition(m_renderTransform->m_Position.x, m_renderTransform->m_Position.y);
}

void RenderComponent::SetBounds() {
	sf::Rect<float> rect = m_sprite.getLocalBounds();

	m_bounds.center = Vector2(m_sprite.getOrigin().x, m_sprite.getOrigin().y);
	m_bounds.extents = Vector2(rect.width * 0.5f, rect.height * 0.5f);
}