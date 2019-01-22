#include "LudicrousEngine.h"

LudicrousEngine::LudicrousEngine()
{
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	m_Window.create(VideoMode(resolution.x, resolution.y),
		"Ludicrous Engine by Not Fast, Just Furious!",
		Style::Fullscreen);

	
	m_BackgroundTexture.loadFromFile("background.jpg");

	m_BackgroundSprite.setTexture(m_BackgroundTexture);
	//ALL TEXT RELATED
	font.loadFromFile("sansation.ttf");
	infoText.setFont(font);
	infoText.setString("Press 'Esc' to EXIT");
	infoText.setCharacterSize(80);
	infoText.setFillColor(Color::White);
	//ALL MUSIC RELATED
	m_Music.openFromFile("music.wav");
	m_Music.setVolume(30.f);
	m_Music.setLoop(true);
	m_Music.play();

}

void LudicrousEngine::start()
{
	Clock clock;

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();

		float dtAsSeconds = dt.asSeconds();

		input();
		update(dtAsSeconds);
		draw();
	}
}