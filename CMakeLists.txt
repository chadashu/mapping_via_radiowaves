cmake_minimum_required(VERSION 3.10)

# Project Name
project(PersonDemo)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 14)

# Add executable
add_executable(PersonDemo NetEngine/main.cpp
        NetEngine/net_engine_header.h
        NetEngine/preprocessing.cpp
)
include_directories(/usr/local/include/eigen)
