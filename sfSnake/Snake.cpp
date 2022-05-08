#include "SFML/Graphics.hpp"

#include <memory>
#include <iostream>
#include <math.h>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"
#include "GameScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;

Snake::Snake() : direction_(Direction::Up), hitSelf_(false)
{
	initNodes();

	pickupBuffer_.loadFromFile("Sounds/ding.wav");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);
	MH_direction=sf::Vector2f(0.0f,-1.0f);
}

void Snake::initNodes()
{
	for (int i = 0; i < Snake::InitialSize; ++i)
	{
		if(i==0){
			nodes_.push_back(SnakeNode(true,sf::Vector2f(
			Game::Width / 2 - SnakeNode::Width / 2,
			Game::Height / 2 - (SnakeNode::Height / 2) + (SnakeNode::Height * i))));
		}
		else{
			nodes_.push_back(SnakeNode(false,sf::Vector2f(
			Game::Width / 2 - SnakeNode::Width / 2,
			Game::Height / 2 - (SnakeNode::Height / 2) + (SnakeNode::Height * i))));
		}
		
	}
}

void Snake::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		MH_direction.x=0.0;
		MH_direction.y=-1.0;
		direction_ = Direction::Up;	
		// std::cout<<"Up!"<<std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		MH_direction.x=0.0;
		MH_direction.y=1.0;
		direction_ = Direction::Down;
		// std::cout<<"Down!"<<std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		MH_direction.x=-1.0;
		MH_direction.y=0.0;
		direction_ = Direction::Left;
		// std::cout<<"Left!"<<std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		MH_direction.x=1.0;
		MH_direction.y=0.0;
		direction_ = Direction::Right;
		// std::cout<<"Right!"<<std::endl;
	}
	else if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		
		float M_globalPosition_x = float(sf::Mouse::getPosition(window).x);
		float M_globalPosition_y = float(sf::Mouse::getPosition(window).y);
		float H_globalPosition_x = nodes_[0].getPosition().x;
		float H_globalPosition_y = nodes_[0].getPosition().y;
		
		float MH_x=M_globalPosition_x-H_globalPosition_x;
		float MH_y=M_globalPosition_y-H_globalPosition_y;
		float len = sqrt(MH_x*MH_x+MH_y*MH_y);
		float New_x=MH_x / len;
		float New_y=MH_y / len;

		double angle = acos(MH_direction.x * New_x + MH_direction.y * New_y);
		if(angle< 3.1415 * 135 / 180){
			MH_direction.x=New_x;
			MH_direction.y=New_y;
			direction_= Direction::Other;
			// std::cout<<"Free Direction!"<<std::endl;
		}
		
	}
		
}

void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto&& it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0].getBounds())){
			toRemove = it;
		}
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		// std::cout<<"hit!"<<std::endl;
		if(toRemove->getFruitColor()==sf::Color::Red)
		{
			grow();grow();grow();
		}
		else if(toRemove->getFruitColor()==sf::Color::Blue)
		{
			grow();grow();
		}
		else if(toRemove->getFruitColor()==sf::Color::Green){
			grow();
		}

		fruits.erase(toRemove);
	}
}

//所有的增加都可以通过，叠加在尾部，然后随着move，逐渐“展开”
void Snake::grow()
{
	nodes_.push_back(SnakeNode(0, sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
		nodes_[nodes_.size() - 1].getPosition().y)));
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

static float distance(sf::Vector2f a, sf::Vector2f b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

void Snake::checkSelfCollisions()
{
	SnakeNode& headNode = nodes_[0];

	for (decltype(nodes_.size()) i = 1; i < nodes_.size(); ++i)
	{
		if (distance(headNode.getPosition(),nodes_[i].getPosition())<SnakeNode::Height/2)
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
		}
	}
}

void Snake::checkEdgeCollisions()
{
	SnakeNode& headNode = nodes_[0];
	if(Game::level==0){
		if (headNode.getPosition().x <= 0)
			headNode.setPosition(Game::Width, headNode.getPosition().y);
		else if (headNode.getPosition().x >= Game::Width)
			headNode.setPosition(0, headNode.getPosition().y);
		else if (headNode.getPosition().y <= 0)
			headNode.setPosition(headNode.getPosition().x, Game::Height);
		else if (headNode.getPosition().y >= Game::Height)
			headNode.setPosition(headNode.getPosition().x, 0);
	}
	else if(Game::level==1){
		float head_x=headNode.getPosition().x;
		float head_y=headNode.getPosition().y;
		if(head_x<=0 || head_x>=Game::Width ||head_y<=0 ||head_y>=Game::Height){
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;			
		}
	}


}

void Snake::move()
{
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
		nodes_[i].imitateRotation(nodes_[i-1]);
	}
	nodes_[0].move(SnakeNode::Height*MH_direction.x , SnakeNode::Height*MH_direction.y);
	nodes_[0].setRotation(MH_direction.x , MH_direction.y);

}

void Snake::render(sf::RenderWindow& window)
{
	for (auto node : nodes_)
		node.render(window);
}

