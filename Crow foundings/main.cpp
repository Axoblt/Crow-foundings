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


    themes[0].top.loadFromFile("Assets/NewPylones/Pylones_1.png");
    themes[0].bottom.loadFromFile("Assets/NewPylones/Pylone_statut_1.1.png");

    themes[1].top.loadFromFile("Assets/NewPylones/Pylones_2.png");
    themes[1].bottom.loadFromFile("Assets/NewPylones/Pylones_Statut2.1.png");

    themes[2].top.loadFromFile("Assets/NewPylones/Pylones_3.png");
    themes[2].bottom.loadFromFile("Assets/NewPylones/Pylones_Statut3.1.png");

    Menu gameMenu(1920.f, 1080.f);
    GameState state = GameState::MENU;

    std::vector<obstacle> obstacles;
    sf::Clock spawnClock;
    sf::Clock dtClock;
    bool isDead = false;


    float gapSize = 250.f;     
    float obstacleScale = 0.5f; 

    while (window.isOpen()) {
    while (window.isOpen()) 
    {
        float dt = dtClock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            if (state == GameState::MENU) {
                if (gameMenu.handleEvent(*event, window) == GameState::PLAYING) {
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
                    if (keyPressed->code == sf::Keyboard::Key::Space || keyPressed->code == sf::Keyboard::Key::Enter) {
                        state = GameState::MENU;
                    }
                }
            }
        }

        if (state == GameState::PLAYING && !isDead) {
            background.update(dt);
            crow.update(dt);


            if (spawnClock.getElapsedTime().asSeconds() > 1.8f) {

                float randomGapY = 150.f + static_cast<float>(std::rand() % 480);
                int themeIndex = std::rand() % 3;


                obstacles.emplace_back(2000.f, randomGapY, gapSize, themes[themeIndex].top, themes[themeIndex].bottom, obstacleScale);
                spawnClock.restart();
            }

            for (auto it = obstacles.begin(); it != obstacles.end();) {
                it->update(dt);

                if (crow.getBounds().findIntersection(it->getTopBounds()).has_value() ||
                    crow.getBounds().findIntersection(it->getBottomBounds()).has_value() ||
                    crow.getBounds().position.y > 1080.f || crow.getBounds().position.y < -50.f)
                {
                    isDead = true;
                    state = GameState::GAME_OVER;
                }

                if (it->isOffScreen()) it = obstacles.erase(it);
                else ++it;
            }
        }

        window.clear(sf::Color(10, 10, 20)); 

        background.draw(window);


        if (state != GameState::MENU) {
            for (auto& obs : obstacles) obs.draw(window);
            crow.draw(window);
        }


        if (state == GameState::MENU) {
            gameMenu.draw(window, GameState::MENU);
        }
        else if (state == GameState::GAME_OVER) {
            gameMenu.draw(window, GameState::GAME_OVER);
        }

        window.display();
    }

    return 0;
}