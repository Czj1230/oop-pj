#include <SFML/Graphics.hpp>

#include <random>
#include <memory>
#include <iostream>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

using namespace sfSnake;

GameScreen::GameScreen() : snake_()
{

}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	while (fruit_.size() < 10)
	{
		static std::default_random_engine engine(time(NULL));
		static std::uniform_int_distribution<int> randomDistribution(1,100);
		int dice=randomDistribution(engine);
		if(dice<=12)
			generateFruit(sf::Color::Black);
		else if(dice<=25)
			generateFruit(sf::Color(237,145,33));	//brown
		else if(dice<=50)
			generateFruit(sf::Color::Red);
		else if(dice<=75)
			generateFruit(sf::Color::Blue);
		else 
			generateFruit(sf::Color::Green);

	}

	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);

	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow& window)
{
	//order is important
	window.draw(Game::background);
	if(Game::grid.gridflag!=1){
		window.draw(Game::grid.grid_);
	}
	if(Game::level){
		window.draw(Game::top_border);
		window.draw(Game::buttom_border);
		window.draw(Game::left_border);
		window.draw(Game::right_border);		
	}
	
	for (auto fruit : fruit_){
		fruit.render(window);
	}
	snake_.render(window);
		
}

void GameScreen::generateFruit(sf::Color color)
{
	static std::default_random_engine engine(time(NULL));
	
	static std::uniform_int_distribution<int> xDistribution(2, Game::Width - SnakeNode::Width);
	float x=xDistribution(engine);
	static std::uniform_int_distribution<int> yDistribution(2, Game::Height - SnakeNode::Height);
	float y=yDistribution(engine);
	fruit_.push_back(Fruit(color, sf::Vector2f(x, y)));

}

