cmake_minimum_required(VERSION 3.16...3.25)
project(sml_imgui_demo LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Set up dependencies
add_subdirectory(external)

FetchContent_Declare(
  boost_sml
  GIT_REPOSITORY https://github.com/boost-ext/sml.git
)

FetchContent_MakeAvailable(boost_sml)

# Manually define a CMake interface library for Boost.SML

add_library(boost_sml INTERFACE)

target_include_directories(boost_sml INTERFACE

    ${boost_sml_SOURCE_DIR}/include

)

# Add source files
add_executable(brine
 src/main.cpp
 src/brine/context.hpp
 src/brine/context.cpp
 src/brine/run_loop.hpp
 src/brine/brine_types.hpp
 src/brine/brine_gl_includes.hpp
 src/state/quadrant_fsm_definition.hpp
 src/state/quadrant_fsm.hpp
 src/state/quadrant_fsm.cpp
)

add_executable(standalone_complex
  src/standalone_complex.cpp
  src/brine/context.hpp
  src/brine/context.cpp
  src/brine/run_loop.hpp
  src/brine/brine_types.hpp
  src/brine/brine_gl_includes.hpp
)

target_link_libraries(brine PRIVATE
 glfw
 glad
 imgui
 boost_sml
)

target_link_libraries(standalone_complex PRIVATE
 glfw
 glad
 imgui
 boost_sml
)

target_include_directories(brine PRIVATE
 ${PROJECT_SOURCE_DIR}/external/stb
)

# Format source code with clang-format
find_program(CLANG_FORMAT_EXE NAMES clang-format)

if(CLANG_FORMAT_EXE)
  file(GLOB_RECURSE ALL_SOURCE_FILES
 "${CMAKE_SOURCE_DIR}/src/*.cpp"
 "${CMAKE_SOURCE_DIR}/src/*.hpp"
 "${CMAKE_SOURCE_DIR}/include/*.hpp"
 "${CMAKE_SOURCE_DIR}/include/*.h"
 "${CMAKE_SOURCE_DIR}/*.cpp"
 "${CMAKE_SOURCE_DIR}/*.hpp"
 )

  add_custom_target(
 clang-format
 COMMAND ${CLANG_FORMAT_EXE} -i ${ALL_SOURCE_FILES}
 COMMENT "Running clang-format on source files"
                )
else()
  message(WARNING "clang-format not found!")
endif()



