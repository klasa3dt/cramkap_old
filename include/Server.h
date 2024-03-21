#ifndef SERVER_H
#define SERVER_H
#include <enet.h>

struct Server {
    ENetHost*   host;
    ENetPacket* packet;
    ENetEvent   event;
    int         peerCount;
    ENetPeer**  peers;
} typedef Server;

void serverInit(Server* server, uint16_t port);
int serverHostService(Server* server);
void serverSendDataToClient (Server* server, ENetPeer* clientPeer, void* data, size_t size);
void serverSendDataToAllClients (Server* server, void* data, size_t size);
void serverTerminate(Server* server);

#endif