cmake_minimum_required(VERSION 3.10)

# set the project name
project(Server)

set(EXEC server)

set(CMAKE_CXX_STANDARD 14)

include_directories(includes)

file(GLOB SOURCES src/*.cpp)

# add the executable
add_executable(${EXEC} ${SOURCES})