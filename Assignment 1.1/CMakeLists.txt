cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 23)

project(Assignment1 VERSION 1.1 LANGUAGES CXX)
add_subdirectory(
        ../external_libs
        ${CMAKE_BINARY_DIR}/external_libs
)
add_executable(${PROJECT_NAME}
        circlewithtext.h
        circlewithtext.cpp
        main.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE external_libs)