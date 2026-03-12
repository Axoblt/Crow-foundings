#include "player.h"
#include <iostream>


player::player() : x(400.f), y(400.f), velocity(0.f), gravity(1200.f), jumpForce(-500.f) {

    if (!spriteSheet.loadFromFile("Assets/spritesheet_vol_corbeau_Skin_1.png")) {
    }

    sprite = std::make_unique<sf::Sprite>(spriteSheet);

    sprite->setTextureRect(sf::IntRect({ 0, 0 }, { frameWidth, frameHeight }));
    sprite->setOrigin({ frameWidth / 2.f, frameHeight / 2.f });
    sprite->setScale({ 0.08f, 0.08f });
}

void player::update(float dt) {
    velocity += gravity * dt;
    y += velocity * dt;

    animationTimer += dt;
    if (animationTimer >= frameDuration) {
        animationTimer = 0.f;
        currentFrame = (currentFrame + 1) % 6;

        int col = currentFrame % 3;
        int row = currentFrame / 3;

        sprite->setTextureRect(sf::IntRect({ col * frameWidth, row * frameHeight }, { frameWidth, frameHeight }));
    }

    sprite->setPosition({ x, y });
    sprite->setRotation(sf::degrees(velocity * 0.05f));
}


void player::handleEvent(const sf::Event& event) {
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Space && !isSpacePressed) {
            velocity = jumpForce;
            isSpacePressed = true;
        }
    }

    if (event.is<sf::Event::KeyReleased>()) {
        if (event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Space) {
            isSpacePressed = false;
        }
    }
}

void player::draw(sf::RenderTarget& target) const {
    if (sprite) {
        target.draw(*sprite); 
    }
}