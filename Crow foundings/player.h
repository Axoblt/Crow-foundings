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

    player(player&&) noexcept = default;
    player& operator=(player&&) noexcept = default;

    void update(float dt);
    void handleEvent(const sf::Event& event);
    void draw(sf::RenderTarget& target) const;

    sf::FloatRect getBounds() const {
        if (sprite) {
            sf::FloatRect local = sprite->getLocalBounds();


            float scale = 0.08f;
            float reduction = 0.28f;


            sf::Vector2f size(local.size.x * scale * (1.0f - reduction * 2),
                local.size.y * scale * (1.0f - reduction * 2));

            sf::Vector2f pos(x - size.x / 2.f, y - size.y / 2.f);

            return { pos, size };
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