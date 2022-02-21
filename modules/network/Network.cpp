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
#include <filesystem>
#include <fcntl.h>
#include <iomanip>

Network::Network()
{
    type = ModuleType::NETWORK;
    name = "NetworkName";
    std::cout << "Network created" << std::endl;
    core = nullptr;

    init();
}

Network::Network(ICore &coreRef) : Network()
{
    core = &coreRef;
}

Network::~Network()
{

}

void Network::init()
{

}

const std::string Network::getContentType(const std::string &file_extension)
{
    return (contentTypeMap[file_extension]);
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
        sockaddr_in conn_addr = {0};
        socklen_t conn_addr_len = {0};
        std::string recv_msg;
        char buf[CHUNK_SIZE] = {0};

        std::cout << "Awaiting connections ..." << std::endl;
        s_conn = accept(s_listen, (sockaddr *)&conn_addr, &conn_addr_len);

        if (s_conn == -1) {
            std::cerr << "Accept error" << std::endl;
        }

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

        std::cout << " " <<  request_method << " " << request_file << " " << request_version << std::endl;

        std::string full_path = "../../www" + request_file;
        std::string file_extension = std::filesystem::path(full_path).extension();

        if (file_extension == ".php") {
            getCore()->send(full_path, ModuleType::PHP_CGI);

            // TODO
        }

        std::ifstream file_data(full_path);
        std::ostringstream stream;

        if (file_data.good()) {
            std::stringstream data;
            data << file_data.rdbuf();
            stream << "HTTP/1.1 200 OK\r\n";
            stream << "Content-Length: " << data.str().length() << "\r\n";
            stream << "Content-Type: "<< getContentType(file_extension);
            stream << "\r\n\r\n";
            stream << data.str();
        }
        else {
            stream << "HTTP/1.1 404 NOT FOUND\r\n";
            stream << "Content-Length: " << 0;
            stream << "\r\n\r\n";
        }

        send(s_conn, stream.str().c_str(), stream.str().length(), 0);

        close(s_conn);
    }
}

ICore *Network::getCore() const
{
    return core;
}

void Network::setCore(ICore &coreRef)
{
    core = &coreRef;
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

extern "C" Network *createNetworkModule(ICore &coreRef) {
    return (new Network(coreRef));
}