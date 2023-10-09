cmake_minimum_required(VERSION 3.16.3)

project(error)

add_executable(error 
    main.cpp
)

set_target_properties(error PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

