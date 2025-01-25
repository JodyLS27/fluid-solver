# Engine CMake Lists

# Used mark this as a static library
add_library(engine STATIC src/engine.cpp "src/window/window.cpp")

target_include_directories(engine PRIVATE include)

# Additional CMake scripts, Add External Libraries 
include(cmake/FetchGLFW.cmake)

add_subdirectory(src)

# TODO: Add A Folder for each of the External Libs.

target_link_libraries(engine PRIVATE glfw) # Might need to be Pulic if the editor includes headers from engine.