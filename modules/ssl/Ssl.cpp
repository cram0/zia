
/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Ssl
*/

#include "Ssl.hpp"
#include "Network.hpp"
#include "Request.hpp"

#include "sslutils.hpp"

#include <openssl/ssl.h>
#include <openssl/err.h>

#include <thread>
#include <string.h>
#include <unistd.h>
#include <ostream>
#include <istream>
#include <fstream>
#include <filesystem>
#include <string>

Ssl::Ssl()
{
    type = ModuleType::PHP_CGI;
    name = "SslName";
    std::cout << "Ssl created" << std::endl;

    ssl_utils::init_ssl();
}

Ssl::Ssl(ICore &coreRef) : Ssl()
{
    core = &coreRef;
}

Ssl::~Ssl()
{

}

void Ssl::setCore(ICore &coreRef)
{
    core = &coreRef;
}

ICore *Ssl::getCore() const
{
    return core;
}

void Ssl::setRequestCallback(std::function<void(std::string HttpsRequestBuffer)> requestCallback)
{
    this->m_requestCallback = requestCallback;
}

void Ssl::sendReponse(std::string HttpsResponse)
{

}

void Ssl::receive(std::any payload)
{
    Request request = std::any_cast<Request>(payload);

    SSL_write(request.getSsl(), request.getData().c_str(), request.getData().length());
}

void Ssl::processRequest(int s_conn)
{
    SSL *ssl;
    SSL_CTX *ctx = ssl_utils::create_context();
    ssl_utils::configure_context(ctx);

    ssl = SSL_new(ctx);
    if (SSL_set_fd(ssl, s_conn) == 0) {
        perror("Unable to set fd to ssl object");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    int ac_err = SSL_accept(ssl);
    SSL_set_accept_state(ssl);

    if (ac_err <= 0) {
        ssl_utils::SSL_print_error(ssl, ac_err);
    }

    std::string recv_msg;
    char buf[CHUNK_SIZE] = {0};

    int ssl_read_size = SSL_read(ssl, buf, CHUNK_SIZE);

    ssl_utils::SSL_print_error(ssl, ssl_read_size);

    recv_msg += buf;

    while (ssl_read_size == CHUNK_SIZE) {
        memset(buf, 0, CHUNK_SIZE);
        ssl_read_size = SSL_read(ssl, buf, CHUNK_SIZE);
        recv_msg += buf;
    }

    std::string request_method, request_file, request_version;

    // std::cout << recv_msg << std::endl;

    std::istringstream iss(recv_msg);
    iss >> request_method >> request_file >> request_version;

    std::cout << request_method << " " << request_file << " " << request_version << std::endl;

    std::string full_path = "../../www" + request_file;
    std::string file_extension = std::filesystem::path(full_path).extension();

    Request request(s_conn, full_path, ssl);

    std::ifstream f_data(full_path);

    // v fix this trash
    std::cout << "File : " << full_path << std::endl;

    if (f_data.is_open()) {
        std::cout << "File exists" << std::endl;
        if (file_extension == ".php") {
            getCore()->send(request, ModuleType::PHP_CGI);
        }
        else {
            std::stringstream data;
            data << f_data.rdbuf();
            request.setData(data.str());
            receive(request);
        }
    }
    else {
        std::cout << "File doesn't exist" << std::endl;
        std::ostringstream response;
        response << "HTTP/1.1 404 NOT FOUND\r\n";
        response << "Content-Length: " << 0;
        response << "\r\n\r\n";

        SSL_write(ssl, response.str().c_str(), response.str().length());
    }

    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    close(s_conn);
}

void Ssl::run()
{
    m_infos.sin_family = AF_INET;
    m_infos.sin_port = htons(22222);
    m_infos.sin_addr.s_addr = htonl(INADDR_ANY);

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

    if (bind(s_listen, (sockaddr *)&m_infos, sizeof(m_infos)) < 0) {
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

        std::cout << "Awaiting SSL connections ..." << std::endl;
        s_conn = accept(s_listen, (sockaddr *)&conn_addr, &conn_addr_len);

        if (s_conn == -1) {
            std::cerr << "Accept SSL error" << std::endl;
        }

        std::thread th(&Ssl::processRequest, *this, s_conn);
        th.detach();
    }
}

bool Ssl::load(std::any payload)
{
    return true;
}

bool Ssl::unload()
{
    return true;
}

std::string Ssl::getName() const
{
    return name;
}

ModuleType Ssl::getType() const
{
    return type;
}

extern "C" Ssl *createSslModule() {
    return (new Ssl());
}