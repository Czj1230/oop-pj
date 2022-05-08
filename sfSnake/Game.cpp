#include <SFML/Graphics.hpp>

#include <memory>

#include "MenuScreen.h"
#include "Game.h"
#include "SnakeNode.h"


using namespace sfSnake;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 10.f);

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();

//initialization
sf::RectangleShape Game::background;
sf::RectangleShape Game::top_border,Game::buttom_border,Game::left_border,Game::right_border;//red 
BGGrid Game::grid;
int Game::level;
screenFlag Game::screenFlag_ = menu;

Game::Game()
: window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake")
{
	bgMusic_.openFromFile("Sounds/bg_music.wav");
	bgMusic_.setLoop(true);
	bgMusic_.play();
}

void Game::handleInput()
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window_.close();
	}

	Game::Screen->handleInput(window_);
}

void Game::update(sf::Time delta)
{
	Game::Screen->update(delta);
}

void Game::render()
{
	window_.clear();
	Game::Screen->render(window_);
	window_.display();
}

static void initialBackground()
{
	Game::background.setPosition(0,0);
	Game::background.setSize(sf::Vector2f(Game::Width,Game::Height));
	Game::background.setFillColor(sf::Color::Black);

	Game::top_border.setPosition(0,0);
	Game::top_border.setSize(sf::Vector2f(Game::Width,8.0f));
	Game::top_border.setFillColor(sf::Color::Red);

	Game::buttom_border.setPosition(0,Game::Height-8.0);
	Game::buttom_border.setSize(sf::Vector2f(Game::Width,8.0f));
	Game::buttom_border.setFillColor(sf::Color::Red);

	Game::left_border.setPosition(0,0);
	Game::left_border.setSize(sf::Vector2f(8.0f,Game::Height));
	Game::left_border.setFillColor(sf::Color::Red);

	Game::right_border.setPosition(Game::Width-8.0,0);
	Game::right_border.setSize(sf::Vector2f(8.0f,Game::Height));
	Game::right_border.setFillColor(sf::Color::Red);
}

static void initialGrid()
{ 
	grid_white.loadFromFile("image/grid_white.png");
	grid_white.setRepeated(true);
	grid_brown.loadFromFile("image/grid_brown.png");
	grid_brown.setRepeated(true);
	grid_black.loadFromFile("image/grid_black.png");
	grid_black.setRepeated(true);
	Game::grid.grid_.setTexture(grid_black);
	//Game::grid.grid_.setColor(sf::Color::Transparent);
	Game::grid.gridflag = 1;
	Game::grid.grid_.setPosition(0,0);
}

void Game::changeGrid()
{
    switch (Game::grid.gridflag)
    {
    case 1:
        break;
    case 2:
        Game::grid.grid_.setTexture(grid_white);
        break;
    case 3:
        Game::grid.grid_.setTexture(grid_brown);
        break;
    case 4:
        Game::grid.grid_.setTexture(grid_black);
        break;
    default:
        break;
    }
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	initialTexture();
	initialBackground();
	initialGrid();


	while (window_.isOpen())
	{
		sf::Time delta = clock.restart();
		timeSinceLastUpdate += delta;

		while (timeSinceLastUpdate > Game::TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			handleInput();
			update(TimePerFrame);
		}

		render();
	}
}