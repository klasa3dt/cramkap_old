#include "Client.h"
#include <enet.h>
#include <stdio.h>

void clientInit (Client* client, const char* ip, uint16_t port) {

    ENetAddress address;
    enet_address_set_host (&address, ip);
    address.port = port;

    if (enet_initialize ()) {

        fprintf (stderr, "Failed to initialize enet");
        exit (EXIT_FAILURE);
    }

    if (!(client->host = enet_host_create (NULL, 1, 2, 0, 0))) {

        fprintf(stderr, "Failed to create enet client");
        exit(EXIT_FAILURE);
    }

    if (!(client->peer = enet_host_connect (client->host, &address, 1, 0))) {

        fprintf(stderr, "Failed to connect peer");

        // TODO: Proper error handling
    }

    while (enet_host_service(client->host, &client->event, 10000) > 0) {

        switch (client->event.type) {

        case ENET_EVENT_TYPE_CONNECT:
            return;

        default:
            puts ("Hejka timeout zjebie");
            break;
        }
    }
}

void clientSendData(Client* client, const void* data, size_t size) {

    // TODO: Resize packet instead of constantly allocating and freeing
    client->packet = enet_packet_create (data, size, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send (client->peer, 0, client->packet);
    enet_packet_destroy (client->packet);
}

int clientHostService(Client* client) {

    return enet_host_service(client->host, &client->event, 0);
}

void clientTerminate(Client* client) {

    if (client->peer){

        enet_peer_disconnect(client->peer, 0);

        while (enet_host_service (client->host, &client->event, 10) > 0) {

            switch (client->event.type) {

            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy (client->event.packet);
                break;
            default:
                break;
            }
        }
    }

    enet_host_destroy(client->host);
    enet_deinitialize();

    memset(client, 0, sizeof(Client));
}
