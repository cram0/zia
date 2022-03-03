/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Network
*/

#include "Network.hpp"
#include "Request.hpp"
#include "ISsl.hpp"

#define ZIA_EXPORTS
#include "Network.hpp"
#include "Request.hpp"
#include "ISsl.hpp"

#if(_WIN32)
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <io.h>
#else
#include <unistd.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
#endif

#include <istream>
#include <string>
#include <cstring>
#include <thread>
#include <filesystem>
#include <fcntl.h>
#include <iomanip>
#include <thread>
#include <sstream>

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

#if(_WIN32)
void Network::processRequest(SOCKET s_conn)
#else
void Network::processRequest(int s_conn)
#endif
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
    std::string file_extension = std::filesystem::path(full_path).extension().string();

    Request request(s_conn, full_path, nullptr);

    std::ifstream f_data(full_path);

    if (f_data.is_open()) {
        std::cout << "File exists" << std::endl;
        if (file_extension == ".php") {
            getCore()->send(request, ModuleType::NETWORK,  ModuleType::PHP_CGI);
            return;
        }
        else {
            std::stringstream data;
            data << f_data.rdbuf();
            request.setData(data.str());
            receive(request, ModuleType::NETWORK);
            return;
        }
    }
    else {
        std::cout << "File doesn't exist" << std::endl;
        std::ostringstream response;
        response << "HTTP/1.1 404 NOT FOUND\r\n";
        response << "Content-Length: " << 0;
        response << "\r\n\r\n";

#if(_WIN32)
        if (response.str().length() > MAXINT32)
            throw;
        send(s_conn, response.str().c_str(), (int)response.str().length(), 0);
        _close((int)s_conn);
#else
        send(s_conn, response.str().c_str(), response.str().length(), 0);
        close(s_conn);
#endif
        return;
    }
}

[[noreturn]] void Network::run()
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
#if(_WIN32)
    SOCKET s_conn = -1;
   const char enable = 1;
#else
    int s_conn = -1;
    int enable = 1;
#endif

    auto s_listen = socket(AF_INET, SOCK_STREAM, 0);

    // Supprimer en production //
    if (setsockopt(s_listen, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        std::cerr << "setsockopt(SO_REUSEADDR) failed" << std::endl;
        exit(1);
    }

    if (setsockopt(s_listen, SOL_SOCKET, SO_BROADCAST, &enable, sizeof(int)) < 0) {
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

void Network::receive(std::any payload, ModuleType sender)
{
    Request request = std::any_cast<Request>(payload);
    std::string f_extension = std::filesystem::path(request.getFilePath()).extension().string();
    std::ostringstream stream;

    stream << "HTTP/1.1 200 OK\r\n";
    stream << "Content-Length: " << request.getData().length() << "\r\n";
    if (f_extension != ".php") {
        stream << "Content-Type: "<< getContentType(f_extension);
        stream << "\r\n\r\n";
    }
    stream << request.getData();

#if(_WIN32)
    if (stream.str().length() > MAXINT32) throw;
    send(request.getSocket(), stream.str().c_str(), (int)stream.str().length(), 0);
    _close((int)request.getSocket());
#else
    send(request.getSocket(), stream.str().c_str(), stream.str().length(), 0);
    close(request.getSocket());
#endif
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