#include "Player.h"

Player::Player(int startX, int startY)
{
    x = startX;
    y = startY;
}

int Player::getX()
{
    return x;
}

int Player::getY()
{
    return y;
}

void Player::moveLeft()
{
    if (x > 0)
    {
        x--;
    }
}

void Player::moveRight(int fieldWidth)
{
    if (x < fieldWidth - 1)
    {
        x++;
    }
}
