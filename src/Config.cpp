/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Config
*/

#include "Config.hpp"

Config::Config()
{

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
