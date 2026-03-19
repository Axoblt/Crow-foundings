#pragma once
#include <SFML/Graphics.hpp>

class obstacle {
private:
    sf::RectangleShape topShape;
    sf::RectangleShape bottomShape;
    float x;
    static constexpr float speed = 350.f;

public:
    // Arguments : position X, taille du trou, texture haut, texture bas, échelle
    obstacle(float startX, float gapSize, const sf::Texture& texTop, const sf::Texture& texBottom, float scale);

    void update(float dt);
    void draw(sf::RenderTarget& target) const;
    bool isOffScreen() const { return x < -500.f; }

    sf::FloatRect getTopBounds() const { return topShape.getGlobalBounds(); }
    sf::FloatRect getBottomBounds() const { return bottomShape.getGlobalBounds(); }
};