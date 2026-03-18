#include "Background_scroll.h"
#include <iostream>

Background_scroll::Background_scroll() {

    std::string files[4] = {
        "Assets/ground_copie.png", //1er Plan  
        "Assets/2nd_layer_A.png",    //2eme Plan
        "Assets/Background_2.png",   //3eme Plan
        "Assets/Background_2.png"    // Plan du fond
    };

    // Vitesses différentes pour créer l'effet de profondeur (Parallaxe)
    speeds = { 20.f, 60.f, 120.f, 200.f };
    offsets = { 0.f, 0.f, 0.f, 0.f };

    for (int i = 0; i < 4; ++i) {
        if (!textures[i].loadFromFile(files[i])) {
            std::cerr << "Erreur chargement : " << files[i] << std::endl;
        }
        textures[i].setRepeated(true);
        shapes[i].setSize({ 1920.f, 1080.f });
        shapes[i].setTexture(&textures[i]);
    }
}

void Background_scroll::update(float dt) {
    for (int i = 0; i < 4; ++i) {
        offsets[i] += speeds[i] * dt;
        shapes[i].setTextureRect(sf::IntRect(
            { static_cast<int>(offsets[i]), 0 },
            { 1920, 1080 }
        ));
    }
}

void Background_scroll::draw(sf::RenderTarget& target) const {
    for (int i = 0; i < 4; ++i) {
        target.draw(shapes[i]);
    }
}