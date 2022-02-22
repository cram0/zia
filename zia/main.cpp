/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** main
*/

#include "Network.hpp"

int displayHelp()
{
    std::cout << "Help..";
    return (0);
}

int main(int ac, char **av)
{
    if (ac == 2 && av[1][0] == '-' && av[1][1] == 'h') return displayHelp();

    Core core;

    core.registerModule(ModuleType::PHP_CGI);
    core.registerModule(ModuleType::NETWORK);
    Network *net = (Network *)core.getModule(ModuleType::NETWORK);
    if (net != nullptr) {
        net->run();
    }

    return (0);
}