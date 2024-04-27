cmake_minimum_required(VERSION 3.20)

project(race_simulator)

# Find OpenMP package
find_package(OpenMP REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    src/main.cpp
    src/interface.cpp
    src/player.cpp
    src/simulator.cpp
    src/game.cpp
    )

# Create executable from sources
add_executable(race_simulator ${SOURCES})

# Link against the ncurses library
target_link_libraries(race_simulator PRIVATE 
    OpenMP::OpenMP_CXX 
    ncursesw
    )

