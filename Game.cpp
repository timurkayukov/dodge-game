#include "Game.h"
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <termios.h>
#include <unistd.h>

namespace
{
class TerminalInputMode
{
public:
    TerminalInputMode()
    {
        enabled = isatty(STDIN_FILENO);

        if (!enabled)
        {
            return;
        }

        if (tcgetattr(STDIN_FILENO, &oldSettings) != 0)
        {
            enabled = false;
            return;
        }

        termios newSettings = oldSettings;
        newSettings.c_lflag &= ~(ICANON | ECHO);
        newSettings.c_cc[VMIN] = 0;
        newSettings.c_cc[VTIME] = 0;

        tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
    }

    ~TerminalInputMode()
    {
        if (enabled)
        {
            tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
        }
    }

private:
    bool enabled = false;
    termios oldSettings{};
};
}

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
    const chrono::milliseconds frameDelay(500);
    TerminalInputMode terminalInputMode;

    draw();

    while (!gameOver)
    {
        this_thread::sleep_for(frameDelay);

        if (handleAvailableInput())
        {
            cout << "Game closed." << endl;
            return;
        }

        update();

        if (checkCollision())
        {
            gameOver = true;
        }

        score++;
        draw();
    }

    cout << "Game over!" << endl;
    cout << "Final score: " << score << endl;
}

void Game::draw()
{
    cout << "\033[2J\033[H";
    cout << "Score: " << score << endl;
    cout << "Command (a-left, d-right, s-stay, q-quit): " << endl;

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

    cout.flush();
}

bool Game::handleAvailableInput()
{
    char buffer[128];
    ssize_t count = read(STDIN_FILENO, buffer, sizeof(buffer));
    bool movedThisFrame = false;

    if (count <= 0)
    {
        return false;
    }

    for (ssize_t i = 0; i < count; i++)
    {
        char command = buffer[i];

        if (command == 'q')
        {
            return true;
        }

        if (!movedThisFrame && (command == 'a' || command == 'd'))
        {
            handleInput(command);
            movedThisFrame = true;
        }
    }

    return false;
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
