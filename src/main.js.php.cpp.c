#define RAYGUI_IMPLEMENTATION
#include "enet.h"
#include "raygui.h"
#include <raylib.h>
#include <stdio.h>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#include "client.cs.c.asm.obj.bin.out.in.cpp.c++.php.js.lua.css.sass.scss.xaml.xml.xht.htmx.html.xhtml.toml.json.jsx.tsx.ts.svelte.vue.asp.cshtml.html.lua.h"

struct Player {
    float posX;
    float posY;
    float velocity;
    int id;
    Color color;
} typedef Player;


typedef unsigned ConnectionType;
enum ConnectionTypeBits {
    CONNECTION_TYPE_NONE   = 0,
    CONNECTION_TYPE_CLIENT = 1,
    CONNECTION_TYPE_SERVER = 2
};

ConnectionType selectConnectionType ();
void clientLoop ();
void serverLoop ();
int main (int argc, char** argv) {

    if (enet_initialize())
    {
        return EXIT_FAILURE;
    }

    InitWindow (SCREEN_WIDTH, SCREEN_HEIGHT, "Simple multipayer game");

    switch (selectConnectionType ()) {

    case CONNECTION_TYPE_CLIENT:
        clientLoop ();
        break;
    case CONNECTION_TYPE_SERVER:
        serverLoop ();
        break;
    default:
        break;
    }

    CloseWindow ();

    enet_deinitialize();
}

ConnectionType selectConnectionType () {

    ConnectionType connectionType = CONNECTION_TYPE_NONE;

    while (!WindowShouldClose () && !connectionType) {

        BeginDrawing (); {

            ClearBackground (BLACK);
            DrawFPS(10, 10);
            DrawText("Select client or server [C/S]", GetRenderWidth() * 0.30, GetRenderHeight() >> 1, 20, PINK);

            if (IsKeyPressed (KEY_C)) {

                connectionType = CONNECTION_TYPE_CLIENT;
            }
            else if (IsKeyPressed (KEY_S)) {

                connectionType = CONNECTION_TYPE_SERVER;
            }
        }
        EndDrawing ();
    }
    return connectionType;
}
void sendPlayerPosition (ENetPeer* peer, ENetPacket* packet, Player* player) {
    packet = enet_packet_create (player, sizeof(player), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send (peer, 0, packet); 
    enet_packet_destroy (packet);
}

void clientLoop () {

    ENetAddress address;
    ENetHost* client;
    ENetEvent event;
    ENetPeer* peer;
    ENetPacket* packet;

    client = enet_host_create (NULL, 1, 2, 0, 0);

    if (client) {
        puts("wiadomo kto wiadomo co client istnieje koleszko ciesz sie i baw");
    }

    enet_address_set_host (&address, "127.0.0.1");
    address.port = 3107;

    peer = enet_host_connect (client, &address, 1, 0);

    if (peer) {
        puts("wiadomo kto wiadomo co peer istnieje koleszko ciesz sie i baw peer peer peer peer perr eppepperer");
    }
    
    if (!peer) {
        fprintf (stderr, "No avaible peers for initiating an ENet bro.");
        exit (EXIT_FAILURE);
    }

    bool connected = 0;
    Player player = { 0, 0, 0.01 };

        while (!WindowShouldClose()) {

            while (enet_host_service(client, &event, 0) > 0) {

                switch (event.type) {

                    case ENET_EVENT_TYPE_CONNECT: {
                        printf("Connected to server wiadomo co wiadomo kto wiadomo kogo\n");
                        connected = 1;
                    } break;

                    case ENET_EVENT_TYPE_RECEIVE: {
                        printf("Message recieved! %s\n od wiadomo kogo wiadmoco co wiadomo czemu", event.packet->data);
                        enet_packet_destroy(event.packet);
                    } break;

                    case ENET_EVENT_TYPE_DISCONNECT:
                    case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
                        printf("Can't connect to the server\n");
                        break;
                }
            }
            
            if (IsKeyDown (KEY_A)) {
                player.posX -= player.velocity;
                sendPlayerPosition(peer, packet, &player);
            }

            if (IsKeyDown (KEY_D)) {
                player.posX += player.velocity;
               sendPlayerPosition(peer, packet, &player);
            } 

            if (IsKeyDown (KEY_W)) {
                player.posY -= player.velocity;
                sendPlayerPosition(peer, packet, &player);
            } 

            if (IsKeyDown (KEY_S)) {
                player.posY += player.velocity;
                sendPlayerPosition(peer, packet, &player);
            } 

            if (player.posX < 0) player.posX = 0;
            if (player.posX + 100 > SCREEN_WIDTH) player.posX = SCREEN_WIDTH - 100;
            if (player.posY < 0) player.posY = 0;
            if (player.posY + 100 > SCREEN_HEIGHT) player.posY = SCREEN_HEIGHT - 100;


        BeginDrawing (); {

            ClearBackground (PINK);
            DrawRectangle (player.posX, player.posY, 100, 100, WHITE);
            DrawFPS (10, 10);
        }

        EndDrawing ();
    }
    enet_host_destroy (client);
}

void serverLoop () {

    ENetAddress address;
    ENetHost* server;
    ENetEvent event;
    ENetPacket* packet;
    address.host = ENET_HOST_ANY;
    address.port = 3107;

    Player* player;

    int playersCount = 0;

    if (!(server = enet_host_create(&address, 32, 2, 0, 0)))
    {
        fprintf(stderr, "Failed to create a server");
        exit(EXIT_FAILURE);
    }

    while (!WindowShouldClose ()) {

        

        BeginDrawing (); {

            ClearBackground (BLUE);
            DrawRectangle (player->posX, player->posY, 100, 100, WHITE);
            DrawFPS (10, 10);
        }

        EndDrawing ();
    }

    enet_host_destroy(server);
}
