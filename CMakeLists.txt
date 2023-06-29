cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(PROJECT_NAME ACL)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} pthread)