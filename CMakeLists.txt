cmake_minimum_required(VERSION 3.16)
project(GameDev)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Incluye todos los .cpp en src y subdirectorios
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

# Crea el ejecutable
add_executable(GameDev ${SOURCES})

# Agrega los directorios de include
target_include_directories(GameDev PRIVATE src)

# Linkea raylib desde vcpkg
find_package(raylib CONFIG REQUIRED)
target_link_libraries(GameDev PRIVATE raylib)
