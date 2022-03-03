/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Core
*/

#include "Core.hpp"
typedef IModule *(*IModuleDLL)();

Core::Core()
{
    std::cout << "Core created" << std::endl;
}

Core::~Core()
{

}

void Core::loadConfig(std::string const &path)
{
    std::cout << "Loading config..." << std::endl;
}

void Core::listModules() const
{

}

IConfig *Core::getConfig() const
{
    return (this->config);
}

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
    IModuleDLL getIModuleDLL = nullptr;
    HINSTANCE handle;

#if(_WIN32)
    if (type == ModuleType::NETWORK) {
        handle = LoadLibrary("bin/network.dll");

        if (handle == nullptr) {
            std::cout << "unable to load: " << "bin/network.dll" << " lib" << std::endl;
            exit(EXIT_FAILURE);
        }
        getIModuleDLL = (IModuleDLL)GetProcAddress(handle, "createNetworkModule");
        if (getIModuleDLL == nullptr) {
            std::cout << "cant get func 'createNetworkModule'" << std::endl;
            FreeLibrary(handle);
            exit(EXIT_FAILURE);
        }
    }
    if (type == ModuleType::PHP_CGI) {
        handle = LoadLibrary("bin/php.dll");

        if (handle == nullptr) {
            std::cout << "unable to load: " << "bin/php.dll" << " lib" << std::endl;
            exit(EXIT_FAILURE);
        }
        getIModuleDLL = (IModuleDLL)GetProcAddress(handle, "createPhpCgiModule");
        if (getIModuleDLL == nullptr) {
            std::cout << "cant get func 'createPhpCgiModule'" << std::endl;
            FreeLibrary(handle);
            exit(EXIT_FAILURE);
        }
    }
    if (type == ModuleType::SSL_MODULE) {
        handle = LoadLibrary("bin/ssl.dll");

        if (handle == nullptr) {
            std::cout << "unable to load: " << "bin/ssl.dll" << " lib" << std::endl;
            exit(EXIT_FAILURE);
        }
        getIModuleDLL = (IModuleDLL)GetProcAddress(handle, "createSslModule");
        if (getIModuleDLL == nullptr) {
            std::cout << "cant get func 'createSslModule'" << std::endl;
            FreeLibrary(handle);
            exit(EXIT_FAILURE);
        }
    }
#else
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
    if (type == ModuleType::SSL_MODULE) {
        handle = dlopen("../modules/ssl/libssl.so", RTLD_LAZY | RTLD_LOCAL);

        if (!handle) {
            fprintf(stderr, "%s\n", dlerror());
            exit(EXIT_FAILURE);
        }

        *(void **)(&tmp) = dlsym(handle, "createSslModule");

    }
    if ((error = dlerror()) != NULL)  {
            fprintf(stderr, "%s\n", error);
            exit(EXIT_FAILURE);
    }
#endif

    IModule *pp = getIModuleDLL();
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
    #if(_WIN32)
        FreeLibrary(modules_handles[type]);
    #else
        dlclose(modules_handles[type]);
    #endif
    modules.erase(type);
    modules_handles.erase(type);
}

std::unordered_map<ModuleType, IModule *> Core::getModules() const
{
    return modules;
}

void Core::send(std::any payload, ModuleType sender, ModuleType receiver)
{
    if (modules.find(receiver) == modules.end()) {
        std::cout << "Send failed : module of type "<< receiver <<" not in modules list" << std::endl;
        return;
    }
    modules[receiver]->receive(payload, sender);
}

std::string Core::getHomePath() const
{
    return homePath;
}

void Core::setHomePath(const std::string &path)
{
    homePath = path;
}

void Core::setPhpString(const std::string &payload)
{
    phpString = payload;
}

std::string Core::getPhp() const
{
    return phpString;
}
