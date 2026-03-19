#include "menu.h"

Menu::Menu(float width, float height) {
    // Chargement du Background du Menu
    if (texBackground.loadFromFile("Assets/Menu/background_menu.png")) {
        sprBackground = std::make_unique<sf::Sprite>(texBackground);
        float scaleX = width / sprBackground->getLocalBounds().size.x;
        float scaleY = height / sprBackground->getLocalBounds().size.y;
        sprBackground->setScale({ scaleX, scaleY });
    }

    texTitle.loadFromFile("Assets/Menu/Raven_Soul_Title.png");
    texStart.loadFromFile("Assets/Menu/Start_Button.png");
    texSettings.loadFromFile("Assets/Menu/Settings_Button.png");
    texExit.loadFromFile("Assets/Menu/Exit_Button.png");
    texGameOver.loadFromFile("Assets/Menu/Game_Over_Panel.png");

    sprTitle = std::make_unique<sf::Sprite>(texTitle);
    sprStart = std::make_unique<sf::Sprite>(texStart);
    sprSettings = std::make_unique<sf::Sprite>(texSettings);
    sprExit = std::make_unique<sf::Sprite>(texExit);
    sprGameOver = std::make_unique<sf::Sprite>(texGameOver);

    centerOriginAndScale(*sprTitle, 0.3f);
    centerOriginAndScale(*sprStart, 0.12f);
    centerOriginAndScale(*sprSettings, 0.08f);
    centerOriginAndScale(*sprExit, 0.05f);
    centerOriginAndScale(*sprGameOver, 0.25f);

    sprTitle->setPosition({ width / 2.f, height * 0.30f });
    sprStart->setPosition({ width / 2.f, height * 0.62f });
    sprSettings->setPosition({ width / 2.f, height * 0.75f });
    sprExit->setPosition({ width / 2.f, height * 0.85f });
    sprGameOver->setPosition({ width / 2.f, height / 2.f });
}

GameState Menu::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (const auto* mouseButton = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButton->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords({ mouseButton->position.x, mouseButton->position.y });

            if (sprStart->getGlobalBounds().contains(mousePos)) return GameState::PLAYING;
            if (sprExit->getGlobalBounds().contains(mousePos)) window.close();
        }
    }
    return GameState::MENU;
}

void Menu::draw(sf::RenderWindow& window, GameState currentState) {
    if (currentState == GameState::MENU) {
        if (sprBackground) window.draw(*sprBackground);
        window.draw(*sprTitle);
        window.draw(*sprStart);
        window.draw(*sprSettings);
        window.draw(*sprExit);
    }
    else if (currentState == GameState::GAME_OVER) {
        if (sprBackground) window.draw(*sprBackground);
        window.draw(*sprGameOver);
    }
}

void Menu::centerOriginAndScale(sf::Sprite& sprite, float scale) {
    sprite.setScale({ scale, scale });
    auto bounds = sprite.getLocalBounds();
    sprite.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
}