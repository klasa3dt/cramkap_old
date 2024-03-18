#define ENET_IMPLEMENTATION
#include "raylib.h"
#include "enet.h"

typedef unsigned ConnectionType;
enum ConnectionTypeBits
{
    CONNECTION_TYPE_NONE   = 0,
    CONNECTION_TYPE_CLIENT = 1,
    CONNECTION_TYPE_SERVER = 2
};

ConnectionType selectConnectionType();
void clientLoop();
void serverLoop();

int main(int argc, char** argv)
{
    InitWindow(800, 600, "Simple multipayer game");

    switch (selectConnectionType())
    {
    case CONNECTION_TYPE_CLIENT:
        clientLoop();
        break;
    case CONNECTION_TYPE_SERVER:
        serverLoop();
        break;
    default:
        break;
    }

    CloseWindow();
}

ConnectionType selectConnectionType()
{
    ConnectionType connectionType = CONNECTION_TYPE_NONE;

    while (!WindowShouldClose() && !connectionType)
    {
        BeginDrawing();
        {
            ClearBackground(BLACK);
            DrawFPS(10, 10);
            DrawText("Select client or server [C/S]", GetRenderWidth() * 0.30, GetRenderHeight() >> 1, 20, PINK);

            if (IsKeyPressed(KEY_C))
            {
                connectionType = CONNECTION_TYPE_CLIENT;
            }
            else if (IsKeyPressed(KEY_S))
            {
                connectionType = CONNECTION_TYPE_SERVER;
            }
        }
        EndDrawing();
    }

    return connectionType;
}

void clientLoop()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            ClearBackground(PINK);
            DrawText("Clint", GetRenderWidth() >> 1, GetRenderHeight() >> 1, 20, BLACK);
            DrawFPS(10, 10);
        }
        EndDrawing();
    }
}

void serverLoop()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            ClearBackground(BLUE);
            DrawText("Sever", GetRenderWidth() >> 1, GetRenderHeight() >> 1, 20, BLACK);
            DrawFPS(10, 10);
        }
        EndDrawing();
    }
}
