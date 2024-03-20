cmake_minimum_required(VERSION 3.16)

project(cramkap)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(${PROJECT_NAME}_SOURCES
src/Server.c
src/Client.c
src/Game.c
src/Player.c
src/main.js.php.cpp.c
)

set(${PROJECT_NAME}_INCLUDE
include/
)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_INCLUDE})

include(Vendor.cmake)