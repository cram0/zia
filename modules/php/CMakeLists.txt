cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${PROJECT_SOURCE_DIR}/lib)
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/lib)
add_library(php SHARED
    PhpCgi.cpp
    ../../Zia/Request.cpp
)
target_link_libraries(php PUBLIC CONAN_PKG::openssl)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
set_target_properties(php PROPERTIES POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})

target_include_directories(php PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(php PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../network)
target_include_directories(php PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../zia-api)
target_include_directories(php PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../Zia)