#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Platform.h"

static const float  VIEW_HEIGHT = 512.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 512), "SFML works!",sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
    sf::Texture playerTexture;
    playerTexture.loadFromFile("Knight.png");


    Player player(&playerTexture, sf::Vector2u(3, 4), 0.3f,100.0f,200.0f);

    std::vector<Platform>platforms;

    platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200), sf::Vector2f(500.0f, 200.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 100), sf::Vector2f(500.0f, 0.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(1000.0f, 200), sf::Vector2f(500.0f, 200.0f)));

    
    float deltaTime = 0.0f;
    sf::Clock clock;


    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                ResizeView(window, view);
                break;
            }
        }

        player.Update(deltaTime);

        sf::Vector2f direction;

        for (Platform& platform : platforms)
            if (platform.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
                player.OnCollision(direction);

        view.setCenter(player.GetPosition());

        window.clear(sf::Color(150,150,150));
        window.setView(view);
        player.Draw(window);
        
        for (Platform& platform : platforms)
        platform.Draw(window);

        window.display();
    }

    return 0;
}