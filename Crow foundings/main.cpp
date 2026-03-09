#include <SFML/Graphics.hpp>
#include "player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Flappy Test");

    player bird;

    sf::CircleShape shape(20.f);
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin({ 20.f,20.f });

    float x = 400.f;

    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::KeyPressed>())
            {
                auto key = event->getIf<sf::Event::KeyPressed>();
                if (key->code == sf::Keyboard::Key::Space)
                    bird.jump();
            }
        }

        bird.update(dt);

        shape.setPosition({ x, bird.getY() });

        window.clear();
        window.draw(shape);
        window.display();
    }
}