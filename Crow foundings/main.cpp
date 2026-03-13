#include <SFML/Graphics.hpp>
#include "player.h"
#include "obstacle.h"
#include "Background_scroll.h" 
#include <vector>
#include <iostream>
#include <cstdlib> 

int main() {
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Flappy Crow");
    window.setFramerateLimit(60);

    Background_scroll background;  
    player crow;
    sf::Texture statueTex;
    if (!statueTex.loadFromFile("Assets/statut_1_WIP.png")) return -1;

    std::vector<obstacle> obstacles;
    sf::Clock spawnClock;
    sf::Clock dtClock;
    bool isDead = false;

    while (window.isOpen()) {
        float dt = dtClock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            if (!isDead) {
                crow.handleEvent(*event);
            }
            else {
                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                    if (keyPressed->code == sf::Keyboard::Key::Space) {
                        isDead = false;
                        auto crow = player(); 
                        obstacles.clear();
                        spawnClock.restart();
                    }
                }
            }
        }

        if (!isDead) {
            background.update(dt); 
            crow.update(dt);
            
            if (spawnClock.getElapsedTime().asSeconds() > 2.0f) {
                float randomY = 200.f + static_cast<float>(rand() % 600);
                obstacles.emplace_back(2000.f, randomY, statueTex);
                spawnClock.restart();
            }

            for (auto it = obstacles.begin(); it != obstacles.end();) {
                it->update(dt);
                if (crow.getBounds().findIntersection(it->getTopBounds()).has_value() ||
                    crow.getBounds().findIntersection(it->getBottomBounds()).has_value() ||
                    crow.getBounds().position.y > 1080.f || crow.getBounds().position.y < -100.f)
                {
                    isDead = true;
                }
                if (it->isOffScreen()) it = obstacles.erase(it);
                else ++it;
            }
        }

        window.clear(sf::Color(20, 20, 30));

        background.draw(window); 

        for (auto& obs : obstacles) {
            obs.draw(window);
            obs.drawDebug(window);
        }
        crow.draw(window);
        crow.drawDebug(window);
        window.display();
    }
    return 0;
}