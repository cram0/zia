/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Config
*/

#pragma once

#include "IConfig.hpp"
#include <json.hpp>

// SO THAT WE DONT WASTE 20 FUCKING COLUMNS BECAUSE THE NAMESPACE IS WAY TOO LONG
using json = nlohmann::json;

class Config : public IConfig {
    public:
        Config();
        ~Config();
        void loadConfig(const std::string &path);
        std::vector<ModuleType> getModules() const;
        const std::any operator[](const char *key);
        bool validKey(const char *key) const;

    private:
        json m_config;
};
