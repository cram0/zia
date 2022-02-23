/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Ssl
*/

#ifndef SSL_HPP_
#define SSL_HPP_

#include "IModule.hpp"

class Ssl : public IModule {
    private:
        ICore *core;
        std::string name;
        ModuleType type;
    public:
        Ssl();
        Ssl(ICore &coreRef);
        ~Ssl();
        void setCore(ICore &coreRef);
        ICore *getCore() const;
        void receive(std::any payload);
        bool load();
        bool unload();
        std::string getName() const;
        ModuleType getType() const;
};

#endif /* !SSL_HPP_ */
