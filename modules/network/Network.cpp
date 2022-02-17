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
#include <fstream>
#include <sstream>
#include <ostream>
#include <istream>
#include <string>
#include <cstring>
#include <thread>

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

    int CHUNK_SIZE = 4096;
    int s_conn = -1;
    int enable = 1;
    int s_listen = socket(AF_INET, SOCK_STREAM, 0);

    // Supprimer en production //
    if (setsockopt(s_listen, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        std::cerr << "setsockopt(SO_REUSEADDR) failed" << std::endl;
        exit(1);
    }

    if (setsockopt(s_listen, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int)) < 0) {
        std::cerr << "setsockopt(SO_REUSEPORT) failed" << std::endl;
        exit(1);
    }
    // Supprimer en production //

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
        std::string recv_msg;
        char buf[CHUNK_SIZE] = {0};

        std::cout << "Awaiting connections ..." << std::endl;
        s_conn = accept(s_listen, (sockaddr *)&conn_addr, &conn_addr_len);

        int recv_size = recv(s_conn, buf, CHUNK_SIZE, 0);
        recv_msg += buf;

        while (recv_size == CHUNK_SIZE) {
            memset(buf, 0, CHUNK_SIZE);
            recv_size = recv(s_conn, buf, CHUNK_SIZE, 0);
            recv_msg += buf;
        }

        std::string request_method, request_file, request_version;

        std::istringstream iss(recv_msg);
        iss >> request_method >> request_file >> request_version;

        std::cout << request_method << request_file << request_version << std::endl;

        std::stringstream response("<h1>404 File not found</h1>");
        std::ifstream f_html("../../www" + request_file);

        if (f_html.good()) {
            response.str("");
            response.clear();
            response << f_html.rdbuf();
        }

        std::ostringstream stream;
        stream << "HTTP/1.1 200 OK\r\n";
        stream << "Content-Type: text/html\r\n";
        stream << "Content-Length: " << response.str().length();
        stream << "\r\n\r\n";
        stream << response.str();
        send(s_conn, stream.str().c_str(), 4096, 0);
        close(s_conn);
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