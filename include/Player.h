#ifndef PLAYER_H
#define PLAYER_H

struct Player {
    float posX;
    float posY;
    float speed;
    int   color;
    char posChanged;
} typedef Player;

void updatePlayerPosition(Player* player);

#endif