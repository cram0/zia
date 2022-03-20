/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Config
*/

#include "Config.hpp"

#include <fstream>

Config::Config() {
    std::cout << "Config created" << std::endl;
}

Config::~Config() = default;

bool Config::isGoodModule(const std::string &param) {
    bool valid = false;
    for (const auto &type: configModuleType) {
        if (param == type) {
            valid = true;
        }
    }
    return valid;
}

bool Config::isValid(const json &config) {
    return std::any_of(config.items().begin(), config.items().end(),
                       [](const auto &module) { return isGoodModule(module.key()); });
}

void Config::loadConfig(const std::string &path) {
    std::ifstream ifs(path);
    json temp;

    if (ifs.is_open()) {
        try {
            temp = json::parse(ifs);
        }
        catch (json::parse_error &e) {
            std::cout << "Not a valid config file" << std::endl;
            std::cout << e.what() << std::endl;
            ifs.close();
            return;
        }

        if (isValid(temp)) {
            m_config = temp;
        }

        ifs.close();
    } else {
        std::cout << "Config file not found" << std::endl;
        m_config = nullptr;
    }
}

// Lire les modules du fichier config, generer un vector et le renvoyer
std::vector<ModuleType> Config::getModules() const {
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
const std::any Config::operator[](const char *key) {
    if (validKey(key))
        return m_config[key].get<std::unordered_map<std::string, json>>();
    return nullptr;
}

// Verifie si la key existe dans le fichier json
bool Config::validKey(const char *key) const {
    if (m_config.find(key) == m_config.end())
        return false;
    return true;
}