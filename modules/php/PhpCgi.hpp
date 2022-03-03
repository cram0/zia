/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** PhpCgi
*/

#ifndef PHPCGI_HPP_
#define PHPCGI_HPP_

#include "IModule.hpp"

#ifdef _WIN32
#    ifdef ZIA_EXPORTS
#        define ZIA_API __declspec(dllexport)
#    else
#        define ZIA_API __declspec(dllimport)
#    endif
#else
#    define ZIA_API
#endif

class ZIA_API PhpCgi : public IModule {
    private:
        ICore *core;
        std::string name;
        ModuleType type;
        char *av[3];
    public:
        PhpCgi();
        PhpCgi(ICore &coreRef);
        ~PhpCgi();
        ICore *getCore() const;
        void setCore(ICore &coreRef);
        void receive(std::any payload, ModuleType sender);
        bool load(std::any payload);
        bool unload();
        std::string getName() const;
        ModuleType getType() const;
};
extern "C" ZIA_API PhpCgi *createPhpCgiModule();

#endif /* !PHPCGI_HPP_ */
