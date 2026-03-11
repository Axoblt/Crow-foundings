#include <SFML/Graphics.hpp>
#include "player.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Flappy Crow");
    player bird;
    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            bird.handleEvent(*event);
        }

        bird.update(dt);

        // Draw
        window.clear();
        bird.draw(window);
        window.display();
    }
}