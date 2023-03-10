/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Request
*/

#ifndef REQUEST_HPP_
#define REQUEST_HPP_

#include <string>
#if(_WIN32)
#include <WinSock2.h>
#else
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#endif
#include <unordered_map>
#include <algorithm>

#include <openssl/ssl.h>

class Request {
    public:
public:
#if(_WIN32)
            Request(SOCKET socket, const std::string &file_path, SSL *ssl);
       #else
            Request(int socket, const std::string &file_path, SSL *ssl);
       #endif

        /**
         * @brief Get the File Path
         *
         * @return const std::string
         */
        [[nodiscard]] const std::string getFilePath() const;

        /**
         * @brief Set the File Path
         *
         * @param file_path
         */
        void setFilePath(const std::string &file_path);

        /**
         * @brief Get the Data
         *
         * @return const std::string
         */
        [[nodiscard]] const std::string getData() const;

        /**
         * @brief Set the Data to the request
         *
         * @param data
         */
        void setData(const std::string &data);

#if(_WIN32)
        /**
         * @brief Get the Socket fd
         *
         * @return const SOCKET
         */
        [[nodiscard]] const SOCKET getSocket() const;
#else
        /**
         * @brief Get the Socket fd
         *
         * @return const int
         */
        const int getSocket() const;
#endif
        /**
         * @brief Set the Socket fd
         *
         * @param socket
         */
        void setSocket(int socket);

        /**
         * @brief Get the Ssl object
         *
         * @return SSL*
         */
        [[nodiscard]] SSL *getSsl() const;

        /**
         * @brief Set the Ssl object
         *
         * @param ssl
         */
        void setSsl(SSL *ssl);
        ~Request();

    protected:
    private:
        std::string m_data;
        std::string m_file_path;
        bool m_file_valid{};
#if(_WIN32)
        SOCKET m_socket;
#else
        int m_socket;
#endif
        SSL* m_ssl = nullptr;
};

/**
 * @brief Contains all the MIME-type files
 *
 */
static std::unordered_map<std::string, std::string> contentTypeMap = {
    {".aac", "audio/aac"},
    {".abw", "application/x-abiword"},
    {".arc", "application/octet-stream"},
    {".avi", "video/x-msvideo"},
    {".azw", "application/vnd.amazon.ebook"},
    {".bin", "application/octet-stream"},
    {".bmp", "image/bmp"},
    {".bz", "application/x-bzip"},
    {".bz2", "application/x-bzip2"},
    {".csh", "application/x-csh"},
    {".css", "text/css"},
    {".csv", "text/csv"},
    {".doc", "application/msword"},
    {".docx", "application/vnd.openxmlformats-officedocument.wordprocessingml.document"},
    {".eot", "application/vnd.ms-fontobject"},
    {".epub", "application/epub+zip"},
    {".gif", "image/gif"},
    {".htm", "text/html"},
    {".html", "text/html"},
    {".ico", "image/x-icon"},
    {".ics", "text/calendar"},
    {".jar", "application/java-archive"},
    {".jpeg", "image/jpeg"},
    {".jpg", "image/jpeg"},
    {".js", "application/javascript"},
    {".json", "application/json"},
    {".mid", "audio/midi"},
    {".midi", "audio/midi"},
    {".mpeg", "video/mpeg"},
    {".mpkg", "application/vnd.apple.installer+xml"},
    {".odp", "application/vnd.oasis.opendocument.presentation"},
    {".ods", "application/vnd.oasis.opendocument.spreadsheet"},
    {".odt", "application/vnd.oasis.opendocument.text"},
    {".oga", "audio/ogg"},
    {".ogv", "video/ogg"},
    {".ogx", "application/ogg"},
    {".otf", "font/otf"},
    {".png", "image/png"},
    {".pdf", "application/pdf"},
    {".ppt", "application/vnd.ms-powerpoint"},
    {".pptx", "application/vnd.openxmlformats-officedocument.presentationml.presentation"},
    {".rar", "application/x-rar-compressed"},
    {".rtf", "application/rtf"},
    {".sh", "application/x-sh"},
    {".svg", "image/svg+xml"},
    {".swf", "application/x-shockwave-flash"},
    {".tar", "application/x-tar"},
    {".tif", "image/tiff"},
    {".tiff", "image/tiff"},
    {".ts", "application/typescript"},
    {".ttf", "font/ttf"},
    {".vsd", "application/vnd.visio"},
    {".wav", "audio/x-wav"},
    {".weba", "audio/webm"},
    {".webm", "video/webm"},
    {".webp", "image/webp"},
    {".woff", "font/woff"},
    {".woff2", "font/woff2"},
    {".xhtml", "application/xhtml+xml"},
    {".xls", "application/vnd.ms-excel"},
    {".xlsx", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"},
    {".xml", "application/xml"},
    {".xul", "application/vnd.mozilla.xul+xml"},
    {".zip", "application/zip"},
    {".3gp", "video/3gpp"},
    {".7z", "application/x-7z-compressed"}
};

/**
 * @brief Contains all the requests method types
 *
 */
static std::vector<std::string> methodTypes = {
    {"GET"},
    {"HEAD"},
    {"POST"},
    {"PUT"},
    {"DELETE"},
    {"CONNECT"},
    {"OPTIONS"},
    {"TRACE"},
    {"PATCH"}
};

/**
 * @brief Get the Content Type
 *
 * @param file_extension
 * @return const std::string
 */
static const std::string getContentType(const std::string &file_extension)
{
    return (contentTypeMap[file_extension]);
}

/**
 * @brief Checks if method is valid
 *
 * @param method
 * @return true
 * @return false
 */
static bool isValidMethod(const std::string &method)
{
    if (std::find(methodTypes.begin(), methodTypes.end(), method) != methodTypes.end()) {
        return true;
    }
    return false;
}

/**
 * @brief Checks if HTTP version is valid for the project
 *
 * @param version
 * @return true
 * @return false
 */
static bool isValidHttpVersion(const std::string &version)
{
    if (version == "HTTP/1.1") {
        return true;
    }
    return false;
}

static const short CHUNK_SIZE = 4096;

#endif /* !REQUEST_HPP_ */
