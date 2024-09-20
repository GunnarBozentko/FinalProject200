#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

class Paddle {
public:
    Paddle(float width, float height, sf::Vector2f position, sf::Color color);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f position);
    void setVelocity(sf::Vector2f velocity);
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;


    sf::FloatRect getGlobalBounds() const;

private:
    sf::RectangleShape _paddleShape;
    sf::Vector2f _velocity;
};

#endif // PADDLE_H