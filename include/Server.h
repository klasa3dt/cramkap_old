#ifndef SERVER_H
#define SERVER_H
#include <enet.h>

struct Server {
    ENetEvent*  host;
    ENetPacket* packet;
    ENetEvent   event;
} typedef Server;

void serverInit(Server* server);
void serverTerminate(Server* server);
void serverServiceEvents(Server* server);

#endif