/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Network
*/

#include "Network.hpp"
#include "Request.hpp"
#include "ISsl.hpp"

#include <sys/socket.h>

// Remplacer ces librairies pour la structure sockaddr_in
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
#include <thread>

Network::Network()
{
    type = ModuleType::NETWORK;
    name = "NetworkName";
    std::cout << "Network created" << std::endl;
    core = nullptr;
}

Network::Network(ICore &coreRef) : Network()
{
    core = &coreRef;
}

Network::~Network()
{
    std::cout << "Network destroyed" << std::endl;
}

void Network::init()
{

}

const std::string Network::getContentType(const std::string &file_extension)
{
    return (contentTypeMap[file_extension]);
}

void Network::processRequest(int s_conn)
{
    std::string recv_msg;
    char buf[CHUNK_SIZE] = {0};

    int recv_size = recv(s_conn, buf, CHUNK_SIZE, 0);
    recv_msg += buf;

    while (recv_size == CHUNK_SIZE) {
        memset(buf, 0, CHUNK_SIZE);
        recv_size = recv(s_conn, buf, CHUNK_SIZE, 0);
        recv_msg += buf;
    }

    std::string request_method, request_file, request_version;

    std::cout << recv_msg << std::endl;

    std::istringstream iss(recv_msg);
    iss >> request_method >> request_file >> request_version;

    std::cout << request_method << " " << request_file << " " << request_version << std::endl;

    std::string full_path = "../../www" + request_file;
    std::string file_extension = std::filesystem::path(full_path).extension();

    Request request(s_conn, full_path, nullptr);

    std::ifstream f_data(full_path);

    if (f_data.is_open()) {
        std::cout << "File exists" << std::endl;
        if (file_extension == ".php") {
            getCore()->send(request, ModuleType::PHP_CGI);
            return;
        }
        else {
            std::stringstream data;
            data << f_data.rdbuf();
            request.setData(data.str());
            receive(request);
            return;
        }
    }
    else {
        std::cout << "File doesn't exist" << std::endl;
        std::ostringstream response;
        response << "HTTP/1.1 404 NOT FOUND\r\n";
        response << "Content-Length: " << 0;
        response << "\r\n\r\n";

        send(s_conn, response.str().c_str(), response.str().length(), 0);
        close(s_conn);
        return;
    }
}

void Network::run()
{
    // Seulement pour Linux
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(11111);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    //
    // Il faut trouver un équivalent pour sockaddr_in
    // Il faut trouver un équivalent pour htons() et htonl()

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
        // Seulement sur Linux
        sockaddr_in conn_addr = {0};
        //
        socklen_t conn_addr_len = {0};

        std::cout << "Awaiting connections ..." << std::endl;
        s_conn = accept(s_listen, (sockaddr *)&conn_addr, &conn_addr_len);

        if (s_conn == -1) {
            std::cerr << "Accept error" << std::endl;
        }

        std::thread request(&Network::processRequest, this, s_conn);
        request.detach();
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
    Request request = std::any_cast<Request>(payload);
    std::string f_extension = std::filesystem::path(request.getFilePath()).extension();
    std::ostringstream stream;

    stream << "HTTP/1.1 200 OK\r\n";
    stream << "Content-Length: " << request.getData().length() << "\r\n";
    if (f_extension != ".php") {
        stream << "Content-Type: "<< getContentType(f_extension);
        stream << "\r\n\r\n";
    }
    stream << request.getData();

    send(request.getSocket(), stream.str().c_str(), stream.str().length(), 0);

    close(request.getSocket());
}

void Network::sslRequestCallback(std::string request)
{
    dynamic_cast<ISsl *>(core->getModule(ModuleType::SSL_MODULE))->sendReponse(request);
}

bool Network::load(std::any payload)
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

extern "C" Network *createNetworkModule() {
    return (new Network());
}