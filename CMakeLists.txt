cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
if (UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lpthread")
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(zia VERSION 1.0)

add_executable(zia
    src/main.cpp
    src/Core.cpp
    src/Config.cpp
    src/Network.cpp
)

target_include_directories(zia PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(zia PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/zia-api)

# Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)
