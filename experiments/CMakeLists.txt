cmake_minimum_required(VERSION 3.30)
project(Experiments LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

# Add external libraries
add_subdirectory(
        ../external_libs
        ${CMAKE_BINARY_DIR}/external_libs
)

add_executable(Text_centering text_centering.cpp)
target_link_libraries(Text_centering PRIVATE external_libs)

add_executable(staticRandom staticRandom.cpp)
add_executable(passingArray passingArray.cpp)
add_executable(CompilerOptimizations CompilerOptimizations.cpp)
add_executable(sizeOf sizeOf.cpp)
add_executable(VectorOfDerivedClasses VectorOfDerivedClasses.cpp)
add_executable(GetNameOfType GetNameOfType.cpp)
add_executable(EcsMini EcsMini.cpp)
add_executable(test test.cpp)