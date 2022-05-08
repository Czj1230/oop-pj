#include <SFML/Graphics.hpp>

#include "SnakeNode.h"
#include <iostream>
#include <math.h>

using namespace sfSnake;

const float SnakeNode::Width = 20.f;
const float SnakeNode::Height = 20.f;


static sf::Texture headshape;
static sf::Texture nodeshape;
extern void sfSnake::initialTexture()
{
	headshape.loadFromFile("image/6.png");
	nodeshape.loadFromFile("image/7.png");
}

SnakeNode::SnakeNode(bool isHead,sf::Vector2f position)
: position_(position)
{
	sprite.setPosition(position_);
	if(isHead){

		sprite.setTexture(headshape);
		this->isHead=true;
		// std::cout<<"Create Head!"<<std::endl;
		// sprite.setScale(0.1,0.1);
	}
	else{

		sprite.setTexture(nodeshape);
		this->isHead=false;
		// std::cout<<"Create Body!"<<std::endl;
	}
	sf::Vector2f origin = sprite.getOrigin();
	sprite.setOrigin(origin.x+10 , origin.y+10);
	
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	sprite.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	sprite.setPosition(position_);
}

void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	sprite.setPosition(position_);
}


sf::FloatRect SnakeNode::getBounds() const
{
	return sprite.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow& window)
{

	window.draw(sprite);
}

void SnakeNode::setRotation(float x, float y)
{
	float angle;
	if(x>0)
		angle=-acos(y)*180/3.1416;
	else
		angle=acos(y)*180/3.1416;
	sprite.setRotation(angle+180);
}

void SnakeNode::imitateRotation(SnakeNode &source)
{
	float angle=source.sprite.getRotation();
	sprite.setRotation(angle);
}