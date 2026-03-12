#include "obstacle.h"

const float GAP_SIZE = 100.f;

obstacle::obstacle(float startX, float gapY, const sf::Texture& texture)
    : topSprite(texture), bottomSprite(texture), x(startX), gapY(gapY) {

    topSprite.setScale({ 0.3f, 0.5f });
    bottomSprite.setScale({ 0.3f, 0.5f });

  
    float spriteHeight = topSprite.getGlobalBounds().size.y;

    topSprite.setPosition({ x, gapY - (GAP_SIZE / 2.f) - spriteHeight });
    bottomSprite.setPosition({ x, gapY + (GAP_SIZE / 2.f) });
}

void obstacle::update(float dt) {
    x -= speed * dt;
    float spriteHeight = topSprite.getGlobalBounds().size.y;

    // Aligne strictement sur le bord haut (-50 pour un léger débordement visuel)
    topSprite.setPosition({ x, -50.f });
    // Aligne strictement sur le bord bas (1080 - hauteur + 50)
    bottomSprite.setPosition({ x, 1080.f - spriteHeight + 50.f });
}
void obstacle::draw(sf::RenderTarget& target) const {
    target.draw(topSprite);
    target.draw(bottomSprite);
}