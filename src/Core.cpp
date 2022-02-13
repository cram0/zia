/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Core
*/

#include "ICore.hpp"

Core::Core()
{

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
