/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** Zia
*/

#pragma once


#include <string>
#include <iostream>

class Zia
{

    // Constructors and Destructors only
    public:
            Zia(const std::string &configFile);
            ~Zia();

    // Public methods
    public:
            void configFileLoad();

    // Private variables
    private:
            std::string _configFile;
            

};