cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME ACL)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(DB)

target_include_directories(${PROJECT_NAME} PUBLIC DB)

target_link_libraries(${PROJECT_NAME} pq pthread pgback)