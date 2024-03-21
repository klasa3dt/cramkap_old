#include "Server.h"
#include <enet.h>
#include <stdio.h>

void serverInit(Server* server, uint16_t port)
{
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = port;

    if (enet_initialize())
    {
        fprintf(stderr, "Failed to initialize enet");
        exit(EXIT_FAILURE);
    }

    if (!(server->host = enet_host_create(&address, 10, 2, 0, 0)))
    {
        fprintf(stderr, "Failed to create a server");
        exit(EXIT_FAILURE);
    }
}

int serverHostService(Server* server) {

    return enet_host_service(server->host, &server->event, 0);
}

void serverSendDataToClient (Server* server, ENetPeer* clientPeer, void* data, size_t size) {
    
    server->packet = enet_packet_create (data, size,ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send (clientPeer, 0, server->packet);
    enet_packet_destroy (server->packet);
}

void serverSendDataToAllClients (Server* server, void* data, size_t size) {

    server->packet = enet_packet_create (data, size, ENET_PACKET_FLAG_RELIABLE);
    enet_host_broadcast (server->host, 0, server->packet);
    enet_packet_destroy (server->packet);
}


void serverTerminate(Server* server)
{
    enet_host_destroy(server->host);
    
    enet_deinitialize();
    
    memset(server, 0, sizeof(Server));
}