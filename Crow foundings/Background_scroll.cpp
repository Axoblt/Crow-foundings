#include "Background_scroll.h"
#include <iostream>

Background_scroll::Background_scroll() : bgSpeed(150.f), offset(0.f) {
    // Assure-toi que le chemin vers l'image est correct
    if (!bgTex.loadFromFile("Assets/Background_1.png")) {
        std::cerr << "Erreur : Background_1.png introuvable" << std::endl;
    }

    // Indispensable pour le scrolling infini
    bgTex.setRepeated(true);

    // On définit la taille du rectangle (taille de ta fenêtre)
    bgShape.setSize({ 1920.f, 1080.f });
    bgShape.setTexture(&bgTex);
}

void Background_scroll::update(float dt) {
    // On augmente le décalage en fonction du temps
    offset += bgSpeed * dt;

    // On déplace la "vue" de la texture vers la droite 
    // pour que le décor semble défiler vers la gauche
    bgShape.setTextureRect(sf::IntRect(
        { static_cast<int>(offset), 0 },
        { 1920, 1080 }
    ));
}

void Background_scroll::draw(sf::RenderTarget& target) const {
    target.draw(bgShape);
}