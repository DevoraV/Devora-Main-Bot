cmake_minimum_required(VERSION 3.22)
project(Main-Bot)

add_subdirectory(libs/DPP)
add_subdirectory(libs/SQLiteCpp)
add_subdirectory(libs/curlpp-0.8.1)

add_executable(${PROJECT_NAME}
        main.cpp
        bot.h bot.cpp
        config.h config.cpp
        roles.h roles.cpp
        )

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

#find_package (sqlite3)
#if (SQLITE3_FOUND)
#    include_directories(${SQLITE3_INCLUDE_DIRS})
#    target_link_libraries (Main-Bot ${SQLITE3_LIBRARIES})
#endif (SQLITE3_FOUND)


target_link_libraries(${PROJECT_NAME}
        dpp
        SQLiteCpp
        curlpp
        sqlite3
        ${CMAKE_THREAD_LIBS_INIT}
        )

target_include_directories(${PROJECT_NAME} PRIVATE
        libs/DPP/include
        libs/SQLiteCpp/include
        libs/curlpp-0.8.1/include
        )

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        )
