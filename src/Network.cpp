/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Network
*/

#include "IModule.hpp"

Network::Network(ICore &coreRef)
{
    core = &coreRef;
    type = ModuleType::NETWORK;
}

Network::~Network()
{

}

void Network::run()
{
    
}

ICore *Network::getCore() const
{
    return core;
}

void Network::receive(std::string const &msg)
{

}

bool Network::load()
{
    return true;
}

bool Network::unload()
{
    return true;
}

std::string Network::getName() const
{
    return name;
}

ModuleType Network::getType() const
{
    return type;
}
