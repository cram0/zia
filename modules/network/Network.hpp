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
   public:
        Network();
        Network(ICore &coreRef);
        ~Network();
        ICore *getCore() const;
        void setCore(ICore &coreRef);
        void init();
        void sslRequestCallback(std::string request);
        void receive(std::any payload, ModuleType sender);
        bool load(std::any payload);
        bool unload();
        std::string getName() const;
        ModuleType getType() const;

    [[noreturn]] void run();
#if(_WIN32)
        void processRequest(SOCKET s_conn);
#else
        void processRequest(int s_conn);
#endif
};

extern "C" ZIA_API Network *createNetworkModule(ICore &coreRef);

#endif /* !NETWORK_HPP_ */
