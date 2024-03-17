#define ENET_IMPLEMENTATION
#include "raylib.h"
#include "enet.h"

int 
main
(
int argc,
char** argv
) {
    InitWindow(800, 600, "Simple multipayer game");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            ClearBackground(RED);

        }
        EndDrawing();
    }

    CloseWindow();
}