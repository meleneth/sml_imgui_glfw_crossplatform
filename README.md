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
