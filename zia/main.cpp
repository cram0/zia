/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** main
*/

#include "Core.hpp"
#include "Config.hpp"

#include <thread>

int displayHelp()
{
    std::cout << "Help..";
    return (0);
}

int main(int ac, char **av)
{
    if (ac == 2 && av[1][0] == '-' && av[1][1] == 'h') return displayHelp();

    Core core;

    core.loadConfig("../../config.json");

    core.registerModule(ModuleType::PHP_CGI);
    core.registerModule(ModuleType::NETWORK);
    core.registerModule(ModuleType::SSL_MODULE);

    char c;
    std::cin >> c;

    return (0);
}