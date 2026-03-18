#ifndef BACKGROUND_SCROLL_H
#define BACKGROUND_SCROLL_H

#include <SFML/Graphics.hpp>
#include <array>

class Background_scroll {
public:
    Background_scroll();
    void update(float dt);
    void draw(sf::RenderTarget& target) const;

private:
    std::array<sf::Texture, 4> textures;
    std::array<sf::RectangleShape, 4> shapes;
    std::array<float, 4> speeds;
    std::array<float, 4> offsets;
};

#endif