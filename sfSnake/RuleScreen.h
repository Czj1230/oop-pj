#pragma once

#include <sfml/Graphics.hpp>
#include "Screen.h"

namespace sfSnake{

class ruleScreen : public Screen{
public:
    ruleScreen ();

    void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

    
private:
    sf::Font font_;
    sf::Text setting_;
    sf::Text hint_;

};

}