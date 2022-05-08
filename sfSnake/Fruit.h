#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class Fruit
{
public:
	Fruit(sf::Color color ,sf::Vector2f position = sf::Vector2f(0, 0));

	void render(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;

	sf::Color getFruitColor();

	static const float Radius;

private:
	sf::CircleShape shape_;

	
};
}

#endif