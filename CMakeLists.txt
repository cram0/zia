cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
if (UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lpthread")
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(zia VERSION 1.0)

add_subdirectory(zia)
add_subdirectory(modules/network)
add_subdirectory(modules/php)
add_subdirectory(modules/ssl)