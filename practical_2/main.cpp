//main.cpp
#include "ship.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"

using namespace sf;
using namespace std;

sf::Texture spritesheet;
sf::Sprite invader;
std::vector<Ship*> ships;
Player* player;

const Keyboard::Key controls[2] = {
    Keyboard::A,
    Keyboard::D,
};

void Load()
{
    if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) 
    {
        cerr << "Failed to load spritesheet!" << std::endl;
    }

    for (int r = 0; r < invaders_rows; ++r)
    {
        auto rect = IntRect(Vector2(0, 0), Vector2(32, 32));
        for (int c = 0; c < invaders_columns; ++c)
        {
            Vector2f position = { 100.0f + (c * 50.0f), 100.0f + (r * 50.0f) };
            auto inv = new Invader(rect, position);
            ships.push_back(inv);
        }
    }

    auto player = new Player();
    ships.push_back(player);

    Invader::speed = 20.f;
    Player::speed = 64.f;
}

void Reset() 
{
    Invader::speed = 20.f;
    Player::speed = 64.f;
}

void Update(RenderWindow& window) 
{
    // Reset clock, recalculate deltatime
    static Clock clock;
    float dt = clock.restart().asSeconds();

    // check and consume events
    Event event;
    while (window.pollEvent(event)) 
    {
        if (event.type == Event::Closed)
        {
            window.close();
            return;
        }
    }

    // Quit Via ESC Key
    if (Keyboard::isKeyPressed(Keyboard::Escape)) 
    {
        window.close();
    }

    for (auto& s : ships) 
    {
        s->Update(dt);
    };
}

void Render(RenderWindow& window) 
{
    for (const auto s : ships) 
    {
        window.draw(*s);
    }
}

int main() {
    RenderWindow window(VideoMode({ gameWidth, gameHeight }), "SpaceInvaders");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}