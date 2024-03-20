#include "Server.h"
#include <enet.h>
#include <stdio.h>

void serverInit(Server* server)
{
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = 3107;

    if (enet_initialize())
    {
        fprintf(stderr, "Failed to initialize enet");
        exit(EXIT_FAILURE);
    }

    if (!(server->host = enet_host_create(&address, 32, 2, 0, 0)))
    {
        fprintf(stderr, "Failed to create a server");
        exit(EXIT_FAILURE);
    }
}

void serverTerminate(Server* server)
{
    enet_host_destroy(server->host);
}