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
#include "Config.hpp"
#include <nlohmann/json.hpp>

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

class ZIA_API Ssl : public IModule, public ISsl {
    private:
        ICore *core{};
        std::string name;
        ModuleType type;
    [[maybe_unused]] std::function<void(std::string HttpsRequestBuffer)> m_requestCallback;
        bool running;
#if(_WIN32)
        SOCKET s_listen{};
#else
        int s_listen;
#endif
    public:
        Ssl();
        explicit Ssl(ICore &coreRef);
        ~Ssl() override;
        void setCore(ICore &coreRef) override;
        [[nodiscard]] ICore *getCore() const override;

        /**
         * @brief Starts the module and listens on the set port
         *
         */
        void run();

        /**
         * @brief Apply the configuration to the SSL server
         *
         * @param confKey
         * @param server
         */
        void setConfig(const char *confKey, sockaddr_in *server) const;

        /**
         * @brief Set the Request Callback (DEPRECATED)
         *
         * @param requestCallback
         */
        void setRequestCallback(std::function<void(std::string HttpsRequestBuffer)> requestCallback) override;

        /**
         * @brief Send a clear HTTP response
         *
         * @param HttpsResponse
         */
        void sendReponse(std::string HttpsResponse) override;

    #if(_WIN32)
        /**
         * @brief Process the given request using a fd (for threaded use only)
         *
         * @param s_conn
         */
        void processRequest(SOCKET s_conn);
     #else
        /**
         * @brief Process the given request using a fd (for threaded use only)
         *
         * @param s_conn
         */
        void processRequest(int s_conn);
    #endif

        /**
         * @brief Receive a payload from a specific module
         *
         * @param payload
         * @param sender
         */
        void receive(std::any payload, ModuleType sender) override;

        /**
         * @brief Load the SSL module
         *
         * @param payload
         * @return true
         * @return false
         */
        bool load(std::any payload) override;

        /**
         * @brief Unload the SSL module
         *
         * @return true
         * @return false
         */
        bool unload() override;

        /**
         * @brief Get the Name of the module
         *
         * @return std::string
         */
        [[nodiscard]] std::string getName() const override;

        /**
         * @brief Get the ModuleType of the module
         *
         * @return ModuleType
         */
        [[nodiscard]] ModuleType getType() const override;
};

extern "C" [[maybe_unused]] ZIA_API Ssl *createSslModule(ICore &coreRef);

#endif /* !SSL_HPP_ */
