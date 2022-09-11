cmake_minimum_required(VERSION 3.22)
project(Main-Bot)

add_subdirectory(libs/DPP)

add_executable(${PROJECT_NAME}
        main.cpp
        bot.h bot.cpp
        config.h config.cpp
        roles.h roles.cpp
        )

target_link_libraries(${PROJECT_NAME}
        dpp
        )

target_include_directories(${PROJECT_NAME} PRIVATE
        libs/DPP/include
        )

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        )
