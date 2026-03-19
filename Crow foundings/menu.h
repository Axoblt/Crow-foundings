#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

enum class GameState { MENU, PLAYING, SETTINGS, SHOP, GAME_OVER };

class Menu {
public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window, GameState currentState);
    GameState handleEvent(const sf::Event& event, sf::RenderWindow& window);

private:
    sf::Texture texTitle, texStart, texSettings, texExit, texGameOver, texBackground;
    std::unique_ptr<sf::Sprite> sprTitle, sprStart, sprSettings, sprExit, sprGameOver, sprBackground;


    void centerOriginAndScale(sf::Sprite& sprite, float scale);
};