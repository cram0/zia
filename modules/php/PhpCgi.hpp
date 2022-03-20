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
        ICore *core{};
        std::string name;
        ModuleType type;
        [[maybe_unused]] char *av[3]{};
    public:
        PhpCgi();
        explicit PhpCgi(ICore &coreRef);
        ~PhpCgi() override;
        [[nodiscard]] ICore *getCore() const override;
        void setCore(ICore &coreRef) override;
        void receive(std::any payload, ModuleType sender) override;
        bool load(std::any payload) override;
        bool unload() override;
        [[nodiscard]] std::string getName() const override;
        [[nodiscard]] ModuleType getType() const override;
};

extern "C" [[maybe_unused]] ZIA_API PhpCgi *createPhpCgiModule(ICore &coreRef);

#endif /* !PHPCGI_HPP_ */
