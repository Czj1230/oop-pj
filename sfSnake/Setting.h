#pragma once

#include <sfml/Graphics.hpp>
#include "Screen.h"

namespace sfSnake{

class settingScreen : public Screen{
public:
    settingScreen ();

    void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

    void changeBG();
    void changeGridFlag();
    void changeLevel();
    
private:
    sf::Font font_;
    sf::Text setting_;
    sf::Text hint_;
    sf::Text level_;

};

}