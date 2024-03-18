#define ENET_IMPLEMENTATION
#include <raylib.h>
#include "enet.h"
#include <stdio.h>

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

    InitWindow (800, 600, "Simple multipayer game");

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

void clientLoop () {

    ENetAddress address;
    ENetHost* client;
    ENetEvent event;
    ENetPeer* peer;

    client = enet_host_create (NULL, 1, 2, 0, 0);

    if (client) {
        puts("wiadomo kto wiadomo co client istnieje czarnuchu ciesz sie i baw");
    }

    enet_address_set_host (&address, "25.47.18.54");
    address.port = 3107;

    peer = enet_host_connect (client, &address, 1, 0);

    if (peer) {
        puts("wiadomo kto wiadomo co peer istnieje czarnuchu ciesz sie i baw peer peer peer peer perr eppepperer");
    }
    
    if (!peer) {
        fprintf (stderr, "No avaible peers for initiating an ENet bro.");
        exit (EXIT_FAILURE);
    }


    while (!WindowShouldClose()) {

        if (IsKeyPressed (KEY_S)) {

            if (
                enet_host_service (client, &event, 5000) > 0
            ) {
                puts ("Connection to widomo co wiadomo kto succeeded");

                char* message = "Wiadomo co wiadomo kto";
                ENetPacket* packet = 
                enet_packet_create (message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);

                enet_peer_send (peer, 0, packet);
            }

            else {
                enet_peer_reset (peer);

                    puts ("Connection to wiadomo co wiadomo kto failed");
            }
        }

        BeginDrawing (); {

            ClearBackground (PINK);
            DrawText ("Clint", GetRenderWidth () >> 1, GetRenderHeight () >> 1, 20, BLACK);
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

    address.host = ENET_HOST_ANY;
    address.port = 3107;

    if (!(server = enet_host_create(&address, 32, 2, 0, 0)))
    {
        fprintf(stderr, "Failed to create a server");
        exit(EXIT_FAILURE);
    }
    char message[512] = {};

    while (!WindowShouldClose ()) {

        while (enet_host_service(server, &event, 0) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
                printf ("A new client connected from %x:%u.\n", 
                        event.peer -> address.host,
                        event.peer -> address.port);
                event.peer -> data = "Client information";
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                printf ("A packet of length %u containing %s was received from %s on channel %u.\n",
                        event.packet -> dataLength,
                        event.packet -> data,
                        event.peer -> data,
                        event.channelID);
                strcpy(message, event.packet->data);
                enet_packet_destroy (event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                printf ("%s disconnected.\n", event.peer -> data);
                event.peer -> data = NULL;
                break;
            default:
                break;
            }
        }

        BeginDrawing (); {

            ClearBackground (BLUE);
            DrawText ("Sever", GetRenderWidth () >> 1, GetRenderHeight () >> 1, 20, BLACK);
            DrawText (message, GetRenderWidth () >> 1, (GetRenderHeight () >> 1) - 30, 20, BLACK);
            DrawFPS (10, 10);
        }

        EndDrawing ();
    }

    enet_host_destroy(server);
}
