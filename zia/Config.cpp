/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Config
*/

#include "Config.hpp"

#include <fstream>

Config::Config()
{
    std::cout << "Config created" << std::endl;
}

Config::~Config()
{

}

void Config::loadConfig(const std::string &path)
{
    std::ifstream ifs(path);

    if (ifs.is_open()) {
        ifs >> m_config;
        std::cout << m_config.dump(4) << std::endl;
        ifs.close();
    }
    else {
        std::cout << "Config file not found" << std::endl;
    }
}

// Lire les modules du fichier config, generer un vector et le renvoyer
std::vector<ModuleType> Config::getModules() const
{
    std::vector<ModuleType> test;
    return test;
}

// Lire la key donnée en parametre et renvoyer sa value
const std::any Config::operator[](const char *key)
{
    return "test";
}

// Verifie si la key existe dans le fichier json
bool Config::validKey(const char *key) const
{
    return true;
}