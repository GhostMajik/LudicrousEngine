#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "Vector2.h"

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Rect.hpp"



struct Bounds
{
public:
	Vector2 center;
	Vector2 extents;
};

class RenderComponent :BaseComponent
{
public:
	sf::Texture m_texture;
	Bounds m_bounds;
	TransformComponent* m_ownerTransform;
	sf::Sprite m_sprite;
private:


public:
	RenderComponent() {}
	RenderComponent(TransformComponent* ownerTransform, sf::Texture texture) : m_ownerTransform(ownerTransform), m_texture(texture) {}
	~RenderComponent() {}

	void Start();
	void UpdatePosition();

	//static sf::Sprite GetSprite();

private:
	void SetBounds();
};

#endif // !RENDERCOMPONENT_H#pragma once
