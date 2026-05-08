#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Game::Game() : player(5, 9)
{
    width = 10;
    height = 10;
    score = 0;
    gameOver = false;

    srand(time(0));
    addObstacle();
}

void Game::run()
{
    while (!gameOver)
    {
        draw();

        char command;
        cout << "Command (a-left, d-right, s-stay, q-quit): ";
        cin >> command;

        if (command == 'q')
        {
            cout << "Game closed." << endl;
            return;
        }

        handleInput(command);
        update();

        if (checkCollision())
        {
            gameOver = true;
        }

        score++;
    }

    draw();
    cout << "Game over!" << endl;
    cout << "Final score: " << score << endl;
}

void Game::draw()
{
    cout << endl;
    cout << "Score: " << score << endl;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            bool printed = false;

            if (player.getX() == x && player.getY() == y)
            {
                cout << "O";
                printed = true;
            }

            for (int i = 0; i < obstacles.size(); i++)
            {
                if (obstacles[i].getX() == x && obstacles[i].getY() == y)
                {
                    cout << "#";
                    printed = true;
                }
            }

            if (!printed)
            {
                cout << ".";
            }
        }

        cout << endl;
    }
}

void Game::handleInput(char command)
{
    if (command == 'a')
    {
        player.moveLeft();
    }

    if (command == 'd')
    {
        player.moveRight(width);
    }
}

void Game::update()
{
    for (int i = 0; i < obstacles.size(); i++)
    {
        obstacles[i].moveDown();
    }

    vector<Obstacle> newObstacles;

    for (int i = 0; i < obstacles.size(); i++)
    {
        if (obstacles[i].getY() < height)
        {
            newObstacles.push_back(obstacles[i]);
        }
    }

    obstacles = newObstacles;

    addObstacle();
}

void Game::addObstacle()
{
    int x = rand() % width;
    Obstacle obstacle(x);
    obstacles.push_back(obstacle);
}

bool Game::checkCollision()
{
    for (int i = 0; i < obstacles.size(); i++)
    {
        if (obstacles[i].getX() == player.getX() &&
            obstacles[i].getY() == player.getY())
        {
            return true;
        }
    }

    return false;
}
