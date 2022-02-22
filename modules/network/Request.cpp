/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Request
*/

#include "Request.hpp"

#include <iostream>

Request::Request()
{

}

Request::Request(int socket, const std::string &file_path)
{
    m_socket = socket;
    m_file_path = file_path;
}

const std::string Request::getFilePath() const
{
    return m_file_path;
}

void Request::setFilePath(const std::string &file_path)
{
    m_file_path = file_path;
}

const std::string Request::getData() const
{
    return m_data;
}

void Request::setData(const std::string &data)
{
    m_data = data;
}

const int Request::getSocket() const
{
    return m_socket;
}

void Request::setSocket(int socket)
{
    m_socket = socket;
}

Request::~Request()
{

}
