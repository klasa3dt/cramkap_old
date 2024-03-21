#include "Player.h"
#include <raylib.h>

void updatePlayerPosition (Player* player) {

    player->posChanged = 0;

    if (IsKeyDown(KEY_A))
    {
        player->posX -= player->speed * GetFrameTime();
        player->posChanged = true;
    }

    if (IsKeyDown(KEY_D)) {
        player->posX += player->speed * GetFrameTime();
        player->posChanged = true;
    }

    if (IsKeyDown(KEY_W)) {
        player->posY -= player->speed * GetFrameTime();
        player->posChanged = true;
    }

    if (IsKeyDown(KEY_S)) {
        player->posY += player->speed * GetFrameTime();
        player->posChanged = true;
    }
}

/**
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
*/