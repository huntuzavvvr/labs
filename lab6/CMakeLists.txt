cmake_minimum_required(VERSION 3.10)

project(BalagurFate3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(SOURCES
    include/NPC.hpp
    include/NPCFactory.hpp
    include/BattleVisitor.hpp
    include/LoggingVisitor.hpp
    include/Robber.hpp
    include/Walkingknight.hpp
    include/Elf.hpp
    include/NPCLoader.hpp
    include/NPCSaver.hpp
    include/ElfFactory.hpp
    include/WalkingknightFactory.hpp
    include/RobberFactory.hpp

    src/NPC.cpp
    src/main.cpp
    src/NPCFactory.cpp
    src/BattleVisitor.cpp
    src/LoggingVisitor.cpp
    src/Walkingknight.cpp
    src/Robber.cpp
    src/Elf.cpp
    src/NPCLoader.cpp
    src/NPCSaver.cpp
)

add_executable(BalagurFate3 ${SOURCES})