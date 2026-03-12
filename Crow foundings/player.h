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
    // Ces deux lignes règlent l'erreur E1776
    player(player&&) noexcept = default;
    player& operator=(player&&) noexcept = default;

    void update(float dt);
    void handleEvent(const sf::Event& event);
    void draw(sf::RenderTarget& target) const;

    sf::FloatRect getBounds() const {
        if (sprite) {
            sf::FloatRect rect = sprite->getGlobalBounds();

            // Facteur de réduction (ex: 0.2f = réduit de 20% sur chaque bord)
            float reduction = 0.28f;

            sf::Vector2f newSize(rect.size.x * (1.0f - reduction * 2), rect.size.y * (1.0f - reduction * 2));
            sf::Vector2f newPos(rect.position.x + (rect.size.x * reduction), rect.position.y + (rect.size.y * reduction));

            return { newPos, newSize };
        }
        return sf::FloatRect({ 0, 0 }, { 0, 0 });
    }

    void drawDebug(sf::RenderTarget& target) const {
        sf::RectangleShape hb(getBounds().size);
        hb.setPosition(getBounds().position);
        hb.setFillColor(sf::Color::Transparent);
        hb.setOutlineColor(sf::Color::Green);
        hb.setOutlineThickness(2.f);
        target.draw(hb);
    }
};