#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include <stdbool.h>

enum GameConnectionType
{
    GAME_CONNECTION_TYPE_NONE   = 0,
    GAME_CONNECTION_TYPE_SERVER = 1,
    GAME_CONNECTION_TYPE_CLIENT = 2
} typedef GameConnectionType;

void loadGame(int width, int height, const char* title);
GameConnectionType selectGameConnectionType();
bool windowAvailable();
void gameLogic(Player* player);
void closeGame();

#endif