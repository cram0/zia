/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Network
*/

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#if(_WIN32)
#include <WinSock2.h>
#endif

#include "IModule.hpp"

class ICore;

class Network : public IModule {
    private:
        ICore *core;
        std::string name;
        ModuleType type;
   public:
        Network();
        Network(ICore &coreRef);
        ~Network();
        ICore *getCore() const;
        void setCore(ICore &coreRef);
        void init();
        const std::string getContentType(const std::string &file_extension);
        void sslRequestCallback(std::string request);
        void receive(std::any payload, ModuleType sender);
        bool load(std::any payload);
        bool unload();
        std::string getName() const;
        ModuleType getType() const;

    [[noreturn]] void run();
#if(_WIN32)
        void processRequest(SOCKET s_conn);
#else
        void processRequest(int s_conn);
#endif
};

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

static const short CHUNK_SIZE = 4096;

#endif /* !NETWORK_HPP_ */
