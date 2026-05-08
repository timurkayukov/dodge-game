cmake_minimum_required(VERSION 3.10)

project(DodgeGame)

set(CMAKE_CXX_STANDARD 17)

add_executable(DodgeGame
    main.cpp
    Game.cpp
    Player.cpp
    Obstacle.cpp
)
