#include "obstacle.h"

obstacle::obstacle(float x, float gapY, float gapSize, const sf::Texture& topTex, const sf::Texture& botTex, float scale)
    : topSprite(topTex), bottomSprite(botTex) {
    topSprite.setScale({ scale, scale });
    topSprite.setOrigin({ (float)topTex.getSize().x / 2.f, (float)topTex.getSize().y });
    topSprite.setPosition({ x, gapY - (gapSize / 2.f) });

    bottomSprite.setScale({ scale, scale });
    bottomSprite.setOrigin({ (float)botTex.getSize().x / 2.f, 0.f });
    bottomSprite.setPosition({ x, gapY + (gapSize / 2.f) });
}

void obstacle::update(float dt) {
    topSprite.move({ -speed * dt, 0.f });
    bottomSprite.move({ -speed * dt, 0.f });
}

void obstacle::draw(sf::RenderWindow& window) const {
    window.draw(topSprite);
    window.draw(bottomSprite);
}

bool obstacle::isOffScreen() const { return topSprite.getPosition().x < -300.f; }
sf::FloatRect obstacle::getTopBounds() const { return topSprite.getGlobalBounds(); }
sf::FloatRect obstacle::getBottomBounds() const { return bottomSprite.getGlobalBounds(); }