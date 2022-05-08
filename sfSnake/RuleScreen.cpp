#include "Setting.h"
#include "Game.h"
#include "MenuScreen.h"
#include "RuleScreen.h"

using namespace sfSnake;

ruleScreen::ruleScreen()
{
    font_.loadFromFile("Fonts/game_over.ttf");
    setting_.setFont(font_);
    setting_.setString("Rule");
    setting_.setFillColor(sf::Color::Yellow);
    setting_.setOutlineColor(sf::Color::White);
    setting_.setCharacterSize(40);

    hint_.setFont(font_);
    hint_.setString("Control the snake:\n"
                    "[up]/[down]/[left]/[right] key or mouse\n\n"
                    "easy mode:\n"
                    "simply eat the fruit as much as possible!\n"
                    "(red>blue>green>black&brown)\n\n"
                    "hard mode:\n"
                    "The basic rule is the same\n"
                    "however, the size of the fruit is different\n"
                    "and the snake can not touch the border\n\n"
                    "Press [Enter] to confirm");
    hint_.setFillColor(sf::Color::Green);
    hint_.setOutlineColor(sf::Color::Green);
    hint_.setCharacterSize(20);

    sf::FloatRect textBound1 = setting_.getLocalBounds();
    setting_.setOrigin(textBound1.left + textBound1.width / 2,
                       textBound1.top + textBound1.height / 2);
    setting_.setPosition(Game::Width / 2, Game::Height / 8);

    sf::FloatRect textBound2 = hint_.getLocalBounds();
    hint_.setOrigin(textBound2.left + textBound2.width / 2,
                    textBound2.top + textBound2.height / 2);
    hint_.setPosition(Game::Width / 2, Game::Height / 2);


}

void ruleScreen::handleInput(sf::RenderWindow &window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        Game::Screen = std::make_shared<settingScreen>();

}


void ruleScreen::update(sf::Time delta){
    
}

void ruleScreen::render(sf::RenderWindow &window)
{
    window.draw(Game::background);

    if(Game::grid.gridflag != 1)
        window.draw(Game::grid.grid_);

    window.draw(setting_);
    window.draw(hint_);
}
