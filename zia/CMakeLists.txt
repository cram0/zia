cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
if (UNIX)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lpthread")
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(zia VERSION 1.0)

add_executable(zia
    main.cpp
    Core.cpp
    Config.cpp
)

target_link_libraries(zia PUBLIC network)
target_link_libraries(zia PUBLIC ssl)

target_include_directories(zia PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(zia PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../zia-api)
target_include_directories(zia PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../modules/network)
target_include_directories(zia PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../modules/php)
target_include_directories(zia PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../modules/ssl)
target_include_directories(zia PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../lib)