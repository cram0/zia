/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Network
*/

#include "INetwork.hpp"
#include "ICore.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

Network::Network(ICore &coreRef)
{
    core = &coreRef;
    type = ModuleType::NETWORK;
    name = "NetworkName";
    std::cout << "Network created" << std::endl;

    run();
}

Network::~Network()
{

}

void Network::run()
{
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(11111);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    char buf[4096];
    int s_conn = -1;
    int s_listen = socket(AF_INET, SOCK_STREAM, 0);
    if (s_listen == -1) {
        std::cerr << "Socket creation error" << std::endl;
        exit(1);
    }

    if (bind(s_listen, (sockaddr *)&server, sizeof(server)) < 0) {
        std::cerr << "Socket binding error" << std::endl;
        exit(1);
    }

    if (listen(s_listen, 10) < 0) {
        std::cerr << "Socket listening error" << std::endl;
        exit(1);
    }

    while(42) {
        sockaddr_in conn_addr;
        socklen_t conn_addr_len;

        std::cout << "Awaiting connections ..." << std::endl;
        s_conn = accept(s_listen, (sockaddr *)&conn_addr, &conn_addr_len);


        recv(s_conn, buf, 4096, 0);
        std::cout << buf << std::endl;
    }
}

ICore *Network::getCore() const
{
    return core;
}

void Network::receive(std::any payload)
{

}

bool Network::load()
{
    return true;
}

bool Network::unload()
{
    return true;
}

std::string Network::getName() const
{
    return name;
}

ModuleType Network::getType() const
{
    return type;
}

extern "C" Network *getNetworkModule(ICore &coreRef) {
    return (new Network(coreRef));
}