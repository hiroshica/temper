##########################################################################################
#    setup for Linux version
##########################################################################################
#  compiler setting
add_definitions(-D__OS_LINUX__)
set(CMAKE_LINKER /usr/bin/gcc)

# Compiler mode flag
set(COMPILE_MODE_FLAG "-m64")
set(LIB_DIR "lib/linux")
# setup platform libraries
#set(PLATFORM_LIBS GL GLU SDL)

# compiler default option
# Linux
set(CMAKE_C_FLAGS          "${CMAKE_C_FLAGS} ${COMPILE_MODE_FLAG} -Wno-unused"     CACHE STRING "C flags")
set(CMAKE_CXX_FLAGS        "${CMAKE_CXX_FLAGS} ${COMPILE_MODE_FLAG} -fcheck-new -Wno-unused" CACHE STRING "C++ flags")

set(CMAKE_EXE_LINKER_FLAGS "${COMPILE_MODE_FLAG} ")

################ end of file ################
