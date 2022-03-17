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

        /**
         * @brief Loads config file from path
         *
         * @param path
         */
        void loadConfig(const std::string &path);

        /**
         * @brief Get the Modules object list
         *
         * @return std::vector<ModuleType>
         */
        std::vector<ModuleType> getModules() const;

        /**
         * @brief Get value from key given
         *
         * @param key
         * @return const std::any
         */
        const std::any operator[](const char *key);

        /**
         * @brief Checks if key is valid in config file
         *
         * @param key
         * @return true
         * @return false
         */
        bool validKey(const char *key) const;

        bool isValid(const json &config) const;
        bool isGoodModule(const std::string &param) const;

    private:
        json m_config;
};

/**
 * @brief Checks if address is valid IPV4 format
 *
 * @param ip_addr
 * @return true
 * @return false
 */
static bool isValidIpv4(std::string ip_addr)
{
    std::regex r_ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
    if (std::regex_match(ip_addr, r_ipv4))
        return true;
    return false;
}

/**
 * @brief Checks if valid port format
 *
 * @param port
 * @return true
 * @return false
 */
static bool isValidPort(std::string port)
{
    std::regex r_port("^((6553[0-5])|(655[0-2][0-9])|(65[0-4][0-9]{2})|(6[0-4][0-9]{3})|([1-5][0-9]{4})|([0-5]{0,5})|([0-9]{1,4}))$");
    if (std::regex_match(port, r_port))
        return true;
    return false;
}

static std::vector<std::string> configModuleType = {
    "SSL",
    "PhpCgi",
    "Network"
};