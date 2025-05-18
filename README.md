This codebase exists to play around with imgui and sml state machines.

<https://github.com/ocornut/imgui>

<https://github.com/boost-ext/sml>

There are multiple branches!

The main branch will have the up-to-date full list, other branches will be at various states.

initial - this is the initial bare-bones cross-compileable "where it all started" simplest possible example.
01_raii_appears - this is the first version with multiple source files, and renames the binary to 'brine'. This is also the version where the valgrind suppresion file comes in, because the call stack for library initialization changes with the extra files, which changes the stack traces for the library 'leaks' that valgrind sees.
02_machine_state_popup - Added a quad FSM setup, and maybe a popup? added a clang-format option to cmake

# Instructions

This assumes you have docker installed. <https://docs.docker.com/engine/install/>
These instructions should build the exe in a directory called win-build

    docker build -t winbuilder .
    ./build-windows.sh

# Code Formatting

cmake --build . --target clang-format

# Debug build, for linux

cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build

This is the version that was used to generate the initial valgrind suppressions. They should cover the minimal RAII version, which means they should catch all the library leaks that we as user level devs can't do anything about.

this was done via

    valgrind --leak-check=full --show-reachable=yes --error-limit=no --gen-suppressions=all --log-file=valgrind.log ./build/brine
    cat valgrind.log | ./gen_valgrind_supressions > valgrind-clean.supp

which lets us run

    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=valgrind-clean.supp ./build/brine
