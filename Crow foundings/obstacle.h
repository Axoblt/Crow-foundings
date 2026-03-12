#pragma once
#include <SFML/Graphics.hpp>

class obstacle {
private:
    sf::Sprite topSprite;
    sf::Sprite bottomSprite;
    float x;
    float gapY;
    static constexpr float speed = 300.f;

public:

    obstacle(float startX, float gapY, const sf::Texture& texture);
    void update(float dt);
    void draw(sf::RenderTarget& target) const;

    bool isOffScreen() const { return x < -200.f; }

    sf::FloatRect getTopBounds() const {
        sf::FloatRect rect = topSprite.getGlobalBounds();

   
        float customWidth = 100.0f;   // largeur 
        float customHeight = 450.0f; //  hauteur 


        float offsetX = (rect.size.x - customWidth) / 1.82f;
        float offsetY = 70.0f; 

        return {
            {rect.position.x + offsetX, rect.position.y + offsetY},
            {customWidth, customHeight}
        };
    }

    sf::FloatRect getBottomBounds() const {
        sf::FloatRect rect = bottomSprite.getGlobalBounds();

        float customWidth = 100.0f;
        float customHeight = 450.0f;

        float offsetX = (rect.size.x - customWidth) / 1.82f;
 
        float offsetY = 70.0f; 

        return {
            {rect.position.x + offsetX, rect.position.y + offsetY},
            {customWidth, customHeight}
        };
    }

    void drawDebug(sf::RenderTarget& target) const {
        sf::RectangleShape hbTop(getTopBounds().size);
        hbTop.setPosition(getTopBounds().position);
        hbTop.setFillColor(sf::Color::Transparent);
        hbTop.setOutlineColor(sf::Color::Red);
        hbTop.setOutlineThickness(2.f);

        sf::RectangleShape hbBottom(getBottomBounds().size);
        hbBottom.setPosition(getBottomBounds().position);
        hbBottom.setFillColor(sf::Color::Transparent);
        hbBottom.setOutlineColor(sf::Color::Red);
        hbBottom.setOutlineThickness(2.f);

        target.draw(hbTop);
        target.draw(hbBottom);
    }
};