#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Puck.h"
#include <fstream>

int main() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Air Hockey Game");

    // Create the puck
    Puck puck(20.0f, sf::Vector2f(500.f, 400.f), sf::Color::White);

    // Define the dimensions of the goals
    const float goalWidth = 200.0f;
    const float goalHeight = 50.0f;

    // Create the left goal
    sf::RectangleShape topGoal(sf::Vector2f(goalWidth, goalHeight));
    topGoal.setPosition(400, 0);
    topGoal.setFillColor(sf::Color::Blue);

    // Create the bottom goal
    sf::RectangleShape bottomGoal(sf::Vector2f(goalWidth, goalHeight));
    bottomGoal.setPosition(400, 740);
    bottomGoal.setFillColor(sf::Color::Red);

    // Define the dimensions of the walls
    const float wallThickness = 10.0f;

    // Create the top wall
    sf::RectangleShape topWall(sf::Vector2f(window.getSize().x - 200, wallThickness));
    topWall.setPosition(100, 0);
    topWall.setFillColor(sf::Color::Green);

    sf::RectangleShape bottomWall(sf::Vector2f(window.getSize().x - 200, wallThickness));
    bottomWall.setPosition(100, 790);
    bottomWall.setFillColor(sf::Color::Green);

    // Create the left wall
    sf::RectangleShape leftWall(sf::Vector2f(wallThickness, window.getSize().y));
    leftWall.setPosition(100, 0);
    leftWall.setFillColor(sf::Color::Green);

    // Create the right wall
    sf::RectangleShape RightWall(sf::Vector2f(wallThickness, window.getSize().y));
    RightWall.setPosition(900, 0);
    RightWall.setFillColor(sf::Color::Green);

    // Define the dimensions of the paddles
    const float paddleWidth = 100.0f;
    const float paddleHeight = 20.0f;

    // Create the top paddle
    Paddle topPaddle(paddleWidth, paddleHeight, sf::Vector2f(450, 200), sf::Color::Blue);

    // Create the bottom paddle
    Paddle bottomPaddle(paddleWidth, paddleHeight, sf::Vector2f(450, 600), sf::Color::Red);

    int topPlayerScore = 0;
    int bottomPlayerScore = 0;

    // Game loop
    sf::Clock clock;
    sf::Clock collisionCooldown;
    sf::Clock paddleFreezeCooldown;
    bool isTopPaddleFrozen = false;
    bool isBottomPaddleFrozen = false;
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart(); // Restart the clock and get the elapsed time
        float dtSeconds = deltaTime.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }


    if (!isTopPaddleFrozen) {
        // Handle user input for the top paddles
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            sf::Vector2f currentPosition = topPaddle.getPosition();
            if (currentPosition.y - 0.1 > 10) {
                topPaddle.setPosition(sf::Vector2f(currentPosition.x, currentPosition.y - 0.1));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            sf::Vector2f currentPosition = topPaddle.getPosition();
            if (currentPosition.y + 0.1 < 250) {
                topPaddle.setPosition(sf::Vector2f(currentPosition.x, currentPosition.y + 0.1));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            sf::Vector2f currentPosition = topPaddle.getPosition();
            if (currentPosition.x - 0.1 > 110) {
                topPaddle.setPosition(sf::Vector2f(currentPosition.x - 0.1, currentPosition.y));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            sf::Vector2f currentPosition = topPaddle.getPosition();
            if (currentPosition.x + 0.1 < 900 - paddleWidth) {
                topPaddle.setPosition(sf::Vector2f(currentPosition.x + 0.1, currentPosition.y));
            }
        }
    }

    if (!isBottomPaddleFrozen) {
        // Handle user input for the bottom paddle
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            sf::Vector2f currentPosition = bottomPaddle.getPosition();
            if (currentPosition.y - 0.1 > 550) {
                bottomPaddle.setPosition(sf::Vector2f(currentPosition.x, currentPosition.y - 0.1));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            sf::Vector2f currentPosition = bottomPaddle.getPosition();
            if (currentPosition.y + 0.1 < 770) {
                bottomPaddle.setPosition(sf::Vector2f(currentPosition.x, currentPosition.y + 0.1));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            sf::Vector2f currentPosition = bottomPaddle.getPosition();
            if (currentPosition.x + 0.1 < 900 - paddleWidth) {
                bottomPaddle.setPosition(sf::Vector2f(currentPosition.x + 0.1, currentPosition.y));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            sf::Vector2f currentPosition = bottomPaddle.getPosition();
            if (currentPosition.x - 0.1 > 110) {
                bottomPaddle.setPosition(sf::Vector2f(currentPosition.x - 0.1, currentPosition.y));
            }
        }
    }

    

    if (puck.getGlobalBounds().intersects(topPaddle.getGlobalBounds())) {


        if (collisionCooldown.getElapsedTime().asSeconds() > 0.1) {

            // Increase the speed of the puck (you can adjust the factor as needed)

            // Update the x and y components separately
            float newXVelocity = puck.getVelocity().x;
            float newYVelocity = puck.getVelocity().y;

            // Calculate the relative hit position on the paddle (between -1 and 1)
            float relativeHitPosition = (puck.getPosition().x - topPaddle.getPosition().x - topPaddle.getSize().x / 2.0f) / (topPaddle.getSize().x / 2.0f);
            // Adjust the newXVelocity based on the relative hit position
            float speedIncreaseFactor = 1.2f;
            newXVelocity += relativeHitPosition * 40.0f * speedIncreaseFactor;

            // Update the y velocity based on the current direction
            if (puck.getVelocity().y > 0) {
                newYVelocity = puck.getVelocity().y * speedIncreaseFactor;
            } else {
                newYVelocity = puck.getVelocity().y * speedIncreaseFactor;
            }

            // Set the new velocity
            puck.setVelocity(sf::Vector2f(newXVelocity, -newYVelocity));

            collisionCooldown.restart();
            isTopPaddleFrozen = true;
            paddleFreezeCooldown.restart();
        }
    }


    if (puck.getGlobalBounds().intersects(bottomPaddle.getGlobalBounds())) {

    if (collisionCooldown.getElapsedTime().asSeconds() > 0.1) {

            // Increase the speed of the puck (you can adjust the factor as needed)

            // Update the x and y components separately
            float newXVelocity = puck.getVelocity().x;
            float newYVelocity = puck.getVelocity().y;

            // Calculate the relative hit position on the paddle (between -1 and 1)
            float relativeHitPosition = (puck.getPosition().x - bottomPaddle.getPosition().x - bottomPaddle.getSize().x / 2.0f) / (topPaddle.getSize().x / 2.0f);
            // Adjust the newXVelocity based on the relative hit position
            float speedIncreaseFactor = 1.03f;
            newXVelocity += relativeHitPosition * 85.0f * speedIncreaseFactor;

            // Update the y velocity based on the current direction
            if (puck.getVelocity().y > 0) {
                newYVelocity = puck.getVelocity().y * speedIncreaseFactor;
            } else {
                newYVelocity = puck.getVelocity().y * speedIncreaseFactor;
            }

            // Set the new velocity
            puck.setVelocity(sf::Vector2f(newXVelocity, -newYVelocity));

            collisionCooldown.restart();
            isBottomPaddleFrozen = true;
            paddleFreezeCooldown.restart();
        }
    }


    // Check for puck collision with the top goal
    if (puck.getGlobalBounds().intersects(topGoal.getGlobalBounds())) {
        // Reset the puck to its initial state
        puck.reset();
        bottomPlayerScore += 1;
    }

    // Check for puck collision with the bottom goal
    if (puck.getGlobalBounds().intersects(bottomGoal.getGlobalBounds())) {
        // Reset the puck to its initial state
        puck.reset();
        topPlayerScore += 1;
    }


        if (paddleFreezeCooldown.getElapsedTime().asSeconds() > .13) {
            isTopPaddleFrozen = false;
            isBottomPaddleFrozen = false;
        }

        if (topPlayerScore >= 3 || bottomPlayerScore >= 3) {

            std::ofstream outputFile("Scores.txt", std::ios::app);

            // Check if the file is open
            if (outputFile.is_open()) {
                // Write scores to the file
                outputFile << "Top Player Score: " << topPlayerScore << std::endl;
                outputFile << "Bottom Player Score: " << bottomPlayerScore << std::endl;
                outputFile << " " << std::endl;

                // Close the file
                outputFile.close();
            }

            // Close the window
            window.close();
        }


        // Clear the window
        window.clear();

        // Draw the goals and walls
        window.draw(topGoal);
        window.draw(bottomGoal);
        window.draw(topWall);
        window.draw(leftWall);
        window.draw(RightWall);
        window.draw(bottomWall);

        // Draw the paddles
        topPaddle.draw(window);
        bottomPaddle.draw(window);

        

        // Update and draw the puck
        puck.update(dtSeconds);
        puck.draw(window);

        // Display the contents of the window
        window.display();
    }

    return 0;
}