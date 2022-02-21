/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** main
*/

#include "ICore.hpp"

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
    IModule *mod = core.getModule(ModuleType::NETWORK);
    INetwork *pp = (INetwork *)mod;
    if (pp != nullptr) {
        std::cout << "Before run" << std::endl;
        pp->run();
        std::cout << "After run" << std::endl;
    }

    return (0);
}