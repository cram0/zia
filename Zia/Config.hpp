/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Config
*/

#pragma once

#include "IConfig.hpp"
#include <nlohmann/json.hpp>

#include <regex>

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

static bool isValidIpv4(std::string ip_addr)
{
    std::regex r_ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
    if (std::regex_match(ip_addr, r_ipv4))
        return true;
    return false;
}

static bool isValidPort(std::string port)
{
    std::regex r_port("^((6553[0-5])|(655[0-2][0-9])|(65[0-4][0-9]{2})|(6[0-4][0-9]{3})|([1-5][0-9]{4})|([0-5]{0,5})|([0-9]{1,4}))$");
    if (std::regex_match(port, r_port))
        return true;
    return false;
}