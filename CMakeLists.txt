cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(PROJECT_NAME ACL)

project(${PROJECT_NAME})

set(LIBRARY_DIR Test/)

add_library(test ${LIBRARY_DIR}test.cpp)
add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${LIBRARY_DIR})
target_link_libraries(${PROJECT_NAME} test)