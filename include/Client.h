#ifndef CLIENT_H
#define CLIENT_H
#include <enet.h>

struct Client {
    ENetHost*   host;
    ENetPeer*   peer;
    ENetPacket* packet;
    ENetEvent   event;
} typedef Client;

void clientInit(Client* client, const char* ip, uint16_t port);
void clientSendData(Client* client, const void* data, size_t size);
int clientHostService(Client* client);
void clientTerminate(Client* client);

#endif