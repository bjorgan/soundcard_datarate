cmake_minimum_required(VERSION 2.8.11)
project(qaudioinput_sampler)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Multimedia REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(qaudioinput_sampler main.cpp audiosink.cpp)
qt5_use_modules(qaudioinput_sampler Core Multimedia)
