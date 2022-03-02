/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Config
*/

#include "Config.hpp"

Config::Config()
{
    initBasicConfig();
}

Config::~Config()
{

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

void Config::initBasicConfig()
{
    std::ifstream ifs("../../config.json");

    if (ifs.is_open()) {
        json jf = json::parse(ifs);
        std::cout << std::setw(4) << jf << "\n\n";
        std::cout << "Config fileeeeeee" << std::endl;
    } else {
        std::cout << "Config file not found" << std::endl;
    }

}

void Config::displayBasicConfig() const
{
    std::cout << _basicConfig << std::endl;
}

void Config::displayCurrentConfig() const
{
    std::cout << _config.dump(4) << std::endl;
}