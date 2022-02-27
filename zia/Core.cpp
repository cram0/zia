/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Core
*/

#include "Core.hpp"

#include <dlfcn.h>

Core::Core()
{
    std::cout << "Core created" << std::endl;
}

Core::~Core()
{

}

void Core::loadConfig(std::string const &path)
{

}

void Core::listModules() const
{

}

// IConfig *Core::getConfig() const
// {
//     return;
// }

IModule *Core::getModule(ModuleType type) const
{
    if (modules.find(type) == modules.end()) {
        return nullptr;
    }
    return modules.at(type);
}

void Core::registerModule(ModuleType type)
{
    char *error = nullptr;
    IModule *(*tmp)() = nullptr;
    void *handle = nullptr;

    if (type == ModuleType::NETWORK) {
        handle = dlopen("../modules/network/libnetwork.so", RTLD_LAZY | RTLD_LOCAL);

        if (!handle) {
            fprintf(stderr, "%s\n", dlerror());
            exit(EXIT_FAILURE);
        }

        *(void **)(&tmp) = dlsym(handle, "createNetworkModule");
    }
    if (type == ModuleType::PHP_CGI) {
        handle = dlopen("../modules/php/libphp.so", RTLD_LAZY | RTLD_LOCAL);

        if (!handle) {
            fprintf(stderr, "%s\n", dlerror());
            exit(EXIT_FAILURE);
        }

        *(void **)(&tmp) = dlsym(handle, "createPhpCgiModule");
    }
    if (type == ModuleType::SSLmod) {
        handle = dlopen("../modules/ssl/libssl.so", RTLD_LAZY | RTLD_LOCAL);

        if (!handle) {
            fprintf(stderr, "%s\n", dlerror());
            exit(EXIT_FAILURE);
        }

        *(void **)(&tmp) = dlsym(handle, "createSSLModule");
    }

    if ((error = dlerror()) != NULL)  {
            fprintf(stderr, "%s\n", error);
            exit(EXIT_FAILURE);
    }

    IModule *pp = (*tmp)();
    pp->setCore(*this);

    modules.emplace(std::make_pair(type, pp));
    modules_handles.emplace(std::make_pair(type, handle));
}

void Core::unregisterModule(ModuleType type)
{
    if (modules.find(type) == modules.end()) {
        std::cout << "Unregistering module of type " << type << " failed probably not in the list or already removed" << std::endl;
        return;
    }
    delete modules[type];
    dlclose(modules_handles[type]);
    modules.erase(type);
    modules_handles.erase(type);
}

std::unordered_map<ModuleType, IModule *> Core::getModules() const
{
    return modules;
}

void Core::send(std::any payload, ModuleType type)
{
    if (modules.find(type) == modules.end()) {
        std::cout << "Send failed : module of type "<< type <<" not in modules list" << std::endl;
        return;
    }
    modules[type]->receive(payload);
}
