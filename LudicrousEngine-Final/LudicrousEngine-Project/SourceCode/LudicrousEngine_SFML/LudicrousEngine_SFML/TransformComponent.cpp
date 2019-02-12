#include "TransformComponent.h"
#include <iostream>

void TransformComponent::Start()
{
	std::cout << "Transform Component Initialized" << std::endl;
}

void TransformComponent::Update()
{
	std::cout << "Pos (x: " << m_Position.x << ", y: " << m_Position.y << ")" << std::endl;
}