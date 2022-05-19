cmake_minimum_required(VERSION 3.16)
project(check_setup)                                    # <.>

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cpp board.cpp)     # <.>

