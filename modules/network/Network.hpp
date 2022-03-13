/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Network
*/

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#if(_WIN32)
#include <WinSock2.h>
#else
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include "IModule.hpp"

class ICore;

#ifdef _WIN32
#    ifdef ZIA_EXPORTS
#        define ZIA_API __declspec(dllexport)
#    else
#        define ZIA_API __declspec(dllimport)
#    endif
#else
#    define ZIA_API
#endif

class ZIA_API Network : public IModule {
    private:
        ICore *core;
        std::string name;
        ModuleType type;
        bool running;
#if(_WIN32)
        SOCKET s_listen;
#else
        int s_listen;
#endif
   public:
        Network();
        Network(ICore &coreRef);
        ~Network();

        /**
         * @brief Get the Core reference
         *
         * @return ICore*
         */
        ICore *getCore() const;

        /**
         * @brief Set the Core reference
         *
         * @param coreRef
         */
        void setCore(ICore &coreRef);

        /**
         * @brief Initialize data for the Network module
         *
         */
        void init();

        /**
         * @brief Used by the SSL module to process a request then send it back
         *
         * @param request
         */
        void sslRequestCallback(std::string request);

        /**
         * @brief Receives a payload from a specific module
         *
         * @param payload
         * @param sender
         */
        void receive(std::any payload, ModuleType sender);

        /**
         * @brief Load the module
         *
         * @param payload
         * @return true
         * @return false
         */
        bool load(std::any payload);

        /**
         * @brief Unload the module
         *
         * @return true
         * @return false
         */
        bool unload();

        /**
         * @brief Get the Name of the module
         *
         * @return std::string
         */
        std::string getName() const;

        /**
         * @brief Get the ModuleType of the module
         *
         * @return ModuleType
         */
        ModuleType getType() const;

        /**
         * @brief Set the configuration to the module
         *
         * @param confKey
         * @param server
         */
        void setConfig(const char *confKey, sockaddr_in *server);

        /**
         * @brief Runs the Network module
         *
         */
        void run();
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
};

extern "C" ZIA_API Network *createNetworkModule(ICore &coreRef);

#endif /* !NETWORK_HPP_ */
