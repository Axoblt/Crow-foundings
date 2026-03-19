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
    float getX() const { return topSprite.getPosition().x; }
    bool isPassed() const { return passed; }
    void setPassed() { passed = true; }

private:
    sf::Sprite topSprite, bottomSprite;
    float speed = 350.f;
    bool passed = false;
};