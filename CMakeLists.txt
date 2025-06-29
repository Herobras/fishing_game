cmake_minimum_required(VERSION 3.16)
project(GameDev)

set(CMAKE_CXX_STANDARD 17)

# Usamos vcpkg
find_package(raylib CONFIG REQUIRED)

add_executable(GameDev src/main.cpp)
target_link_libraries(GameDev PRIVATE raylib)
