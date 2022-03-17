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
    std::cout << "Help.." << std::endl;;
    return (0);
}

int main(int ac, char **av)
{
    if (ac == 2 && av[1][0] == '-' && av[1][1] == 'h') return displayHelp();

    Core core;
    core.loadConfig("config.json");
    bool running = true;

    while (running) {
        std::string command = "";
        std::cout << ">> ";
        std::getline(std::cin, command);
        if (command.compare("update") == 0) {
            core.loadConfig("config.json");
        }
        if (command.compare("exit") == 0) {
            running = false;
        }
    }

    return (0);
}