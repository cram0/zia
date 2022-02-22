/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Network
*/

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

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
        void receive(std::any payload);
        bool load();
        bool unload();
        std::string getName() const;
        ModuleType getType() const;
        void run();
        void processRequest(int s_conn);
};

static std::unordered_map<std::string, std::string> contentTypeMap = {
    {".txt", "text/plain"},
    {".txt", "text/plain"},
    {".html", "text/html"},
    {".php", "text/html"},
    {".css", "text/css"},
    {".js", "application/javascript"},
    {".json", "application/json"},
    {".pdf", "application/pdf"},
    {".jpg", "image/jpeg"},
    {".jpeg", "image/jpeg"},
    {".png", "image/png"}
};

static size_t CHUNK_SIZE = 4096;

#endif /* !NETWORK_HPP_ */
