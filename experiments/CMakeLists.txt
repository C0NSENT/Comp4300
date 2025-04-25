cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD  23)

add_subdirectory(
        "../Comp4300/external_libs"
        "${CMAKE_BINARY_DIR}/external_libs"
)

project(Text_centering)
add_executable(${PROJECT_NAME} text_centering.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE external_libs)