/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** PhpCgi
*/

#include "PhpCgi.hpp"
#include "Request.hpp"

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#include <sstream>

PhpCgi::PhpCgi()
{
    type = ModuleType::PHP_CGI;
    name = "PhpCgiName";
    std::cout << "PhpCgi created" << std::endl;
}

PhpCgi::PhpCgi(ICore &coreRef) : PhpCgi()
{
    core = &coreRef;
}

PhpCgi::~PhpCgi()
{

}

ICore *PhpCgi::getCore() const
{
    return core;
}

void PhpCgi::setCore(ICore &coreRef)
{
    core = &coreRef;
}

void PhpCgi::receive(std::any payload)
{
    Request request = std::any_cast<Request>(payload);
    std::string f_data;
    ssize_t pread_size = 0;
    int CHUNK_SIZE = 4096;
    char buf[CHUNK_SIZE] = {0};

    FILE *f;
    f = popen(std::string("php-cgi " + request.getFilePath()).c_str(), "r");
    pread_size = fread(buf, 1, CHUNK_SIZE, f);
    f_data += buf;

    while (pread_size == CHUNK_SIZE) {
        memset(buf, 0, CHUNK_SIZE);
        pread_size = fread(buf, 1, CHUNK_SIZE, f);
        f_data += buf;
    }

    pclose(f);
    request.setData(f_data);
    if (request.getSsl() == nullptr)
        getCore()->send(request, ModuleType::NETWORK);
    else
        getCore()->send(request, ModuleType::SSL_MODULE);
}

bool PhpCgi::load(std::any payload)
{
    return true;
}

bool PhpCgi::unload()
{
    return true;
}

std::string PhpCgi::getName() const
{
    return name;
}

ModuleType PhpCgi::getType() const
{
    return type;
}

extern "C" PhpCgi *createPhpCgiModule() {
    return (new PhpCgi());
}