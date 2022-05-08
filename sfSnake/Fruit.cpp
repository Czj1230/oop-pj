#include <SFML/Graphics.hpp>

#include "Fruit.h"
#include <iostream>
#include "Game.h"

using namespace sfSnake;

const float Fruit::Radius = 8.f;

Fruit::Fruit(sf::Color color ,sf::Vector2f position)
{
	if(Game::level==0){
		shape_.setPosition(position);
		shape_.setRadius(Fruit::Radius);
		shape_.setFillColor(color);
		shape_.setOutlineColor(sf::Color::White);
		shape_.setOutlineThickness(1);
	}
	else if(Game::level==1){
		shape_.setPosition(position);
		if(color == sf::Color::Red){
			shape_.setRadius(1.5f);
		}
		else if(color == sf::Color::Blue){
			shape_.setRadius(3.0f);
		}
		else if(color == sf::Color::Green){
			shape_.setRadius(5.0f);
		}
		else{
			shape_.setRadius(8.0f);
		}
		
		shape_.setFillColor(color);
		shape_.setOutlineColor(sf::Color::White);
		shape_.setOutlineThickness(1);
	}

}

void Fruit::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}

sf::Color Fruit::getFruitColor()
{
	return shape_.getFillColor();
}