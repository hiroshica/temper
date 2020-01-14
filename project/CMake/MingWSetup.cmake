##########################################################################################
#    setup for Linux version
##########################################################################################
#  compiler setting
#add_definitions(-D__OS_MINGW__ -D__MINGW32__)
set(CMAKE_EXE_LINKER_FLAGS -mwindows)

# compiler default option
# MinGW32
set(CMAKE_C_FLAGS          "${CMAKE_C_FLAGS} ${COMPILE_MODE_FLAG}"     CACHE STRING "C flags")
set(CMAKE_CXX_FLAGS        "${CMAKE_CXX_FLAGS} ${COMPILE_MODE_FLAG} -fcheck-new" CACHE STRING "C++ flags")

################ end of file ################
