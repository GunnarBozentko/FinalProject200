#include "Paddle.h"

Paddle::Paddle(float width, float height, sf::Vector2f position, sf::Color color)
    : _velocity(0.0f, 0.0f) {
    _paddleShape.setSize(sf::Vector2f(width, height));
    _paddleShape.setFillColor(color);
    _paddleShape.setPosition(position);
}

void Paddle::update(float deltaTime) {
    // Update the position based on the velocity
    _paddleShape.move(_velocity * deltaTime);
}

void Paddle::draw(sf::RenderWindow& window) {
    window.draw(_paddleShape);
}

void Paddle::setPosition(sf::Vector2f position) {
    _paddleShape.setPosition(position);
}

sf::Vector2f Paddle::getPosition() const {
    return _paddleShape.getPosition();
}

sf::FloatRect Paddle::getGlobalBounds() const {
    return _paddleShape.getGlobalBounds();
}

sf::Vector2f Paddle::getSize() const {
    return _paddleShape.getSize();
}