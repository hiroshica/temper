##########################################################################################
#    setup for Linux version
##########################################################################################
#  compiler setting
add_definitions(-D__OS_LINUX__)
set(CMAKE_LINKER /usr/bin/gcc)

# Compiler mode flag
set(COMPILE_MODE_FLAG "-m64 -D__ADDRESS_64BIT__")
set(LIB_DIR "lib/linux")
# setup platform libraries
set(PLATFORM_LIBS GL GLU SDL)

# compiler default option
# Linux
set(C_DEF_FLAGS "${COMPILE_MODE_FLAG} -Wno-unused)
set(CXX_DEF_FLAGS "${COMPILE_MODE_FLAG} -fcheck-new -Wno-unused -Wno-invalid-offsetof)
set(CMAKE_EXE_LINKER_FLAGS "${COMPILE_MODE_FLAG}")

################ end of file ################
