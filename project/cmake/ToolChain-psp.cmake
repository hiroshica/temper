INCLUDE(CMakeForceCompiler)

# the name of the target operating system
SET(CMAKE_SYSTEM_NAME PSP)

# which compilers to use for C and C++
CMAKE_FORCE_C_COMPILER(psp-gcc GNU)
CMAKE_FORCE_CXX_COMPILER(psp-gcc GNU)

#set(CMAKE_C_LINK_EXECUTABLE "psp-gcc")

# here is the target environment located
SET(CMAKE_FIND_ROOT_PATH  /usr/local/pspdev/psp)

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
