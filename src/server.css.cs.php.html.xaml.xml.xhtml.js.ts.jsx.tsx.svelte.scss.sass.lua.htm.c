#include "server.css.cs.php.html.xaml.xml.xhtml.js.ts.jsx.tsx.svelte.scss.sass.lua.htm.h"
#include <enet/enet.h>

Server serverInit (Server* server) {

    Server result;

    if (enet_initialize ()) {
        exit (EXIT_FAILURE);
    }
}

int hostService(Server* server)
{
    ENetEvent event;
    int result = enet_host_service((ENetHost*)server->host,)
}

void serverServiceEvents (Server* server) {
    ENetEvent event;
    while (enet_host_service(server, &event, 0) > 0) {

            switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                printf ("A new client connected from %x:%u.\n", 
                        event.peer -> address.host,
                        event.peer -> address.port);
                event.peer -> data = "Client information";
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                player = (Player*)event.packet->data;
                enet_packet_destroy (event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                printf ("%s disconnected.\n", event.peer->data);
                enet_packet_destroy (event.packet);
                break;
            default:
                break;
            }
        }
}

void serverTerminate () {

}