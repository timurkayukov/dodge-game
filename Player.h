#ifndef PLAYER_H
#define PLAYER_H

class Player
{
private:
    int x;
    int y;

public:
    Player(int startX, int startY);

    int getX();
    int getY();

    void moveLeft();
    void moveRight(int fieldWidth);
};

#endif
