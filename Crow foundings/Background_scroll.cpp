#include "Background_scroll.h"
#include <iostream>

Background_scroll::Background_scroll() {
    std::string files[4] = {
        "Assets/Arriere_Plan_Interieur_.png",
        "Assets/2nd_layer_A.png",
        "Assets/ground_copie.png",           // Plan 2
        "Assets/asset_premierplan_bas.png"    // Plan 3
    };

    speeds = { 20.f, 60.f, 120.f, 200.f };
    offsets = { 0.f, 0.f, 0.f, 0.f };

    for (int i = 0; i < 4; ++i) {
        if (!textures[i].loadFromFile(files[i])) {
            std::cerr << "Erreur chargement : " << files[i] << std::endl;
        }
        textures[i].setRepeated(true);

        float height;
        if (i == 2) {
            //plan 2
            height = 750.f;
        }
        else if (i == 3) {
            //  plan 3 
            height = 750.f;
        }
        else {
            // Les plans de fond
            height = 1080.f;
        }

        shapes[i].setSize({ 1920.f, height });
        shapes[i].setTexture(&textures[i]);

        
        if (i >= 2) {
            shapes[i].setPosition({ 0.f, 1080.f - height });
        }
        else {
            shapes[i].setPosition({ 0.f, 0.f });
        }
    }
}

void Background_scroll::update(float dt) {
    for (int i = 0; i < 4; ++i) {
        offsets[i] += speeds[i] * dt;
        
        
        float currentHeight = shapes[i].getSize().y;

        shapes[i].setTextureRect(sf::IntRect(
            { static_cast<int>(offsets[i]), 0 },
            { 1920, static_cast<int>(currentHeight) }
        ));
    }
}

void Background_scroll::draw(sf::RenderTarget& target) const {
    for (int i = 0; i < 4; ++i) {
        target.draw(shapes[i]);
    }
}