set(CMAKE_SYSTEM_NAME "Linux")

if("${CROSS}" STREQUAL "")
  set(CROSS mipsel-linux-)
endif ()

set(MIPS_FLAGS "${MIPS_FLAGS} -mips32r2 -DDYNAREC_SKIP_DCACHE_FLUSH -DTMPFS_MIRRORING -DTMPFS_DIR=/tmp -mno-abicalls -fno-PIC -mno-check-zero-division")

if("${MODEL}" STREQUAL "rs97")
  set(MIPS_FLAGS "${MIPS_FLAGS} -DRS97")
elseif("${MODEL}" STREQUAL "rg350")
  set(MIPS_FLAGS "${MIPS_FLAGS} -DRG350")
else()
  set(MIPS_FLAGS "${MIPS_FLAGS} -DGCW_ZERO")
endif()

if("${TOOLCHAIN_PREFIX}" STREQUAL "")
  set(TOOLCHAIN_PREFIX "/opt/${MODEL}-toolchain/usr")
endif()

set(TOOL_OS_SUFFIX "")
if(CMAKE_HOST_WIN32)
 set(TOOL_OS_SUFFIX ".exe")
endif()

set(CMAKE_SYSTEM_PROCESSOR "mipsel")
set(CMAKE_C_COMPILER   "${TOOLCHAIN_PREFIX}/bin/${CROSS}gcc${TOOL_OS_SUFFIX}"     CACHE PATH "C compiler")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PREFIX}/bin/${CROSS}g++${TOOL_OS_SUFFIX}"     CACHE PATH "C++ compiler")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_PREFIX}/bin/${CROSS}gcc${TOOL_OS_SUFFIX}"     CACHE PATH "assembler")
set(CMAKE_STRIP        "${TOOLCHAIN_PREFIX}/bin/${CROSS}strip${TOOL_OS_SUFFIX}"   CACHE PATH "strip")
set(CMAKE_AR           "${TOOLCHAIN_PREFIX}/bin/${CROSS}ar${TOOL_OS_SUFFIX}"      CACHE PATH "archive")
set(CMAKE_LINKER       "${TOOLCHAIN_PREFIX}/bin/${CROSS}ld${TOOL_OS_SUFFIX}"      CACHE PATH "linker")
set(CMAKE_NM           "${TOOLCHAIN_PREFIX}/bin/${CROSS}nm${TOOL_OS_SUFFIX}"      CACHE PATH "nm")
set(CMAKE_OBJCOPY      "${TOOLCHAIN_PREFIX}/bin/${CROSS}objcopy${TOOL_OS_SUFFIX}" CACHE PATH "objcopy")
set(CMAKE_OBJDUMP      "${TOOLCHAIN_PREFIX}/bin/${CROSS}objdump${TOOL_OS_SUFFIX}" CACHE PATH "objdump")
set(CMAKE_RANLIB       "${TOOLCHAIN_PREFIX}/bin/${CROSS}ranlib${TOOL_OS_SUFFIX}"  CACHE PATH "ranlib")

set(CMAKE_C_FLAGS          "${CMAKE_C_FLAGS} ${MIPS_CFLAGS}"     CACHE STRING "C flags")
set(CMAKE_CXX_FLAGS        "${CMAKE_CXX_FLAGS} ${MIPS_CXXFLAGS}" CACHE STRING "C++ flags")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--as-needed -Wl,--gc-sections" CACHE STRING "Executable linker flags")

# No runtime cpu detect for mipsel-linux-gcc.
set(CONFIG_RUNTIME_CPU_DETECT 0 CACHE BOOL "")

execute_process(COMMAND ${CMAKE_C_COMPILER} -print-sysroot OUTPUT_VARIABLE MIPS_SYSROOT_PATH OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CMAKE_FIND_ROOT_PATH "${MIPS_SYSROOT_PATH}")

set(CMAKE_PREFIX_PATH "${TOOLCHAIN_PREFIX}/bin;${TOOLCHAIN_PREFIX}/mipsel-gcw0-linux-uclibc/sysroot/usr/bin")
#set(ENV{PKG_CONFIG_PATH} "${TOOLCHAIN_PREFIX}/mipsel-gcw0-linux-uclibc/sysroot/usr/lib32/pkgconfig")

if(NOT CMAKE_FIND_ROOT_PATH_MODE_LIBRARY)
  set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
endif()
if(NOT CMAKE_FIND_ROOT_PATH_MODE_INCLUDE)
  set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
endif()
