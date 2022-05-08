#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>

#include "Screen.h"

namespace sfSnake
{
//outer space linkable	
class BGGrid
{
public: 
	sf::Sprite grid_;
	int gridflag;// 1 for transparent; 2 for black; 3 for white; 4 for brown.
};

enum screenFlag
{
	menu, game
};	

class Game
{
public:
	Game();

	void run();

	void handleInput();
	void update(sf::Time delta);
	void render();

	static void changeGrid();

	static const int Width = 900;
	static const int Height = 600;

	static std::shared_ptr<Screen> Screen;

	static sf::RectangleShape background; //color : black, white, brown
	static BGGrid grid;	//transparent, black, white, brown(138,54,15,120)
	static screenFlag screenFlag_;
	static int level;
	static sf::RectangleShape top_border,buttom_border,left_border,right_border;//red 

private:
	sf::RenderWindow window_;
	sf::Music bgMusic_;
	
	static const sf::Time TimePerFrame;
};


static sf::Texture grid_white;
static sf::Texture grid_brown;
static sf::Texture grid_black;
}


#endif