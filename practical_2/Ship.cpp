//ship.cpp
#include "ship.h"
#include "game.h"
#include "bullet.h"

using namespace sf;
using namespace std;

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float& dt) {}

//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;

void Ship::Explode() {
    setTextureRect(IntRect(Vector2(128, 32), Vector2(32, 32)));
    _exploded = true;
}

bool Ship::is_exploded() const
{
    return _exploded;
}

Invader::Invader() : Ship() {}

bool Invader::direction;
float Invader::speed;

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) 
{
	setOrigin(Vector2f(16.f, 16.f));;
	setPosition(pos);
}

void Invader::Update(const float& dt) {
    Ship::Update(dt);

    move(Vector2f(dt * (direction ? 1.0f : -1.0f) * speed, 0.0f));

    if ((direction && getPosition().x > gameWidth - 16) ||
        (!direction && getPosition().x < 16)) 
    {
        direction = !direction;
        for (int i = 0; i < ships.size() - 1; ++i) {
            ships[i]->move(Vector2f(0.0f, 24.0f));
        }
        //speed += 20;
    }

    static float firetime = 0.0f;
    firetime -= dt;

        if (firetime <= 0 && rand() % 100 == 0) 
        {
            Bullet::Fire(getPosition(), true);
            firetime = 4.0f + (rand() % 60);
        }
}

float Player::speed;

Player::Player() : Ship(IntRect(Vector2(160, 32), Vector2(32, 32))) {
    setPosition({ gameWidth * .5f, gameHeight - 32.f });
}

void Player::Update(const float& dt) 
{
    Ship::Update(dt);

    float direction = 0.0f;

    if (Keyboard::isKeyPressed(Keyboard::A) && getPosition().x > 0) 
    {
        direction--;
    }

    if (Keyboard::isKeyPressed(Keyboard::D) && getPosition().x + 32 < gameWidth) 
    {
        direction++;
    }
    move(Vector2f((dt * direction * speed), 0));

    static float firetime = 0.0f;
    firetime -= dt;
    
        if (firetime <= 0 && Keyboard::isKeyPressed(Keyboard::Space)) {
            Bullet::Fire(getPosition(), false);
            firetime = 0.7f;
        }
}