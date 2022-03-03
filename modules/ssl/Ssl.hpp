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

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Ssl : public IModule, public ISsl {
    private:
        ICore *core;
        std::string name;
        ModuleType type;
        std::function<void(std::string HttpsRequestBuffer)> m_requestCallback;

        sockaddr_in m_infos;
        int s_serv;
    public:
        Ssl();
        Ssl(ICore &coreRef);
        ~Ssl();
        void setCore(ICore &coreRef);
        ICore *getCore() const;
        void run();
        void setRequestCallback(std::function<void(std::string HttpsRequestBuffer)> requestCallback);
        void sendReponse(std::string HttpsResponse);

        void processRequest(int s_conn);

        void receive(std::any payload, ModuleType sender);
        bool load(std::any payload);
        bool unload();
        std::string getName() const;
        ModuleType getType() const;
};

#endif /* !SSL_HPP_ */
