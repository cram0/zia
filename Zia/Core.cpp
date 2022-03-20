/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Core
*/

#include "Core.hpp"
#include "Config.hpp"

typedef IModule *(*IModuleDLL)(ICore &coreRef);

Core::Core() {
    std::cout << "Core created" << std::endl;

    if (config == nullptr) {
        config = new Config;
    }
}

Core::~Core() {
    if (config != nullptr) {
        delete config;
    }
}

void Core::updateModule(const ModuleType &cm) {
    unregisterModule(cm);
    registerModule(cm);
}

void Core::loadModulesFromConf(const std::vector<ModuleType> &confModules) {
    for (const ModuleType &cm: confModules) {
        if (modules.find(cm) == modules.end()) {
            registerModule(cm);
        } else {
            updateModule(cm);
        }
    }
}

void Core::loadConfig(std::string const &path) {
    auto *config = (Config *) getConfig();
    config->loadConfig(path);
    loadModulesFromConf(config->getModules());
}

void Core::listModules() const {

}

IConfig *Core::getConfig() const {
    return (this->config);
}

IModule *Core::getModule(ModuleType type) const {
    if (modules.find(type) == modules.end()) {
        return nullptr;
    }
    return modules.at(type);
}

void Core::registerModule(ModuleType type) {
    IModuleDLL getIModuleDLL = nullptr;

#if(_WIN32)
    HINSTANCE handle;
    if (type == ModuleType::NETWORK) {
        handle = LoadLibrary("lib/network.dll");

        if (handle == nullptr) {
            std::cout << "unable to load: " << "network.dll" << " lib" << std::endl;
            exit(EXIT_FAILURE);
        }
        getIModuleDLL = (IModuleDLL) GetProcAddress(handle, "createNetworkModule");
        if (getIModuleDLL == nullptr) {
            std::cout << "cant get func 'createNetworkModule'" << std::endl;
            FreeLibrary(handle);
            exit(EXIT_FAILURE);
        }
    }
    if (type == ModuleType::PHP_CGI) {
        handle = LoadLibrary("lib/php.dll");

        if (handle == nullptr) {
            std::cout << "unable to load: " << "php.dll" << " lib" << std::endl;
            exit(EXIT_FAILURE);
        }
        getIModuleDLL = (IModuleDLL) GetProcAddress(handle, "createPhpCgiModule");
        if (getIModuleDLL == nullptr) {
            std::cout << "cant get func 'createPhpCgiModule'" << std::endl;
            FreeLibrary(handle);
            exit(EXIT_FAILURE);
        }
    }
    if (type == ModuleType::SSL_MODULE) {
        handle = LoadLibrary("lib/ssl.dll");

        if (handle == nullptr) {
            std::cout << "unable to load: " << "ssl.dll" << " lib" << std::endl;
            exit(EXIT_FAILURE);
        }
        getIModuleDLL = (IModuleDLL) GetProcAddress(handle, "createSslModule");
        if (getIModuleDLL == nullptr) {
            std::cout << "cant get func 'createSslModule'" << std::endl;
            FreeLibrary(handle);
            exit(EXIT_FAILURE);
        }
    }
#else
    void *handle = nullptr;
    if (type == ModuleType::NETWORK) {
        handle = dlopen("lib/libnetwork.so", RTLD_LAZY | RTLD_LOCAL);

        if (!handle) {
            fprintf(stderr, "%s\n", dlerror());
            exit(EXIT_FAILURE);
        }

       getIModuleDLL = (IModuleDLL)dlsym(handle, "createNetworkModule");
    }
    if (type == ModuleType::PHP_CGI) {
        handle = dlopen("lib/libphp.so", RTLD_LAZY | RTLD_LOCAL);

        if (!handle) {
            fprintf(stderr, "%s\n", dlerror());
            exit(EXIT_FAILURE);
        }

       getIModuleDLL = (IModuleDLL)dlsym(handle, "createPhpCgiModule");
    }
    if (type == ModuleType::SSL_MODULE) {
        handle = dlopen("lib/libssl.so", RTLD_LAZY | RTLD_LOCAL);

        if (!handle) {
            fprintf(stderr, "%s\n", dlerror());
            exit(EXIT_FAILURE);
        }

       getIModuleDLL = (IModuleDLL)dlsym(handle, "createSslModule");

    }
#endif

    IModule *pp = getIModuleDLL(*this);

    modules.emplace(std::make_pair(type, pp));
    modules_handles.emplace(std::make_pair(type, handle));
}

void Core::unregisterModule(ModuleType type) {
    if (modules.find(type) == modules.end()) {
        std::cout << "Unregistering module of type " << type << " failed, probably not in the list or already removed"
                  << std::endl;
        return;
    }
    modules[type]->unload();
    // delete modules[type];
#if(_WIN32)
    FreeLibrary(modules_handles[type]);
#else
    dlclose(modules_handles[type]);
#endif
    modules.erase(type);
    modules_handles.erase(type);
    std::cout << "Succesfully deleted module of type " << type << std::endl;
}

std::unordered_map<ModuleType, IModule *> Core::getModules() const {
    return modules;
}

void Core::send(std::any payload, ModuleType sender, ModuleType receiver) {
    if (modules.find(receiver) == modules.end()) {
        std::cout << "Send failed : module of type " << receiver << " not in modules list" << std::endl;
        return;
    }
    modules[receiver]->receive(payload, sender);
}

std::string Core::getHomePath() const {
    return homePath;
}

void Core::setHomePath(const std::string &path) {
    homePath = path;
}

void Core::setPhpString(const std::string &payload) {
    phpString = payload;
}

std::string Core::getPhp() const {
    return phpString;
}
