cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG    ${PROJECT_SOURCE_DIR})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${PROJECT_SOURCE_DIR})
add_executable(zia
    main.cpp
    Core.cpp
    Config.cpp
)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

target_link_libraries(zia PRIVATE Threads::Threads)
target_link_libraries(zia PRIVATE ${CMAKE_DL_LIBS})
target_link_libraries(zia PRIVATE CONAN_PKG::nlohmann_json)

target_include_directories(zia PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(zia PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../zia-api)
target_include_directories(zia PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../modules/network)
target_include_directories(zia PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../modules/php)
target_include_directories(zia PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../modules/ssl)