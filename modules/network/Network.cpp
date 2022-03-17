/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Network
*/

#define ZIA_EXPORTS
#include "Network.hpp"
#include "Request.hpp"
#include "ISsl.hpp"
#include "Config.hpp"

#if(_WIN32)
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#include <io.h>
#else
#include <unistd.h>
#endif

#include <istream>
#include <string>
#include <cstring>
#include <thread>
#include <filesystem>
#include <sstream>

Network::Network()
{
    type = ModuleType::NETWORK;
    name = "NetworkName";
    std::cout << "Network created" << std::endl;
    core = nullptr;
    running = true;
}

Network::Network(ICore &coreRef) : Network()
{
    core = &coreRef;
    std::thread th(&Network::run, this);
    th.detach();
}

Network::~Network()
{
    std::cout << "Network destroyed" << std::endl;
#if(_WIN32)
    closesocket(s_listen);
    WSACleanup();
#else
    close(s_listen);
#endif
}

void Network::init()
{

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


    // std::cout << recv_msg << std::endl;

    std::istringstream iss(recv_msg);
    iss >> request_method >> request_file >> request_version;

    if (!isValidMethod(request_method)) {
        std::cout << "Bad method : " << request_method << std::endl;
#if(_WIN32)
        closesocket(s_conn);
#else
        close(s_conn);
#endif
        return;
    }

    if (!isValidHttpVersion(request_version)) {
        std::cout << "Bad HTTP version : " << request_version << std::endl;
#if(_WIN32)
        closesocket(s_conn);
#else
        close(s_conn);
#endif
        return;
    }


    // std::cout << request_method << " " << request_file << " " << request_version << std::endl;

    std::string full_path = "www" + request_file;
    std::string file_extension = std::filesystem::path(full_path).extension().string();

    Request request(s_conn, full_path, nullptr);

    std::ifstream f_data(full_path);

    if (f_data.is_open()) {

        std::cout << "File exists" << std::endl;
        if (file_extension == ".php") {
            if (getCore()->getModule(ModuleType::PHP_CGI)) {
                getCore()->send(request, ModuleType::SSL_MODULE, ModuleType::PHP_CGI);
            }
            else {
                std::ostringstream response;
                response << "HTTP/1.1 404 NOT FOUND\r\n";
                response << "Content-Length: " << 0;
                response << "\r\n\r\n";
#if(_WIN32)
                if (response.str().length() > MAXINT32)
                    throw;
                send(s_conn, response.str().c_str(), (int)response.str().length(), 0);
                closesocket(s_conn);
#else
                send(s_conn, response.str().c_str(), response.str().length(), 0);
                close(s_conn);
#endif
                return;
            }

            f_data.close();
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
        closesocket(s_conn);
#else
        send(s_conn, response.str().c_str(), response.str().length(), 0);
        close(s_conn);
#endif
    }
}

void Network::setConfig(const char *confKey, sockaddr_in *server)
{
    Config *config = (Config *)getCore()->getConfig();
    auto conf = std::any_cast<std::unordered_map<std::string, json>>((*config)[confKey]);

    if (conf != nullptr) {
        if (conf["ip"].type() == json::value_t::string) {
            if (isValidIpv4(conf["ip"]))
                server->sin_addr.s_addr = inet_addr(conf["ip"].get<std::string>().c_str());
            else
                std::cout << "Invalid ipv4" << std::endl;
        }
        if (conf["port"].type() == json::value_t::string) {
            if (isValidPort(conf["port"])) {
                std::string port = conf["port"].get<std::string>();
                server->sin_port = htons(std::atoi(port.c_str()));
            }
            else
                std::cout << "Invalid port" << std::endl;
        }
    }
}

void Network::run()
{
#if(_WIN32)
    //----------------------
    // Initialize Windsock.
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup failed with error: %ld\n", iResult);
        std::exit(1);
    }
    SOCKET s_conn;
    const char enable = 1;
#else
    int s_conn = -1;
    int enable = 1;
#endif

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(11111);

    setConfig("Network", &server);

    s_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

    if (setsockopt(s_listen, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        std::cerr << "network setsockopt(SO_REUSEADDR) failed" << std::endl;
        std::exit(1);
    }

    if (setsockopt(s_listen, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int)) < 0) {
        std::cerr << "network setsockopt(SO_REUSEPORT) failed" << std::endl;
        std::exit(1);
    }

#if(_WIN32)
    if (s_listen == INVALID_SOCKET) {
        wprintf(L"Network socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        std::exit(1);
    }
    if (bind(s_listen, (sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        wprintf(L"Network bind failed with error: %ld\n", WSAGetLastError());
        closesocket(s_listen);
        WSACleanup();
        std::exit(1);
    }

    if (listen(s_listen, 10) == SOCKET_ERROR) {
        wprintf(L"Network listen failed with error: %ld\n", WSAGetLastError());
        closesocket(s_listen);
        WSACleanup();
        std::exit(1);
    }
#else
    if (s_listen == -1) {
        std::cerr << "Network Socket creation error" << std::endl;
        std::exit(1);
    }

    if (bind(s_listen, (sockaddr *)&server, sizeof(server)) < 0) {
        std::cerr << "Network Socket binding error" << std::endl;
        std::exit(1);
    }

    if (listen(s_listen, 10) < 0) {
        std::cerr << "Network Socket listening error" << std::endl;
        std::exit(1);
    }
#endif

    while(running) {
        sockaddr_in conn_addr = {0};
        socklen_t sizeof_addr = sizeof(conn_addr);

        // std::cout << "Network Awaiting connections ..." << std::endl;
        s_conn = accept(s_listen, (sockaddr *)&conn_addr, &sizeof_addr);
#if(_WIN32)
        if (s_conn == INVALID_SOCKET) {
            wprintf(L"accept failed with error: %ld\n", WSAGetLastError());
            closesocket(s_listen);
            WSACleanup();
        }
#else
        if (s_conn == -1 && errno == EBADF) {
            perror("Accept network error");
            running = false;
            close(s_listen);
        }
#endif
        else {
            std::thread request(&Network::processRequest, this, s_conn);
            request.detach();
        }
    }

#if(_WIN32)
        closesocket(s_listen);
#else
        std::cout << "Network : Closing listening socket" << std::endl;
        close(s_listen);
#endif
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
    closesocket(request.getSocket());
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
    std::cout << "Unloaded module Network" << std::endl;
    running = false;
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

extern "C" ZIA_API Network *createNetworkModule(ICore &coreRef) {
    return new Network(coreRef);
}