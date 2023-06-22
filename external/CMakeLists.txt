add_library(external INTERFACE)

message(STATUS "Fetching SDL2")
# Update submodules
find_package(Git REQUIRED)
execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive COMMAND_ERROR_IS_FATAL ANY)

add_subdirectory(SDL)
target_link_libraries(external INTERFACE SDL2-static)

add_subdirectory(nicemath)