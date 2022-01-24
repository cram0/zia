#pragma once


#include <string>
#include <iostream>

class Zia
{
    public:
            Zia(const std::string &configFile);
            ~Zia();

    private:
            std::string _configFile;
            

};