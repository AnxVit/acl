cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(PROJECT_NAME DB)

project(${PROJECT_NAME})

add_library(connect STATIC Connection.cpp)
add_library(pgback STATIC pgback.cpp)

target_link_libraries(pgback connect)