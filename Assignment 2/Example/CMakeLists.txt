cmake_minimum_required(VERSION 3.31)
set(CMAKE_CXX_STANDARD 23)

project("Assignment2_Example" LANGUAGES CXX)
add_subdirectory(
        ../../external_libs
        ${CMAKE_BINARY_DIR}/external_libs
)
add_executable(${PROJECT_NAME}
        main.cpp
        Entity.cpp
        EntityManager.cpp
        Game.cpp
        Vec2.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE external_libs)
