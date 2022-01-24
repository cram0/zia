/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** main
*/

#include "Zia.hpp"

int displayHelp()
{
    std::cout << "Help..";
    return (0);
}

int main(int ac, char **av)
{
    if (ac == 1 && av[1][0] == '-' && av[1][1] == 'h') return displayHelp();
    Zia zia(ac == 1 ? "./config.json" : av[1]);
    zia.configFileLoad();

    return (0);
}