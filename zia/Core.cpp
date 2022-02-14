/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Core
*/

#include "ICore.hpp"

#include <dlfcn.h>

Core::Core()
{
    std::cout << "Core created" << std::endl;
    handle = nullptr;
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

// IModule *Core::getModule(ModuleType type) const
// {
//     return;
// }

void Core::registerModule(ModuleType type)
{
    char *error;
    IModule *(*tmp)();
    handle = dlopen("../modules/network/libnetwork.so", RTLD_LAZY | RTLD_LOCAL);

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    *(void **)(&tmp) = dlsym(handle, "getNetworkModule");

    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    std::cout << (*tmp)()->getName() << std::endl;
    
}

void Core::unregisterModule(ModuleType type)
{

}

std::unordered_map<ModuleType, IModule *> Core::getModules() const
{
    return modules;
}

void Core::send(std::any payload, ModuleType type)
{

}
