#include "Setting.h"
#include "Game.h"
#include "MenuScreen.h"
#include "RuleScreen.h"

using namespace sfSnake;

settingScreen::settingScreen()
{
    font_.loadFromFile("Fonts/game_over.ttf");
    setting_.setFont(font_);
    setting_.setString("Setting");
    setting_.setFillColor(sf::Color(255,255,0));
    setting_.setOutlineColor(sf::Color::White);
    setting_.setCharacterSize(40);

    hint_.setFont(font_);
    hint_.setString("Press [C] to switch the background color\n"
                    "(Black, White, Brown)\n\n"
                    "Press [G] to switch the grid\n"
                    "(Transparent, White, Black, Brown)\n\n"
                    "Press [D] to switch the mode\n"
                    "(Easy, Medium, Hard)\n\n"
                    "Press [R] to see the rule\n\n"
                    "Press [Enter] to confirm");
    hint_.setFillColor(sf::Color::Green);
    hint_.setOutlineColor(sf::Color::Green);
    hint_.setCharacterSize(20);

    level_.setFont(font_);
    if (Game::level==0)
        level_.setString("Mode:       Easy");
    else if (Game::level==1)
        level_.setString("Mode:       Hard");
    level_.setFillColor(sf::Color::Green);
    level_.setOutlineColor(sf::Color::Green);

    sf::FloatRect textBound1 = setting_.getLocalBounds();
    setting_.setOrigin(textBound1.left + textBound1.width / 2,
                       textBound1.top + textBound1.height / 2);
    setting_.setPosition(Game::Width / 2, Game::Height / 8);

    sf::FloatRect textBound2 = hint_.getLocalBounds();
    hint_.setOrigin(textBound2.left + textBound2.width / 2,
                    textBound2.top + textBound2.height / 2);
    hint_.setPosition(Game::Width / 2, Game::Height / 2);

    sf::FloatRect textBound3 = level_.getLocalBounds();
    level_.setOrigin(textBound3.left + textBound3.width / 2,
                        textBound3.top + textBound3.height / 2);
    level_.setPosition(Game::Width / 2, Game::Height*7 / 8);


}

void settingScreen::handleInput(sf::RenderWindow &window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        Game::Screen = std::make_shared<MenuScreen>();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        Game::Screen = std::make_shared<ruleScreen>();    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
    {
        changeBG();
        sf::sleep(sf::seconds(0.2));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
    {
        Game::changeGrid();
        changeGridFlag();
        sf::sleep(sf::seconds(0.2));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        changeLevel();
        sf::sleep(sf::seconds(0.2));
    }

}

void settingScreen::changeBG(){
    if(Game::background.getFillColor()==sf::Color::Black){
        Game::background.setFillColor(sf::Color::White) ;
    }
    else if(Game::background.getFillColor()==sf::Color::White){
        Game::background.setFillColor(sf::Color(244,164,96)) ;
    }
    else if(Game::background.getFillColor()==sf::Color(244,164,96)){
        Game::background.setFillColor(sf::Color::Black) ;
    }
}

void settingScreen::changeGridFlag(){
    if(Game::grid.gridflag==1){
        Game::grid.gridflag =2;
    }
    else if(Game::grid.gridflag==2){
        Game::grid.gridflag =3;
    }
    else if(Game::grid.gridflag==3){
        Game::grid.gridflag = 4;
    }
    else{
        Game::grid.gridflag = 1;
    }
}

void settingScreen::changeLevel(){
    if(Game::level==0){
        Game::level=1;
        level_.setString("Mode:       Hard");
    }
    else if(Game::level==1){
        Game::level=0;
        level_.setString("Mode:       Easy");
    }
}

void settingScreen::update(sf::Time delta){
    
}

void settingScreen::render(sf::RenderWindow &window)
{
    window.draw(Game::background);

    if(Game::grid.gridflag != 1)
        window.draw(Game::grid.grid_);

    window.draw(setting_);
    window.draw(hint_);
    window.draw(setting_);
    window.draw(level_);
}
