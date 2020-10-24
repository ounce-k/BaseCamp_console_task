cmake_minimum_required(VERSION 3.10)

# set the project name
project(Client)

set(EXEC client)

set(CMAKE_CXX_STANDARD 14)
IF(UNIX)
find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIR})
ENDIF(UNIX)

IF(WIN32)
find_library(USER32 user32)
ENDIF(WIN32)

include_directories(includes)

file(GLOB SOURCES src/*.cpp)

# add the executable
add_executable(${EXEC} ${SOURCES})
#IF(WIN32)
#target_link_libraries( client LINK_PUBLIC ${USBHID_LIB_DEPS} )
#ENDIF(WIN32)
