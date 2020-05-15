cmake_minimum_required(VERSION 3.0)

SET(CMAKE_CXX_COMPILER "g++")

PROJECT(RunProgram)

# set c++11 standard
if (CMAKE_VERSION VERSION_LESS "3.1")
  if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
  endif ()
else ()
  set (CMAKE_CXX_STANDARD 11)
endif ()

include_directories("/usr/local/ButlerIPU/include")
# include_directories("/usr/local/ButlerIPU/include")
# add CFLAGS
add_definitions("-O3 -Wall -g -lstdc++ -lstdc++fs -Wl,-rpath -fpermissive -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable -std=c++11")

# make a list of all source files for ButkerIPUServer
file(GLOB SOURCES "src/*.h" "src/*.cpp")

link_directories("/usr/local/ButlerIPU/lib")

# x86_64 settings
add_executable(RunProgram ${SOURCES})

target_link_libraries(RunProgram
  pthread
  boost_filesystem
  boost_system
  boost_iostreams

# /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.65.1
# /usr/lib/x86_64-linux-gnu/libboost_system.so
)

# target_include_directories(RunProgram PRIVATE
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
# )