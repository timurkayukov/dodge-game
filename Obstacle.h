#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle
{
private:
    int x;
    int y;

public:
    Obstacle(int startX);

    int getX();
    int getY();

    void moveDown();
};

#endif
