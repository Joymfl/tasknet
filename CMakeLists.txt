cmake_minimum_required(VERSION 3.5)

project(tasknet VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE TASKNET_SOURCES
        CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

add_executable(tasknet WIN32 ${TASKNET_SOURCES})

target_include_directories(tasknet PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

if (WIN32)
    target_link_libraries(tasknet PRIVATE user32 gdi32 dwmapi)
endif ()