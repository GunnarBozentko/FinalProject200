#ifndef PUCK_H
#define PUCK_H


#include <SFML/Graphics.hpp>

class Puck {
public:
    Puck(float radius, sf::Vector2f position, sf::Color color);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void setVelocity(sf::Vector2f newVelocity);
    sf::Vector2f getVelocity();
    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f newPosition);
    void reset();
private:
    float _radius;
    sf::CircleShape _puckShape;
    sf::Vector2f _velocity;
};

#endif // PADDLE_H