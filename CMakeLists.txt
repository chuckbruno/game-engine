# CMakeList.txt : CMake project for GameEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(GameEngine)

# Add source to this project's executable.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# TODO: Add tests and install targets if needed.

add_subdirectory("src")
# add_subdirectory("src/physics-engine")
target_include_directories(GameEngine PUBLIC "${PROJECT_SOURCE_DIR}/src/physics-engine/include")


