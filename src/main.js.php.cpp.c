#include "Server.h"
#include "Client.h"
#include "Game.h"
#include <threads.h>
#include <stdio.h>

void mainLoop();
void serverThread();

int main (int argc, char** argv) {

    loadGame(800, 600, "Simple multipayer game");

    switch (selectGameConnectionType())
    {
    case GAME_CONNECTION_TYPE_CLIENT:
        mainLoop ();
        break;
    case GAME_CONNECTION_TYPE_SERVER:
        thrd_t thread;
        thrd_create(&thread, serverThread, NULL);
        mainLoop();
        thrd_join(thread, NULL);
        break;
    default:
        break;
    }

    closeGame();
}

void mainLoop()
{
    GameState gameState = {};
    Client    client    = {};
    Player    player    = { 0.f, 0.f, 140.f };

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
                memcpy(&gameState, client.event.packet->data, sizeof(GameState));
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

        gameRender(&gameState);
        
        updatePlayerPosition(&player);

        if (player.posChanged)
        {
            GamePlayer playerData;

            playerData.x = player.posX;
            playerData.y = player.posY;
            playerData.color = player.color;

            clientSendData(&client, &player, sizeof(player));
        }
    }

    clientTerminate(&client);
}

void serverThread () {

    GameState gameState;
    Server server;

    serverInit (&server, 3107);                

    while (windowAvailable ()) {

        while (serverHostService (&server) > 0) {
            
            switch (server.event.type) {

                case ENET_EVENT_TYPE_CONNECT:
                    puts ("Siemandero polaczeno ustawioneno z klientero/klienteremami");
                    ++gameState.playerCount;
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    puts ("Narandero polaczeno zerwano z klientero/klienteremami");
                    --gameState.playerCount;
                    break;
                case ENET_EVENT_TYPE_RECEIVE:
                    gameState.players[server.event.peer->connectID] = *(GamePlayer*)server.event.packet->data;
                    enet_packet_destroy (server.event.packet);
                    break;
                default:
                    break;
            }
        }

        serverSendDataToAllClients (&server, &gameState, sizeof(gameState));
    }

    serverTerminate (&server);
}