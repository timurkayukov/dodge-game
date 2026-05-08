#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"
#include "Obstacle.h"

class Game
{
private:
    int width;
    int height;
    int score;
    bool gameOver;

    Player player;
    std::vector<Obstacle> obstacles;

public:
    Game();

    void run();

private:
    void draw();
    void handleInput(char command);
    void update();
    void addObstacle();
    bool checkCollision();
};

#endif
