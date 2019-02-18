#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Rect.hpp"

struct Bounds {
	Vector2 center;
	Vector2 extents;
};

class RenderComponent
{
public:
	sf::Texture m_texture;
	Bounds m_bounds;
	TransformComponent* m_renderTransform;
	sf::Sprite m_sprite;

	RenderComponent() {}
	RenderComponent(TransformComponent* renderTransform, sf::Texture texture)
		: m_renderTransform(renderTransform), m_texture(texture) {}
	~RenderComponent() {}
	void Start();
	void UpdatePosition();

private:
	void SetBounds();
};

