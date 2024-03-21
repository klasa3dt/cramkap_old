#include "Server.h"
#include "Client.h"
#include "Game.h"
#include <threads.h>

void clientLoop ();
void serverLoop ();
int main (int argc, char** argv) {

    loadGame(800, 600, "Simple multipayer game");

    switch (selectGameConnectionType())
    {
    case GAME_CONNECTION_TYPE_CLIENT:
        clientLoop ();
        break;
    case GAME_CONNECTION_TYPE_SERVER:
        serverLoop ();
        break;
    default:
        break;
    }

    closeGame();
}

void clientLoop()
{
    Client client = {};
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

void serverThread()
{
    Server server = {};

    serverInit(&server, 3107);

    while (windowAvailable())
    {

    }

    serverTerminate(&server);
}

void serverLoop () {

    thrd_t thread;
    thrd_create(&thread, serverThread, NULL);

    Client client = {};
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

    thrd_join(thread, NULL);
}
