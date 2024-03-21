#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include <stdbool.h>

struct GamePlayers
{
    float x, y;
    unsigned color;
    unsigned id;
} typedef GamePlayers;

struct GameState
{
    GamePlayers players[10];
    unsigned playerCount;
} typedef GameState;

enum GameConnectionType
{
    GAME_CONNECTION_TYPE_NONE   = 0,
    GAME_CONNECTION_TYPE_SERVER = 1,
    GAME_CONNECTION_TYPE_CLIENT = 2
} typedef GameConnectionType;

void loadGame(int width, int height, const char* title);
GameConnectionType selectGameConnectionType();
bool windowAvailable();
void gameRender(GameState* state);
void closeGame();

#endif