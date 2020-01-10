##########################################################################################
#    setup for Linux version
##########################################################################################
#  compiler setting
add_definitions(-D__OS_MINGW__ -D__MINGW32__)
set(CMAKE_EXE_LINKER_FLAGS -mwindows)

# compiler default option
# MinGW32
set(C_DEF_FLAGS "-Wno-unused ${SDL_INCLUDE_DIRS}")
set(CXX_DEF_FLAGS "-fcheck-new -Wno-unused ${SDL_INCLUDE_DIRS}")
set(PLATFORM_LIBS "${SDL_LIBRARY} -mconsole -lbz2 -lz -lvorbisfile -lvorbis -logg -lwsock32")

################ end of file ################
