#include <SFML/Graphics.hpp>
#include "player.h"
#include "obstacle.h"
#include "menu.h"
#include "Background_scroll.h" 
#include <vector>

struct ObstacleTheme { sf::Texture top, bottom; };

int main() {
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Raven Soul");
    window.setFramerateLimit(60);

    Background_scroll background;
    player crow;
    Menu gameMenu(1920.f, 1080.f);
    GameState state = GameState::MENU;

    // --- SCORE TTF (Pendant le jeu) ---
    int score = 0;
    sf::Font font;
    font.openFromFile("Assets/Fonts/VampireWars.ttf");
    sf::Text liveScoreText(font, "0", 70);
    liveScoreText.setFillColor(sf::Color::White);
    liveScoreText.setPosition({ 60.f, 40.f });

    // --- THEMES & OBSTACLES ---
    std::vector<ObstacleTheme> themes(3);
    themes[0].top.loadFromFile("Assets/NewPylones/Pylones_1.png");
    themes[0].bottom.loadFromFile("Assets/NewPylones/Pylone_statut_1.1.png");
    themes[1].top.loadFromFile("Assets/NewPylones/Pylones_2.png");
    themes[1].bottom.loadFromFile("Assets/NewPylones/Pylones_Statut2.1.png");
    themes[2].top.loadFromFile("Assets/NewPylones/Pylones_3.png");
    themes[2].bottom.loadFromFile("Assets/NewPylones/Pylones_Statut3.1.png");

    std::vector<obstacle> obstacles;
    sf::Clock spawnClock, clock;


    float gapSize = 250.f;     
    float obstacleScale = 0.5f; 

  

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            
            GameState result = gameMenu.handleEvent(*event, window);
            if (state == GameState::MENU || state == GameState::GAME_OVER) {
                if (result == GameState::PLAYING) {
                    score = 0;
                    liveScoreText.setString("0");
                    obstacles.clear();
                    state = GameState::PLAYING;
                }
            }
            if (state == GameState::PLAYING) crow.handleEvent(*event);
        }

        float dt = clock.restart().asSeconds();

        if (state == GameState::PLAYING) {
            background.update(dt);
            crow.update(dt);

            if (spawnClock.getElapsedTime().asSeconds() > 1.8f) {
                float gapY = 250.f + (rand() % 500);
                obstacles.emplace_back(2000.f, gapY, 320.f, themes[rand()%3].top, themes[rand()%3].bottom, 0.6f);
                spawnClock.restart();
            }

            for (auto it = obstacles.begin(); it != obstacles.end();) {
                it->update(dt);
                if (!it->isPassed() && it->getX() < 400.f) {
                    score++;
                    it->setPassed();
                    liveScoreText.setString(std::to_string(score));
                }
                if (crow.getBounds().findIntersection(it->getTopBounds()) || 
                    crow.getBounds().findIntersection(it->getBottomBounds())) {
                    state = GameState::GAME_OVER;
                }
                if (it->isOffScreen()) it = obstacles.erase(it); else ++it;
            }
        }

        window.clear();
        if (state == GameState::MENU) {
            gameMenu.draw(window, GameState::MENU);
        } else {
            background.draw(window);
            for (auto& obs : obstacles) obs.draw(window);
            crow.draw(window);
            
            if (state == GameState::PLAYING) {
                window.draw(liveScoreText);
            } else if (state == GameState::GAME_OVER) {
                gameMenu.draw(window, GameState::GAME_OVER);
            }
        }
        window.display();
    }
    return 0;
}