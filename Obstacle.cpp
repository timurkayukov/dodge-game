#include "Obstacle.h"

Obstacle::Obstacle(int startX)
{
    x = startX;
    y = 0;
}

int Obstacle::getX()
{
    return x;
}

int Obstacle::getY()
{
    return y;
}

void Obstacle::moveDown()
{
    y++;
}
