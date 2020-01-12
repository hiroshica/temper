##########################################################################################
#    this file is part of the CMake build system for ProjectSS
##########################################################################################
cmake_minimum_required(VERSION 2.6)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
cmake_policy(SET CMP0003 NEW)

project(temper)    #dummy project name

################################################
# setup library cmake includes
################################################
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL sdl REQUIRED)

MESSAGE("SDL_INC = ${SDL_INCLUDE_DIR}")
MESSAGE("SDL_LIBS = ${SDL_LIBRARIES}")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

################################################
# platform/build config
################################################
string(TOLOWER "${COMPILE_TYPE}" COMPILE)
string(TOLOWER "${CMAKE_BUILD_TYPE}" PROJECT_BUILD_TYPE)

################################################
# build config.
################################################
if (PROJECT_BUILD_TYPE STREQUAL "finalmaster")
  add_definitions(-D__FINALMASTER__)

elseif(PROJECT_BUILD_TYPE STREQUAL "debugmaster")
  add_definitions(-D__DEBUGMASTER__)
  set(PROJECT_LIB_SUFFIX "R")
else()
  add_definitions(-D__DEBUG__ -D_DEBUG)
  add_definitions(-g)
  set(PROJECT_LIB_SUFFIX "D")
endif()

set(PROJECT_EXE_SUFFIX "${MACHINE_SUFFIX}${PROJECT_LIB_SUFFIX}")

################################################
# setup project
################################################

INCLUDE(ConfigCompileType)

################################################
#    setup targets
################################################
#
add_subdirectory(temper)

################ end of file ################
