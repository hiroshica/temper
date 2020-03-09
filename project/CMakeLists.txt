##########################################################################################
#    this file is part of the CMake build system for ProjectSS
##########################################################################################
cmake_minimum_required(VERSION 3.1)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
cmake_policy(SET CMP0003 NEW)
#set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}../CMake")

################################################
MESSAGE("compile type = ${COMPILE_TYPE}")

#project(RG-Temp)
project(SsProjects)

################################################################################################
# pre setup
################################################################################################
################################################
# setup library cmake includes
################################################
if(COMPILE_TYPE STREQUAL "linux")
  # linux
elseif(COMPILE_TYPE STREQUAL "rg350")
  # rg350
#  set(PKG_CONFIG_EXECUTABLE "${TOOLCHAIN_PREFIX}/bin/pkg-config")
elseif(COMPILE_TYPE STREQUAL "mingw")
  # mingw32
  set(PKG_CONFIG_EXECUTABLE "C:/msys64/mingw64/bin/pkg-config.exe")
endif()

MESSAGE("pkgpath = $ENV{PKG_CONFIG_PATH}")
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL sdl REQUIRED)

if(COMPILE_TYPE STREQUAL "linux")
  # linux
  set(SDL_INC "${SDL_INCLUDE_DIRS}")
  set(SDL_LIBS "${SDL_LDFLAGS}")
elseif(COMPILE_TYPE STREQUAL "rg350")
  # rg350
  set(SDL_INC "${SDL_INCLUDE_DIRS}")
  set(SDL_LIBS "${SDL_LDFLAGS}")
elseif(COMPILE_TYPE STREQUAL "mingw")
  # mingw32
  set(SDL_INC "${SDL_INCLUDE_DIRS}")
  set(SDL_LIBS "${SDL_LDFLAGS};-mwindows")
endif()
MESSAGE("SDL_INC = ${SDL_INC}")
MESSAGE("SDL_LIBS = ${SDL_LIBS}")


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


################################################################################################
# setup by platform
################################################################################################
if(COMPILE_TYPE STREQUAL "linux")
  # linux
  add_definitions(-D__POINTER64BIT__)
  add_definitions(-D__LP64__)
  add_definitions(-D__OS_LINUX__)
  add_definitions(-DLINUX_X86_BUILD)
  set(PLATFORM_CFLAGS " ")
  set(PLATFORM_LIBS "-lz -lm -pthread ${SDL_LIBS}")
elseif(COMPILE_TYPE STREQUAL "rg350")
  # rg350
  add_definitions(-D__OS_LINUX__)
  add_definitions(-DRG350_BUILD)
  set(PLATFORM_CFLAGS "-Ofast -mips32r2 -mmxu -fdata-sections -ffunction-sections")
  set(PLATFORM_LIBS " -lz -lm -lbz2 -pthread -Wl,--as-needed -Wl,--gc-sections -flto -s ${SDL_LIBS}")
elseif(COMPILE_TYPE STREQUAL "mingw")
  # mingw32
  add_definitions(-D__LP64__)
  add_definitions(-D__POINTER64BIT__)
  add_definitions(-D__OS_MINGW__)
  add_definitions(-DWIN32_BUILD)
  set(PLATFORM_CFLAGS " ")
  set(PLATFORM_LIBS "-mconsole -lbz2 -lz -lvorbisfile -lvorbis -logg -lwsock32 ${SDL_LIBS}")
endif()

set(PROJECT_EXE_SUFFIX "${MACHINE_SUFFIX}${PROJECT_LIB_SUFFIX}")

if(SSLIB_ARCH_SUBDIRECTORY STREQUAL "SDLGL")
  add_definitions(-D__OPENGL__)
elseif(SSLIB_ARCH_SUBDIRECTORY STREQUAL "SDLGLES")
  add_definitions(-D__OPENGLES__)
elseif(SSLIB_ARCH_SUBDIRECTORY STREQUAL "SDL2")
  add_definitions(-D__SDL2ONLY__)
endif()


set(SSLIB_ARCH_ARCHIVES arch_${SSLIB_ARCH_SUBDIRECTORY}${PROJECT_LIB_SUFFIX})
set(BUILD_CFLAGS "${PLATFORM_CFLAGS}")
set(BUILD_CXXFLAGS "${PLATFORM_CXXFLAGS}")
set(BUILD_LDFLAGS "${PLATFORM_LIBS} ${SDL_LIBS}")

MESSAGE("first set BuildFlag ${BUILD_CFLAGS}")
MESSAGE("first set Buildlibs ${BUILD_LFLAGS}")
include_directories(${SDL_INC})

################################################################################################
# setup projects
################################################################################################
INCLUDE(SsLibCommonSetup)
set(PROJECT_WORK_DIR ${PROJECT_BINARY_DIR})
set(EXE_DIR "exe/${COMPILE_TYPE}")
set(LIB_DIR "lib/${COMPILE_TYPE}")

# Specify build paths
set(PROJECT_OUTPUT_TOPDIR ${PROJECT_SOURCE_DIR}/../out)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_TOPDIR}/${EXE_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_TOPDIR}/${LIB_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_TOPDIR}/${LIB_DIR}")
MESSAGE("OUTPUT_DIR = ${PROJECT_OUTPUT_TOPDIR}")
link_directories(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})


function(rg350_opk appname, app_comment, iconfile)
if(COMPILE_TYPE STREQUAL "rg350")
  set (NOWWORKDIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
  set (NOWWORKOUTFILE "${appname}")
  set (NOWWORKLASTOUTFILE "${NOWWORKOUTFILE}.opk")
  set (OPKPATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/opk_data)
  file(REMOVE_RECURSE ${OPKPATH})
  file(MAKE_DIRECTORY ${OPKPATH})
if(iconfile STRLESS "")
  file(COPY ${iconfile} ${OPKPATH}/icon.png)
endif()
#
  add_custom_target(${NOWWORKLASTOUTFILE} ALL
  DEPENDS ${NOWWORKOUTFILE}
  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
  COMMENT "Build OPK"
  COMMAND cp ${NOWWORKOUTFILE} "${OPKPATH}/"
  COMMAND echo "[Desktop Entry]" > ${OPKPATH}/default.gcw0.desktop
  COMMAND echo Type=Application >> ${OPKPATH}/default.gcw0.desktop
  COMMAND echo Name=${NOWWORKOUTFILE} >> ${OPKPATH}/default.gcw0.desktop
  COMMAND echo Comment=${app_comment} >> ${OPKPATH}/default.gcw0.desktop
  COMMAND echo Exec=${NOWWORKOUTFILE} %f >> ${OPKPATH}/default.gcw0.desktop
  COMMAND echo Icon=icon >> ${OPKPATH}/default.gcw0.desktop
  COMMAND echo Terminal=false >> ${OPKPATH}/default.gcw0.desktop
  COMMAND echo "Categories=emulators;" >> ${OPKPATH}/default.gcw0.desktop
  #COMMAND echo MimeType=.pce >> ${OPKPATH}/default.gcw0.desktop
  COMMAND ${CMAKE_STRIP} ${OPKPATH}/${NOWWORKOUTFILE}
  COMMAND ${TOOLCHAIN_PREFIX}/bin/mksquashfs ${OPKPATH} ${NOWWORKLASTOUTFILE} -all-root -noappend -no-exports -no-xattrs
  )
endif()
endfunction()

################################################
#    setup targets
################################################
#
#add_subdirectory(test)
add_subdirectory(temper)


################ end of file ################
