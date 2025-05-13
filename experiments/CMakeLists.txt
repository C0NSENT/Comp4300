cmake_minimum_required(VERSION 3.30)
project(Text_centering)

set(CMAKE_CXX_STANDARD 23)

# Добавляем поддиректорию с явным указанием бинарной директории
add_subdirectory(
        ../external_libs
        ${CMAKE_BINARY_DIR}/external_libs
)

add_executable(${PROJECT_NAME} text_centering.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE external_libs)

project(staticRandom LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
add_executable(${PROJECT_NAME} staticRandom.cpp)