/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Ssl
*/

#include "Ssl.hpp"

Ssl::Ssl()
{
    type = ModuleType::PHP_CGI;
    name = "SslName";
    std::cout << "Ssl created" << std::endl;
}

Ssl::Ssl(ICore &coreRef) : Ssl()
{
    core = &coreRef;
}

Ssl::~Ssl()
{

}

void Ssl::setCore(ICore &coreRef)
{
    core = &coreRef;
}

ICore *Ssl::getCore() const
{
    return core;
}

void Ssl::receive(std::any payload)
{

}

bool Ssl::load()
{
    return true;
}

bool Ssl::unload()
{
    return true;
}

std::string Ssl::getName() const
{
    return name;
}

ModuleType Ssl::getType() const
{
    return type;
}
