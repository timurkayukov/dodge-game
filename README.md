# Dodge Game

This is a simple console game written in C++.

The player controls the symbol `O`.
Obstacles are shown as `#`.
The player must avoid falling obstacles.

## Controls

- `a` — move left
- `d` — move right
- `s` — stay
- `q` — quit

Commands are read immediately, so pressing Enter is not required.

## Build

cmake -B build
make -C build

## Run

./build/DodgeGame
