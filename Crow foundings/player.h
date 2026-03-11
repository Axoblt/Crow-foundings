#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class player {
private:
    float x, y, velocity, gravity, jumpForce;

    sf::Texture spriteSheet; 
    std::unique_ptr<sf::Sprite> sprite;

    float animationTimer{ 0.f };
    int currentFrame{ 0 };
    const float frameDuration{ 0.1f };
    bool isSpacePressed = false;

    const int frameWidth = 2050;
    const int frameHeight = 2050;

public:
    player();
    void update(float dt);
    void handleEvent(const sf::Event& event);
    void draw(sf::RenderTarget& target) const;

    sf::FloatRect getBounds() const {
        if (sprite) return sprite->getGlobalBounds();
        return sf::FloatRect({ 0, 0 }, { 0, 0 });
    }

};