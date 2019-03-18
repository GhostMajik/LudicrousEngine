#pragma once
#include <Windows.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <stdio.h>
#include <iostream>
#include <list>

#include "SceneGraph.h"

class GraphicsDisplay
{
public:
	GraphicsDisplay();
	~GraphicsDisplay();

	static void Init(SceneGraph sceneGraph);
	static void Draw(SceneGraph sceneGraph);

	static sf::RenderWindow mainWindow;
	
};

