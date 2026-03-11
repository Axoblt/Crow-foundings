#include "obstacle.h"


obstacle::obstacle(float startX, float gapY, const sf::Texture& texture)
    : topSprite(texture), bottomSprite(texture), x(startX), gapY(gapY) {

    topSprite.setScale({ 0.3f, 0.5f });
    bottomSprite.setScale({ 0.3f, 0.5f });


    float gapSize = 350.f; // Réduis cette valeur pour rendre le passage plus difficile

    topSprite.setPosition({ x, gapY - 600.f }); // Ajuste ces valeurs pour que le haut soit collé en haut
    bottomSprite.setPosition({ x, gapY + gapSize });
}
void obstacle::update(float dt) {
    x -= speed * dt;
    topSprite.setPosition({ x, gapY - 500.f });
    bottomSprite.setPosition({ x, gapY + 100.f });
}

void obstacle::draw(sf::RenderTarget& target) const {
    target.draw(topSprite);
    target.draw(bottomSprite);
}