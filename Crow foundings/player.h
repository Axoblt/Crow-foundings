#pragma once

class player
{
private:
    float y;
    float velocity;

    float gravity;
    float jumpForce;

public:
    player();

    void update(float dt);
    void jump();

    float getY() const;
};