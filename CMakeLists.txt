# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.21)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

# Rename the project
SET(PROJECT_NAME BARCAMP_GAME_PHYSICS)

project (${PROJECT_NAME} VERSION 0.1)

# Include external dependencies
add_subdirectory (external)
# Include sub-projects.
add_subdirectory (src)

target_link_libraries(${PROJECT_NAME} PRIVATE external)