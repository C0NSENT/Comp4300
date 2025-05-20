cmake_minimum_required(VERSION 3.31)
set(CMAKE_CXX_STANDARD 23)

project(ACTEPOID VERSION 0.1 LANGUAGES CXX)
add_subdirectory(
        ../../external_libs
        ${CMAKE_BINARY_DIR}/external_libs
)
add_executable(${PROJECT_NAME}
        Vector2.tpp
        main.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE external_libs)