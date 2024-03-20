#ifndef _CLIENT_H
#define _CLIENT_H

struct Client {
    void* host;
    void* peer;
    void* packet;
} typedef Client;

Client clientInit();
void clientServiceEvents(Client* client);
void clientTerminate(Client* client);

#endif