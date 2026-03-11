#include <SFML/Graphics.hpp>
#include "player.h"
#include "obstacle.h"
#include <vector>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Flappy Crow Modern");
    player crow;

    sf::Texture statueTex;
    if (!statueTex.loadFromFile("Assets/statut_1_WIP.png")) {
        return -1;
    }

    std::vector<obstacle> obstacles;
    sf::Clock spawnClock;
    sf::Clock dtClock;
    sf::Clock gameStartClock;

    while (window.isOpen()) {
        float dt = dtClock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            crow.handleEvent(*event);
        }

        crow.update(dt);

        if (spawnClock.getElapsedTime().asSeconds() > 2.0f) {
            obstacles.emplace_back(1920.f, 500.f, statueTex);
            spawnClock.restart();
        }

        for (auto it = obstacles.begin(); it != obstacles.end();) {
            it->update(dt);

            if (gameStartClock.getElapsedTime().asSeconds() > 2.0f) {
                if (crow.getBounds().findIntersection(it->getTopBounds()).has_value() ||
                    crow.getBounds().findIntersection(it->getBottomBounds()).has_value()) {
                    std::cout << "Collision ! Game Over!" << std::endl;
                    //window.close();
                }
            }

            if (it->isOffScreen()) it = obstacles.erase(it);
            else ++it;
        }

        window.clear(sf::Color(20, 20, 30));
        for (const auto& obs : obstacles) obs.draw(window);
        crow.draw(window);
        window.display();
    }
}