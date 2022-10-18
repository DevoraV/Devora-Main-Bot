cmake_minimum_required(VERSION 3.22)
project(Main-Bot)

add_subdirectory(libs/DPP)

add_executable(${PROJECT_NAME}
        main.cpp
        bot.h bot.cpp
        config.h config.cpp
        roles.h roles.cpp
        )

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME}
        dpp
        ${CMAKE_THREAD_LIBS_INIT}
        )

target_include_directories(${PROJECT_NAME} PRIVATE
        libs/DPP/include
        )

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        )
