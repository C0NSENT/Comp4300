cmake_minimum_required(VERSION 3.31)
set(CMAKE_CXX_STANDARD 23)

project(ACTEPOID VERSION 0.1 LANGUAGES CXX)

add_subdirectory(
        ../../external_libs
        ${CMAKE_BINARY_DIR}/external_libs
)

set(SYSTEMS_SOURCES
        systems/Entity_Manager.cpp
        systems/Entity_Manager.hpp
        systems/Game.cpp
        systems/Game.hpp
        systems/Physics.cpp
        systems/Physics.hpp
)

#[[set(SYSTEMS_SOURCES
        systems/Game.cpp
        systems/Game.hpp
        systems/EntityManager.cpp
        systems/EntityManager.hpp

        )]]

add_executable(${PROJECT_NAME}
        ${SYSTEMS_SOURCES}

        Entity.cpp
        Entity.hpp
        Components.hpp
        Vector2.tpp
        main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC external_libs)