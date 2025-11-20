cmake_minimum_required(VERSION 3.5)

project(tasknet VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(taskent WIN32 src/main.cpp)

if (WIN32)
    target_link_libraries(taskent PRIVATE user32 gdi32)
endif()