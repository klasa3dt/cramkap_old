#define RAYGUI_IMPLEMENTATION
#include "Game.h"
#include <raygui.h>
#include <raylib.h>

void loadGame(int width, int height, const char* title)
{
    InitWindow(width, height, title);
}

GameConnectionType selectGameConnectionType()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(10, 10);
        DrawText("Select client or server [C/S]", (int)(GetRenderWidth() * 0.30), GetRenderHeight() >> 1, 20, PINK);
        EndDrawing();

        if (IsKeyPressed(KEY_C))
        {
            return GAME_CONNECTION_TYPE_CLIENT;
        }
        else if (IsKeyPressed(KEY_S))
        {
            return GAME_CONNECTION_TYPE_SERVER;
        }
    }

    return GAME_CONNECTION_TYPE_NONE;
}

bool windowAvailable()
{
    return !WindowShouldClose();
}

void gameLogic(Player* player)
{
    player->posChanged = false;

    if (IsKeyDown(KEY_A))
    {
        player->posX -= player->velocity * GetFrameTime();
        player->posChanged = true;
    }

    if (IsKeyDown(KEY_D)) {
        player->posX += player->velocity * GetFrameTime();
        player->posChanged = true;
    }

    if (IsKeyDown(KEY_W)) {
        player->posY -= player->velocity * GetFrameTime();
        player->posChanged = true;
    }

    if (IsKeyDown(KEY_S)) {
        player->posY += player->velocity * GetFrameTime();
        player->posChanged = true;
    }

    if (player->posX < 0) player->posX = 0;
    if (player->posX + 100 > (float)GetRenderWidth()) player->posX = (float)GetRenderWidth() - 100;
    if (player->posY < 0) player->posY = 0;
    if (player->posY + 100 > (float)GetRenderHeight()) player->posY = (float)GetRenderHeight() - 100;

    BeginDrawing();

    ClearBackground(PINK);
    DrawRectangle((int)player->posX, (int)player->posY, 100, 100, WHITE);
    DrawFPS(10, 10);

    EndDrawing();
}

void closeGame()
{
    CloseWindow();
}
