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

    if (m_config.find("Network") != m_config.end())
        test.emplace_back(ModuleType::NETWORK);
    if (m_config.find("PhpCgi") != m_config.end())
        test.emplace_back(ModuleType::PHP_CGI);
    if (m_config.find("SSL") != m_config.end())
        test.emplace_back(ModuleType::SSL_MODULE);

    return test;
}


// Lire la key donnée en parametre et renvoyer sa value
const std::any Config::operator[](const char *key)
{
    if (validKey(key))
        return json::()
    return nullptr;
}

// Verifie si la key existe dans le fichier json
bool Config::validKey(const char *key) const
{
    if (m_config.find(key) == m_config.end())
        return false;
    return true;
}