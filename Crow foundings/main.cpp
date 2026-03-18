#include <SFML/Graphics.hpp>
#include "player.h"
#include "obstacle.h"
#include "menu.h"
#include "Background_scroll.h" 
#include <vector>
#include <iostream>
#include <cstdlib> 

int main() {
    
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Raven Soul");
    window.setFramerateLimit(60);

   
    Background_scroll background;
    player crow;
    sf::Texture statueTex;
    if (!statueTex.loadFromFile("Assets/statut_1_WIP.png")) return -1;


    Menu gameMenu(1920, 1080);
    GameState state = GameState::MENU;

    std::vector<obstacle> obstacles;
    sf::Clock spawnClock;
    sf::Clock dtClock;
    bool isDead = false;

    while (window.isOpen()) 
    {
        float dt = dtClock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();


            if (state == GameState::MENU) {

                GameState newState = gameMenu.handleEvent(*event, window);
                if (newState == GameState::PLAYING) {

                    isDead = false;
                    player crow = player();
                    obstacles.clear();
                    spawnClock.restart();
                    state = GameState::PLAYING;
                }
            }
            else if (state == GameState::PLAYING) {
                if (!isDead) {
                    crow.handleEvent(*event);
                }
            }
            else if (state == GameState::GAME_OVER) {

                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                    if (keyPressed->code == sf::Keyboard::Key::Space) {
                        state = GameState::MENU;
                    }
                }
            }
        }


        if (state == GameState::PLAYING && !isDead) {
            background.update(dt);
            crow.update(dt);

            // Spawn des obstacles
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
                    state = GameState::GAME_OVER;
                }

                if (it->isOffScreen()) it = obstacles.erase(it);
                else ++it;
            }
        }


        window.clear(sf::Color(20, 20, 30));


        background.draw(window);

        if (state == GameState::MENU) {
            gameMenu.draw(window, GameState::MENU);
        }
        else if (state == GameState::PLAYING || state == GameState::GAME_OVER) {

            for (auto& obs : obstacles) {
                obs.draw(window);
            }
            crow.draw(window);


            if (state == GameState::GAME_OVER) {
                gameMenu.draw(window, GameState::GAME_OVER);
            }
        }

        window.display();
    }

    return 0;
}