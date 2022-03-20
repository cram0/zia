/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Request
*/

#include "Request.hpp"

#include <iostream>

#if(_WIN32)

Request::Request(SOCKET socket, const std::string &file_path, SSL *ssl)
#else
Request::Request(int socket, const std::string &file_path, SSL *ssl)
#endif
{
    m_socket = socket;
    m_file_path = file_path;
    m_ssl = ssl;
}

const std::string Request::getFilePath() const {
    return m_file_path;
}

void Request::setFilePath(const std::string &file_path) {
    m_file_path = file_path;
}

const std::string Request::getData() const {
    return m_data;
}

void Request::setData(const std::string &data) {
    m_data = data;
}

#if(_WIN32)

const SOCKET Request::getSocket() const
#else
const int Request::getSocket() const
#endif
{
    return m_socket;
}

void Request::setSocket(int socket) {
    m_socket = socket;
}

SSL *Request::getSsl() const {
    return m_ssl;
}

void Request::setSsl(SSL *ssl) {
    m_ssl = ssl;
}

Request::~Request() = default;
