cmake_minimum_required(VERSION 3.16...3.25)
project(sml_imgui_demo LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Set up dependencies
add_subdirectory(external)

# Add source files
add_executable(brine
    src/main.cpp
    src/brine/context.hpp
    src/brine/context.cpp
    src/brine/run_loop.hpp
    src/brine/brine_types.hpp
)

target_link_libraries(brine PRIVATE
    glfw
    glad
    imgui
)

target_include_directories(brine PRIVATE
    ${PROJECT_SOURCE_DIR}/external/stb
)
