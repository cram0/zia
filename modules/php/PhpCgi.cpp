/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** PhpCgi
*/

#include "PhpCgi.hpp"
#include "Request.hpp"

#if(_WIN32)
#include <io.h>
#else
#include <unistd.h>
#endif

#include <cstdio>
#include <fcntl.h>
#include <cstring>

#include <sstream>

PhpCgi::PhpCgi() {
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

void PhpCgi::receive(std::any payload, ModuleType sender)
{
    Request request = std::any_cast<Request>(payload);
    std::string f_data;
    size_t pread_size = 0;
    const short CHUNK_SIZE = 4096;
    char buf[CHUNK_SIZE] = {0};

    FILE *f;

#if(_WIN32)
    f = _popen(std::string("php-cgi " + request.getFilePath()).c_str(), "r");
#else
    f = popen(std::string("php-cgi " + request.getFilePath()).c_str(), "r");
#endif

    pread_size = fread(buf, 1, CHUNK_SIZE, f);
    f_data += buf;

    while (pread_size == CHUNK_SIZE) {
        memset(buf, 0, CHUNK_SIZE);
        pread_size = fread(buf, 1, CHUNK_SIZE, f);
        f_data += buf;
    }

#if(_WIN32)
    _pclose(f);
#else
    pclose(f);
#endif

    request.setData(f_data);
    if (request.getSsl() == nullptr)
        getCore()->send(request, ModuleType::PHP_CGI, ModuleType::NETWORK);
    else
        getCore()->send(request, ModuleType::PHP_CGI, ModuleType::SSL_MODULE);
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