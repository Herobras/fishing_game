cmake_minimum_required(VERSION 3.16)
project(GameDev)

set(CMAKE_CXX_STANDARD 17)

# Usamos vcpkg
find_package(raylib CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(GameDev ${SOURCES})
target_include_directories(GameDev PRIVATE src)
target_link_libraries(GameDev PRIVATE raylib)
