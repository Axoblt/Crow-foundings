#include "Background_scroll.h"
#include <iostream>

Background_scroll::Background_scroll() : bgSpeed(150.f), offset(0.f) {
    
    if (!bgTex.loadFromFile("Assets/Background_2.png")) {
        std::cerr << "Erreur : Background_1.png introuvable" << std::endl;
    }

    bgTex.setRepeated(true);

    //(horizontale/vertical)
    bgShape.setSize({ 5020.f, 4000.f });
    bgShape.setTexture(&bgTex);
}

void Background_scroll::update(float dt) {
   
    offset += bgSpeed * dt;

    bgShape.setTextureRect(sf::IntRect(
        { static_cast<int>(offset), 0 },
        { 1920, 1080 }
    ));
}

void Background_scroll::draw(sf::RenderTarget& target) const {
    target.draw(bgShape);
}