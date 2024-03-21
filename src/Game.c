#define RAYGUI_IMPLEMENTATION
#include "Game.h"
#include <raygui.h>
#include <raylib.h>

void loadGame(int width, int height, const char* title)
{
    InitWindow(width, height, title);
    SetTargetFPS (1000);
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

bool windowAvailable() { 

    return !WindowShouldClose();
}

void gameRender(GameState* state) {

    BeginDrawing();

    ClearBackground(PINK);

    for (unsigned i = 0; i < state->playerCount; ++i) {

        DrawRectangle((int)state->players[i].x, (int)state->players[i].y, 100, 100, WHITE);
    }

    DrawFPS(10, 10);
    EndDrawing();
}

void closeGame() {

    CloseWindow();
}
