/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Core
*/

#include "ICore.hpp"

#pragma once

#if(_WIN32)
#define _WINSOCKAPI_    // stops windows.h including winsock.h
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

class Core : public ICore {
    private:
        std::unordered_map<ModuleType, IModule *> modules;
#if(_WIN32)
        std::unordered_map<ModuleType, HINSTANCE> modules_handles;
#else
        std::unordered_map<ModuleType, void *> modules_handles;
#endif
        IConfig *config = nullptr;
        std::string homePath;
        std::string phpString;
    public:

        Core();
        ~Core();
        void loadConfig(std::string const &path);
        void listModules() const;
        IConfig *getConfig() const;
        IModule *getModule(ModuleType type) const;
        void updateModule(const ModuleType &cm);
        void loadModulesFromConf(const std::vector<ModuleType> &confModules);
        void registerModule(ModuleType type);
        void unregisterModule(ModuleType type);
        std::unordered_map<ModuleType, IModule *> getModules() const;
        void send(std::any payload, ModuleType type, ModuleType receiver);
        std::string getHomePath() const;
        void setHomePath(const std::string &path);
        void setPhpString(const std::string &payload);
        std::string getPhp() const;
};