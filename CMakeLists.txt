cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 23)

project(balls)
add_subdirectory(external_libs)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE external_libs)