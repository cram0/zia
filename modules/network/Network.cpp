/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Network
*/

#include "INetwork.hpp"
#include "ICore.hpp"

#include <sys/socket.h>

Network::Network(ICore &coreRef)
{
    core = &coreRef;
    type = ModuleType::NETWORK;
    name = "test";
    std::cout << "Network created" << std::endl;

    
}

Network::~Network()
{

}

void Network::run()
{
    std::cout << "Network Loaded" << std::endl;
}

ICore *Network::getCore() const
{
    return core;
}

void Network::receive(std::any payload)
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

extern "C" Network *getNetworkModule(ICore &coreRef) {
    return (new Network(coreRef));
}