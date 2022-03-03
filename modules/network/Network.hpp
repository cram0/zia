/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Network
*/

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include "IModule.hpp"

class ICore;

class Network : public IModule {
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
        void run();
        void processRequest(int s_conn);
};

#endif /* !NETWORK_HPP_ */
