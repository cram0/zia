/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Ssl
*/

#ifndef SSL_HPP_
#define SSL_HPP_

#include "IModule.hpp"
#include "ISsl.hpp"

#if(_WIN32)
#include <WinSock2.h>
#include <WS2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#ifdef _WIN32
#    ifdef ZIA_EXPORTS
#        define ZIA_API __declspec(dllexport)
#    else
#        define ZIA_API __declspec(dllimport)
#    endif
#else
#    define ZIA_API
#endif

class Ssl : public IModule, public ISsl {
    private:
        ICore *core{};
        std::string name;
        ModuleType type;
        std::function<void(std::string HttpsRequestBuffer)> m_requestCallback;

        sockaddr_in m_infos{};
        int s_serv{};
    public:
        Ssl();
        Ssl(ICore &coreRef);
        ~Ssl();
        void setCore(ICore &coreRef);
        ICore *getCore() const;

    [[noreturn]] void run();
        void setRequestCallback(std::function<void(std::string HttpsRequestBuffer)> requestCallback);
        void sendReponse(std::string HttpsResponse);

    #if(_WIN32)
        void processRequest(SOCKET s_conn);
     #else
        void processRequest(int s_conn);
    #endif

        void receive(std::any payload, ModuleType sender);
        bool load(std::any payload);
        bool unload();
        std::string getName() const;
        ModuleType getType() const;
};

extern "C" ZIA_API Ssl *createSslModule();

#endif /* !SSL_HPP_ */
