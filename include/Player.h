#ifndef PLAYER_H
#define PLAYER_H

struct Player {
    float posX;
    float posY;
    float velocity;
    int id;
    int color;
    char posChanged;
} typedef Player;

#endif