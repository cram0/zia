/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Core
*/

#include "ICore.hpp"

#ifndef CORE_HPP_
#define CORE_HPP_

class Core : public ICore {
    private:
        std::unordered_map<ModuleType, IModule *> modules;
        std::unordered_map<ModuleType, void *> modules_handles;
        IConfig* config;
    public:

        Core();
        ~Core();
        void loadConfig(std::string const &path);
        void listModules() const;
        IConfig *getConfig() const;
        IModule *getModule(ModuleType type) const;
        void registerModule(ModuleType type);
        void unregisterModule(ModuleType type);
        std::unordered_map<ModuleType, IModule *> getModules() const;
        void send(std::any payload, ModuleType type);
};

#endif /* !CORE_HPP_ */
