cmake_minimum_required(VERSION 3.16)

project(cramkap)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE src/main.js.php.cpp.c)

include(Vendor.cmake)
