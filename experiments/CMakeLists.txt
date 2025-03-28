cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX 23)

add_subdirectory("D:/Open this folder only if you are listening Skinny Puppy
        rn/C++/MEH Engine/external_libs")


project(Text_centering)
add_executable(${PROJECT_NAME} text_centering.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE external_libs)