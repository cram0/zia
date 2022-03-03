/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Request
*/

#ifndef REQUEST_HPP_
#define REQUEST_HPP_

#include <string>

#if(_WIN32)
    #include <WinSock2.h>
#else
    #include <unistd.h>
    #include <sys/socket.h>
#endif

#include <openssl/ssl.h>

class Request {
    public:
#if(_WIN32)
        Request(SOCKET socket, const std::string &file_path, SSL *ssl);
#else
        Request(int socket, const std::string &file_path, SSL *ssl);
#endif

        const std::string getFilePath() const;
        void setFilePath(const std::string &file_path);

        const std::string getData() const;
        void setData(const std::string &data);

#if(_WIN32)
        const SOCKET getSocket() const;
#else
        const int getSocket() const;
#endif

        void setSocket(int socket);

        SSL *getSsl() const;
        void setSsl(SSL *ssl);
        ~Request();

    protected:
    private:
        std::string m_data;
        std::string m_file_path;
        bool m_file_valid{};
#if(_WIN32)
        SOCKET m_socket;
#else
        int m_socket;
#endif
        SSL* m_ssl = nullptr;
};

#endif /* !REQUEST_HPP_ */
