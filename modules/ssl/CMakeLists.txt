cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${PROJECT_SOURCE_DIR}/lib)
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/lib)
add_library(ssl SHARED
    Ssl.cpp
    ../../Zia/Request.cpp
)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(ssl PRIVATE Threads::Threads)
target_link_libraries(ssl PUBLIC CONAN_PKG::openssl)
target_link_libraries(ssl PUBLIC CONAN_PKG::nlohmann_json)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
set_target_properties(ssl PROPERTIES POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})

target_include_directories(ssl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ssl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../network)
target_include_directories(ssl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../zia-api)
target_include_directories(ssl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../Zia)