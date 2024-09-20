#include "Puck.h"
#include <cmath>


#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


Puck::Puck(float radius, sf::Vector2f position, sf::Color color)
        : _radius(radius), _velocity(0.0f, -150.0f) {
        // Create the puck shape
        _puckShape.setRadius(radius);
        _puckShape.setFillColor(color);
        _puckShape.setPosition(position);
        _puckShape.setOrigin(radius, radius); // Set the origin to the center
}

void Puck::update(float deltaTime) {
    // Update the position based on the velocity
    _puckShape.move(_velocity * deltaTime);
    float _topSpeed = 2000;

    float speed = sqrt(_velocity.x * _velocity.x + _velocity.y * _velocity.y);
    if (speed > _topSpeed) {
        // Scale down the velocity to the top speed while maintaining direction
        _velocity = (_velocity / speed) * _topSpeed;
    }

    // Simple collision with walls
    if (_puckShape.getPosition().x - _radius < 110) {
        _puckShape.setPosition(110 + _radius, _puckShape.getPosition().y); // Reset position to stay inside the left wall
        _velocity.x = -_velocity.x; // Reverse the horizontal velocity
    }

    if (_puckShape.getPosition().x + _radius > 900) {
        _puckShape.setPosition(900 - _radius, _puckShape.getPosition().y); // Reset position to stay inside the right wall
        _velocity.x = -_velocity.x; // Reverse the horizontal velocity
    }

    if (_puckShape.getPosition().y - _radius < 10) {
        _puckShape.setPosition(_puckShape.getPosition().x, 10 + _radius); // Reset position to stay inside the top wall
        _velocity.y = -_velocity.y; // Reverse the vertical velocity
    }

    if (_puckShape.getPosition().y + _radius > 790) {
        _puckShape.setPosition(_puckShape.getPosition().x, 790 - _radius); // Reset position to stay inside the bottom wall
        _velocity.y = -_velocity.y; // Reverse the vertical velocity
    }
}

void Puck::draw(sf::RenderWindow& window) {
    window.draw(_puckShape);
}

void Puck::setVelocity(sf::Vector2f newVelocity) {
    _velocity = newVelocity;
}

sf::Vector2f Puck::getVelocity() {
    return _velocity;
}

sf::FloatRect Puck::getGlobalBounds() const {
    return _puckShape.getGlobalBounds();
}

sf::Vector2f Puck::getPosition() const {
    return _puckShape.getPosition();
}

void Puck::setPosition(sf::Vector2f newPosition) {
    _puckShape.setPosition(newPosition);
}

void Puck::reset() {
    // Reset position to the initial position
    _puckShape.setPosition(sf::Vector2f(500.f, 400.f));

    // Reset velocity to the initial velocity
    _velocity = sf::Vector2f(0.0f, -150.0f);
}