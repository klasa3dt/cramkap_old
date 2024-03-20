//#define RAYGUI_IMPLEMENTATION
#include "enet.h"
//#include "raygui.h"
//#include <raylib.h>
#include <stdio.h>
#include "Client.h"
#include "Game.h"

void clientLoop ();
void serverLoop ();
int main (int argc, char** argv) {

    //if (enet_initialize())
    //{
    //    return EXIT_FAILURE;
    //}

    loadGame(800, 600, "Simple multipayer game");

    switch (selectGameConnectionType())
    {
    case GAME_CONNECTION_TYPE_CLIENT:
        clientLoop ();
        break;
    case GAME_CONNECTION_TYPE_SERVER:
        //serverLoop ();
        break;
    default:
        break;
    }

    closeGame();

    //enet_deinitialize();
}


//void sendPlayerPosition (ENetPeer* peer, ENetPacket* packet, Player* player) {
//    packet = enet_packet_create (player, sizeof(player), ENET_PACKET_FLAG_RELIABLE);
//    enet_peer_send (peer, 0, packet);
//    enet_packet_destroy (packet);
//}
//
void clientLoop()
{
    Client client;
    Player player = { 0.f, 0.f, 140.f };

    clientInit(&client, "127.0.0.1", 3107);

    while (windowAvailable())
    {
        while (clientHostService(&client) > 0)
        {
            switch (client.event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
                printf("Connected to server wiadomo co wiadomo kto wiadomo kogo\n");
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                printf("Message recieved! %s\n od wiadomo kogo wiadmoco co wiadomo czemu", client.event.packet->data);
                enet_packet_destroy(client.event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
            case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
                printf("Can't connect to the server\n");
                break;
            default:
                break;
            }
        }

        gameLogic(&player);

        if (player.posChanged)
        {
            clientSendData(&client, &player, sizeof(player));
        }
    }

    clientTerminate(&client);
}
//
//void serverLoop () {
//
//    ENetAddress address;
//    ENetHost* server;
//    ENetEvent event;
//    ENetPacket* packet;
//    address.host = ENET_HOST_ANY;
//    address.port = 3107;
//
//    Player* player;
//
//    int playersCount = 0;
//
//    if (!(server = enet_host_create(&address, 32, 2, 0, 0)))
//    {
//        fprintf(stderr, "Failed to create a server");
//        exit(EXIT_FAILURE);
//    }
//
//    while (!WindowShouldClose ()) {
//
//
//
//        BeginDrawing (); {
//
//            ClearBackground (BLUE);
//            DrawRectangle (player->posX, player->posY, 100, 100, WHITE);
//            DrawFPS (10, 10);
//        }
//
//        EndDrawing ();
//    }
//
//    enet_host_destroy(server);
//}
