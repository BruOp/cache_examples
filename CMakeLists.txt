cmake_minimum_required( VERSION 3.1 )
project(cache_example VERSION 0.1
        DESCRIPTION "Experiments in CPU cache performance"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(naive_simple)
