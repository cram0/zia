/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Config
*/

#pragma once

#include "IConfig.hpp"
#include <json.hpp>

//for convinience
using json = nlohmann::json;

class Config : public IConfig {
    public:
        Config();
        ~Config();
        std::vector<ModuleType> getModules() const;
        const std::any operator[](const char *key);
        bool validKey(const char *key) const;
        void displayBasicConfig() const;
        void displayCurrentConfig() const;

    private:
        void initBasicConfig();
        json _config;
        json _basicConfig;
};
