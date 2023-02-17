//ship.h
#pragma once
#include <SFML/Graphics.hpp>
#include "bullet.h"

class Ship : public sf::Sprite {
protected:
    sf::IntRect _sprite;
    bool _exploded = false;
    //Default constructor is hidden
    Ship();
public:
    //Constructor that takes a sprite
    explicit Ship(sf::IntRect ir);
    //Pure virtual deconstructor -- makes this an abstract class and avoids undefined behaviour!
    virtual ~Ship() = 0;
    //Update, virtual so can be overridden, but not pure virtual
    virtual void Update(const float& dt);
    bool is_exploded() const;
    virtual void Explode();
};

class Invader : public Ship {
public:
    Invader(sf::IntRect ir, sf::Vector2f pos);
    Invader();
    void Update(const float& dt) override;
    static bool direction;
    static float speed;
};

class Player : public Ship {
public:
    Player();
    static float speed;
    void Update(const float& dt) override;
};