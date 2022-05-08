#include <SFML/Graphics.hpp>

#include <memory>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "Game.h"
#include "Setting.h"

using namespace sfSnake;

MenuScreen::MenuScreen()
{
	font_.loadFromFile("Fonts/game_over.ttf");
	text_.setFont(font_);
	text_.setString(
		"\n\n\n\n\n\n\n\n\nPress [SPACE] to play"
		"\n\nPress [ESC] to quit"
		"\n\nPress [S] to Settings");
	text_.setColor(sf::Color(176,224,230));

	snakeText_.setFont(font_);
	snakeText_.setString("Snake!");
	snakeText_.setColor(sf::Color::Green);
	snakeText_.setOutlineColor(sf::Color::White);
	snakeText_.setOutlineThickness(2.0);
	snakeText_.setCharacterSize(80);
	snakeText_.setStyle(sf::Text::Bold);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 2);

	sf::FloatRect snakeTextBounds = snakeText_.getLocalBounds();
	snakeText_.setOrigin(snakeTextBounds.left + snakeTextBounds.width / 2,
		snakeTextBounds.top + snakeTextBounds.height / 2);
	snakeText_.setPosition(Game::Width / 2, Game::Height / 4);
}

void MenuScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		Game::Screen = std::make_shared<GameScreen>();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		Game::Screen = std::make_shared<settingScreen>();
}

void MenuScreen::update(sf::Time delta)
{
	static bool movingLeft = false;
	static bool movingRight = true;

	if (movingRight)
	{
		snakeText_.rotate(delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == 10)
		{
			movingRight = false;
			movingLeft = true;
		}
	}

	if (movingLeft)
	{
		snakeText_.rotate(-delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == (360 - 10))
		{
			movingLeft = false;
			movingRight = true;
		}
	}
}

void MenuScreen::render(sf::RenderWindow& window)
{
	window.draw(Game::background);
	if(Game::grid.gridflag!=1){
		window.draw(Game::grid.grid_);
	}
	window.draw(text_);
	window.draw(snakeText_);
}