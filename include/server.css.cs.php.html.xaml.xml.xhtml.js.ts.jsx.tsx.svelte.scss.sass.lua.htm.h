#ifndef _SERVER_H
#define _SERVER_H

struct Server {
    void* host;
    void* packet;
} typedef Server;

Server serverInit (Server* server);
void serverTerminate ();
void serverServiceEvents (Server* server);

#endif