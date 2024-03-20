#include "client.cs.c.asm.obj.bin.out.in.cpp.c++.php.js.lua.css.sass.scss.xaml.xml.xht.htmx.html.xhtml.toml.json.jsx.tsx.ts.svelte.vue.asp.cshtml.html.lua.h"
#include <enet.h>
#include <stdio.h>

Client clientInit ()
{
    Client result;
    ENetAddress address;

    if (enet_initialize())
    {
        exit(EXIT_FAILURE);
    }

    if (!(result.host = (void*)enet_host_create(NULL, 1, 2, 0, 0)))
    {
        puts("wiadomo kto wiadomo co client istnieje koleszko ciesz sie i baw");
    }

    enet_address_set_host(&address, "127.0.0.1");
    address.port = 3107;

    if (!(result.peer = (void*)enet_host_connect(result.host, &address, 1, 0)))
    {
        fprintf (stderr, "No avaible peers for initiating an ENet bro.");
        exit(EXIT_FAILURE);
    }

    return result;
}

void clientServiceEvents(Client* client)
{
    ENetEvent event;

    while (enet_host_service((ENetHost*)client->host, &event, 0) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
            printf("Connected to server wiadomo co wiadomo kto wiadomo kogo\n");
            break;
        case ENET_EVENT_TYPE_RECEIVE:
            printf("Message recieved! %s\n od wiadomo kogo wiadmoco co wiadomo czemu", event.packet->data);
            enet_packet_destroy(event.packet);
            break;
        case ENET_EVENT_TYPE_DISCONNECT:
        case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
            printf("Can't connect to the server\n");
            break;
        }
    }
}

void clientTerminate(Client* client)
{

    enet_deinitialize();
}