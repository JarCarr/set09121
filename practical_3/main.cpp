#include "Player.h"
#include "LevelSystem.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;

const int gameWidth = 800;
const int gameHeight = 600;
unique_ptr<Player> player(new Player());

void load() 
{

    auto path = "res/levels/maze.txt";

    ls::loadLevelFile(path);

    string buffer;

    ifstream f(path);
    if (f.good()) {
        f.seekg(0, std::ios::end);
        buffer.resize(f.tellg());
        f.seekg(0);
        f.read(&buffer[0], buffer.size());
        f.close();
    }
    else {
        throw string("Couldn't open level file: ") + path;
    }

    size_t pos[] = { 0,0 };

    auto row = 0;

    for (int i = 0; i < buffer.size(); i++)
    {
        if (buffer[i] == 's')
        {
            pos[0] = i % row;
            pos[1] = row;
            break;
        }
        
        if (buffer[i] == '\n')
        {
            row++;
        }
    }

    cout << pos[0] << ", " << pos[1] << endl;

    auto s = ls::getTilePosition({ pos[0], pos[1] });

    auto poo = ls::getHeight();

    auto poopoo = ls::getWidth();

    s.x += 50;
    s.y += 50;

    player->setPosition(s);

    cout << s.x << ", " << s.y << endl;

    // Print the level to the console
    for (size_t y = 0; y < ls::getHeight(); ++y) {
        for (size_t x = 0; x < ls::getWidth(); ++x) {
            cout << ls::getTile({ x, y });
        }
        cout << endl;
    }
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

    player->Update(dt);
}

void Render(RenderWindow& window)
{
    ls::Render(window);
    player->Render(window);
}

int main() {
    RenderWindow window(VideoMode({ gameWidth, gameHeight }), "SpaceInvaders");
    load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}