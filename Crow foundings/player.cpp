#include "player.h"

player::player()
{
    y = 400.f;
    velocity = 0.f;

    gravity = 1200.f;   // pixels par seconde²
    jumpForce = -500.f;
}

void player::update(float dt)
{
    velocity += gravity * dt;
    y += velocity * dt;
}

void player::jump()
{
    velocity = jumpForce;
}

float player::getY() const
{
    return y;
}