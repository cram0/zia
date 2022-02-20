cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
if (UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lpthread")
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(php VERSION 1.0)

add_library(php SHARED
    PhpCgi.cpp
)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

set_target_properties(php PROPERTIES POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})
# set_target_properties(php PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(php PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(php PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../zia-api)