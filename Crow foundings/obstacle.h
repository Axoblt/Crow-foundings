#pragma once
#include <SFML/Graphics.hpp>

class obstacle {
private:
    sf::Sprite topSprite;
    sf::Sprite bottomSprite;
    float x;
    float gapY;
    static constexpr float speed = 300.f;

public:
    // On ne passe pas la texture ici pour éviter le problème de constructeur
    obstacle(float startX, float gapY, const sf::Texture& texture);
    void update(float dt);
    void draw(sf::RenderTarget& target) const;
    bool isOffScreen() const { return x < -200.f; }
    sf::FloatRect getTopBounds() const { return topSprite.getGlobalBounds(); }
    sf::FloatRect getBottomBounds() const { return bottomSprite.getGlobalBounds(); }
};