/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Request
*/

#ifndef REQUEST_HPP_
#define REQUEST_HPP_

#include <string>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>

class Request {
    public:
        Request();
        Request(int socket, const std::string &file_path);

        const std::string getFilePath() const;
        void setFilePath(const std::string &file_path);

        const std::string getData() const;
        void setData(const std::string &data);

        const int getSocket() const;
        void setSocket(int socket);
        ~Request();

    protected:
    private:
        std::string m_data;
        std::string m_file_path;
        bool m_file_valid;
        int m_socket;
};

#endif /* !REQUEST_HPP_ */
