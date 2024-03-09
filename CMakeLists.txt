cmake_minimum_required(VERSION 3.27)
project(imgproc CPP)

add_executable(imgproc main.cpp)
target_include_directories(imgproc PRIVATE raylib/include)
target_link_libraries(imgproc PRIVATE
        ${CMAKE_SOURCE_DIR}/raylib/lib/raylib.lib
        winmm.lib)
