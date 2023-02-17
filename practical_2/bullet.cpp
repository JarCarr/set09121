#include "bullet.h"
#include "game.h"


using namespace sf;
using namespace std;

Bullet Bullet::bullets[256];
unsigned char Bullet::bulletPointer = '0';

Bullet::Bullet(const sf::Vector2f& pos, const bool mode)
{
    setPosition(pos);
    _mode = mode;
    setTexture(spritesheet);

    if (_mode)
    {
        auto rect = IntRect(Vector2(32, 32), Vector2(32, 32));
        setTextureRect(rect);
    }
    else
    {
        auto rect = IntRect(Vector2(64, 32), Vector2(32, 32));
        setTextureRect(rect);
    }
}

void Bullet::Render(sf::RenderWindow& window)
{
    for (auto b : bullets) {
        window.draw(b);
    }
}

void Bullet::Fire(const sf::Vector2f& pos, const bool mode)
{
    bullets[++bulletPointer] = Bullet(pos, mode);
}

void Bullet::Init()
{

}

void Bullet::Update(const float& dt) {
    for (auto& b : bullets) {
        b.move({ 0, 200.0f * dt * (b._mode ? 1.0f : -1.0f) });
        b._Update(dt);
    }
}

void Bullet::_Update(const float& dt) {
    if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
        //off screen - do nothing
        return;
    }
    else {
        move(Vector2f(0, dt * 200.0f * (_mode ? 1.0f : -1.0f)));
        const auto boundingBox = getGlobalBounds();

        for (auto s : ships) {
            if (!_mode && s == player) {
                //player bulelts don't collide with player
                continue;
            }
            if (_mode && s != player) {
                //invader bullets don't collide with other invaders
                continue;
            }
            if (!s->is_exploded() &&
                s->getGlobalBounds().findIntersection(boundingBox)) {
                //Explode the ship
                s->Explode();
                //warp bullet off-screen
                setPosition(Vector2f(-100, -100));
                return;
            }
        }
    }
};