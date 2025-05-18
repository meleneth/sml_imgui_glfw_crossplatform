cmake_minimum_required(VERSION 3.21)
project(sml_imgui_demo LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Set up dependencies
add_subdirectory(external)

# Add source files
add_executable(sml_imgui
    src/main.cpp
)

target_link_libraries(sml_imgui PRIVATE
    glfw
    glad
    imgui
)

target_include_directories(sml_imgui PRIVATE
    ${PROJECT_SOURCE_DIR}/external/stb
)
