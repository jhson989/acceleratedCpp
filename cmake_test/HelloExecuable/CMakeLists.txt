# CMake bianry version
cmake_minimum_required(VERSION 3.10)

# Proejct info
project(
    HelloCMake
    VERSION 0.1
    DESCRIPTION "Hello CMake example"
    LANGUAGES CXX
)


add_executable (JHSON main.cpp runable.cpp)


target_compile_options(JHSON PUBLIC -O3)

target_include_directories(JHSON PUBLIC ${CMAKE_SOURCE_DIR}/includes)