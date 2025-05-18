This codebase exists to play around with imgui and sml state machines.

<https://github.com/ocornut/imgui>

<https://github.com/boost-ext/sml>

There are multiple branches!

The main branch will have the up-to-date full list, other branches will be at various states.

initial - this is the initial bare-bones cross-compileable "where it all started" simplest possible example.

# Instructions

This assumes you have docker installed. <https://docs.docker.com/engine/install/>
These instructions should build the exe in a directory called win-build

    docker build -t winbuilder .
    ./build-windows.sh

# Debug build, for linux

cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build

This is the version that was used to generate the initial valgrind suppressions. They should cover the minimal RAII version, which means they should catch all the library leaks that we as user level devs can't do anything about.

this was done via

    valgrind --leak-check=full --show-reachable=yes --error-limit=no --gen-suppressions=all --log-file=valgrind.log ./build/brine
    cat valgrind.log | ./gen_valgrind_supressions > valgrind-clean.supp

which lets us run

    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=valgrind-clean.supp ./build/brine
