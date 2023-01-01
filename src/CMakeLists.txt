# CMakeList.txt : CMake project for GameEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
# add_executable (GameEngine "GameEngine.cpp")
add_subdirectory("physics-engine")

add_executable (GameEngine "GameEngine.cpp"  "Game.hpp" "Game.cpp")

# TODO: Add tests and install targets if needed.

find_package(SDL2 CONFIG REQUIRED)

target_link_libraries(GameEngine PRIVATE SDL2::SDL2 SDL2::SDL2main)  #
target_link_libraries(GameEngine PUBLIC PhysicsEngine)
# target_link_libraries(GameEngine PUBLIC PhysicsEngine)
