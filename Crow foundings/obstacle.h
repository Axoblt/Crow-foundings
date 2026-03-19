#pragma once
#include <SFML/Graphics.hpp>

class obstacle {
public:
    obstacle(float x, float gapY, float gapSize, const sf::Texture& topTex, const sf::Texture& botTex, float scale);

    void update(float dt);
    void draw(sf::RenderWindow& window) const;
    bool isOffScreen() const;

    sf::FloatRect getTopBounds() const;
    sf::FloatRect getBottomBounds() const;

private:
    sf::Sprite topSprite;
    sf::Sprite bottomSprite;
    float speed = 350.f;
};