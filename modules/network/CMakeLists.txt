cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${PROJECT_SOURCE_DIR}/lib)
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/lib)
add_library(network SHARED
Network.cpp
../../Zia/Request.cpp
)
find_package(Threads REQUIRED)
target_link_libraries(network PRIVATE Threads::Threads)
target_link_libraries(network PUBLIC CONAN_PKG::openssl)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
set_target_properties(network PROPERTIES POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})


target_include_directories(network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../zia-api)
target_include_directories(network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../Zia)