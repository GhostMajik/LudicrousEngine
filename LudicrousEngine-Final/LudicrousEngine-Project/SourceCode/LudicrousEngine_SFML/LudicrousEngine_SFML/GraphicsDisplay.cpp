#include "GraphicsDisplay.h"
#include "LudicrousEngine.h"


sf::RenderWindow GraphicsDisplay::mainWindow;
//Vector2 resolution;


GraphicsDisplay::GraphicsDisplay()
{
}


GraphicsDisplay::~GraphicsDisplay()
{
}

void GraphicsDisplay::Init(SceneGraph sceneGraph) {

	//Set up window 
	//GET RESOLUTION
/*	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;


	//INIT WINDOW
	GraphicsDisplay::mainWindow.create(VideoMode(resolution.x, resolution.y),
		"Ludicrous Engine by Not Fast, Just Furious!",
		Style::Fullscreen);

	mainWindow.setMouseCursorVisible(false);*/

	std::cout << "Graphics Display Initialized" << std::endl;
}

void GraphicsDisplay::Draw(SceneGraph sceneGraph) {
	GraphicsDisplay::mainWindow.clear();

	std::list<RenderComponent*> renderComps = sceneGraph.renderComponents;

	for (std::list<RenderComponent*>::iterator i = renderComps.begin(); i != renderComps.end(); i++) {
		GraphicsDisplay::mainWindow.draw((*i)->m_sprite);
	}

	GraphicsDisplay::mainWindow.display();
}
