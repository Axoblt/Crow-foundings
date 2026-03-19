#include <SFML/Graphics.hpp>
#include "player.h"
#include "obstacle.h"
#include "menu.h"
#include "Background_scroll.h" 
#include <vector>
#include <iostream>
#include <cstdlib> 
#include <ctime>

struct ObstacleTheme {
    sf::Texture top;
    sf::Texture bottom;
};

int main() {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));


    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Raven Soul");
    window.setFramerateLimit(60);

    Background_scroll background;
    player crow;

    
    std::vector<ObstacleTheme> themes(3);

   
    if (!themes[0].top.loadFromFile("Assets/Pylones/Obstacle_1__Pylone_.png") ||
        !themes[0].bottom.loadFromFile("Assets/Pylones/Bas_Pylones_Obstacles_1.png")) return -1;

    
    if (!themes[1].top.loadFromFile("Assets/Pylones/Obstacle_2_Pylone_.png") ||
        !themes[1].bottom.loadFromFile("Assets/Pylones/Bas_Pylones_Obstacles_2.png")) return -1;

    
    if (!themes[2].top.loadFromFile("Assets/Pylones/Obstacle_3_Pylone_.png") ||
        !themes[2].bottom.loadFromFile("Assets/Pylones/Bas_Pylones_Obstacles_3.png")) return -1;

    
    for (int i = 0; i < 3; i++) {
        themes[i].bottom.setRepeated(true);
    }

    Menu gameMenu(1920.f, 1080.f);
    GameState state = GameState::MENU;

    std::vector<obstacle> obstacles;
    sf::Clock spawnClock;
    sf::Clock dtClock;
    bool isDead = false;

    
    float obstacleScale = 0.5f;

    while (window.isOpen()) {
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
            else if (state == GameState::PLAYING && !isDead) {
                crow.handleEvent(*event);
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


            if (spawnClock.getElapsedTime().asSeconds() > 1.8f) {
                float randomGap = 250.f + static_cast<float>(std::rand() % 250);

                int themeIndex = std::rand() % 3;


                obstacles.emplace_back(2000.f, randomGap, themes[themeIndex].top, themes[themeIndex].bottom, obstacleScale);

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
        else {
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