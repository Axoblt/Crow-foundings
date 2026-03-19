#include "obstacle.h"

obstacle::obstacle(float startX, float gapSize, const sf::Texture& texTop, const sf::Texture& texBottom, float scale)
    : x(startX)
{
    // --- 1. LE HAUT (Taille fixe, touche le plafond, jamais étiré) ---
    float displayWidth = static_cast<float>(texTop.getSize().x) * scale;
    float displayHeightTop = static_cast<float>(texTop.getSize().y) * scale;

    topShape.setSize({ displayWidth, displayHeightTop });
    topShape.setTexture(&texTop);
    topShape.setPosition({ x, 0.f }); // TOUCHE LE PLAFOND (Y = 0)

    // --- 2. LE BAS (S'ajuste pour créer l'écart) ---
    // On calcule le début du pilier du bas : hauteur du haut + l'écart voulu
    float bottomStart = displayHeightTop + gapSize;
    float bottomHeight = 1080.f - bottomStart;

    if (bottomHeight > 0) {
        bottomShape.setSize({ displayWidth, bottomHeight });
        bottomShape.setTexture(&texBottom);
        bottomShape.setPosition({ x, bottomStart });

        // On permet à la texture du bas de se répéter pour combler le vide sans s'étirer
        const_cast<sf::Texture&>(texBottom).setRepeated(true);
        bottomShape.setTextureRect(sf::IntRect(
            { 0, 0 },
            { static_cast<int>(texBottom.getSize().x), static_cast<int>(bottomHeight / scale) }
        ));
    }
}

void obstacle::update(float dt) {
    x -= speed * dt;
    topShape.setPosition({ x, topShape.getPosition().y });
    bottomShape.setPosition({ x, bottomShape.getPosition().y });
}

void obstacle::draw(sf::RenderTarget& target) const {
    target.draw(topShape);
    if (bottomShape.getSize().y > 0) {
        target.draw(bottomShape);
    }
}