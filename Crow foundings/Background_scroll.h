#pragma once
#ifndef BACKGROUND_SCROLL_H
#define BACKGROUND_SCROLL_H

#include <SFML/Graphics.hpp>

class Background_scroll {
public:
    Background_scroll();
    // On utilise float dt pour un mouvement constant
    void update(float dt);
    void draw(sf::RenderTarget& target) const;

private:
    sf::Texture bgTex;
    sf::RectangleShape bgShape;
    float bgSpeed;
    float offset; // Stocke le décalage horizontal
};

#endif