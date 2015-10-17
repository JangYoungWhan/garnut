#
#  File    : CMakeLists.txt
#  Author  : YW. Jang
#  Date    : 2015.08.01.Sat
#
#  Copyright 2015, YW. Jang, All rights reserved.
#

cmake_minimum_required (VERSION 2.8)

project (libgarnut)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") # using gcc
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.8)
    message(FATAL_ERROR "GCC version must be at least 4.8!")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fexceptions -Wall")
  endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC") # using Visual Studio C++
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 17)
    message(FATAL_ERROR "MSVC version must be at least VC110!")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc")
  endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") # using Clang
    # require at least clang 3.2
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.2)
        message(FATAL_ERROR "Clang version must be at least 3.2!")
    endif()
else()
  message (FATAL_ERROR "Did not support this platform!")
endif()

add_definitions(-DUNICODE -D_UNICODE)

# Specify a common place where CMake should put the library.
#set (LIBRARY_OUTPUT_PATH ${${PROJECT_NAME}_BINARY_DIR}/lib CACHE PATH "Output directory for libraries" )

# Set compiler flags and options. 
# Here it is setting the Visual Studio warning level to 4
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
#message ("cxx Flags: " ${CMAKE_CXX_FLAGS})

# The version number.
set (GARNUT_VERSION_MAJOR 1)
set (GARNUT_VERSION_MINOR 0)
set (GARNUT_VERSION_REVISION 0)

set (PACKAGE_VERSION "${GARNUT_VERSION_MAJOR}.${GARNUT_VERSION_MINOR}.${GARNUT_VERSION_REVISION}")

# Configure a header file.
#configure_file ("${PROJECT_SOURCE_DIR}/garnut_config.h.in"
#                 "${PROJECT_BINARY_DIR}/garnut_config.h")

include_directories (${PROJECT_SOURCE_DIR}/include)

file (GLOB_RECURSE LIB_HDRS *.hpp)
file (GLOB_RECURSE LIB_SRCS *.cpp)

add_library (libgarnut STATIC
             ${LIB_HDRS}
             ${LIB_SRCS})