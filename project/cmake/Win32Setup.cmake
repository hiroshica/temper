##########################################################################################
#    setup for Linux version
##########################################################################################
#  compiler setting
add_definitions(-D__OS_WIN32__)
add_definitions(/wd4819)	# warning UTF-8N
set(LIB_DIR "lib/win32")
set(USE_SSBULLET "true")

# compiler default option
# Win32
set(C_DEF_FLAGS "-Wno-unused -D_IRR_STATIC_LIB_")
set(CXX_DEF_FLAGS "-fcheck-new -Wno-unused -Wno-invalid-offsetof -D_IRR_STATIC_LIB_")

# setup default SsLib
INCLUDE(SsLibCommonSetup)

# additional include/library path
include_directories(${PROJECT_SOURCE_DIR}/win32/include)
link_directories(${PROJECT_SOURCE_DIR}/win32/lib)

# architechture archive name
set(SSLIB_ARCH_SUBDIRECTORY DX)
set(SSLIB_ARCH_ARCHIVES arch_${SSLIB_ARCH_SUBDIRECTORY}${PROJECTSS_LIB_SUFFIX})

# setup SsLibraries
set(SSLIB_ARCHIVES 
  sscore${PROJECTSS_LIB_SUFFIX}
  ssbullet${PROJECTSS_LIB_SUFFIX}
  sssound${PROJECTSS_LIB_SUFFIX}
  ssirrlicht${PROJECTSS_LIB_SUFFIX}
  sscore${PROJECTSS_LIB_SUFFIX}
  ${SSLIB_ARCH_ARCHIVES}
  ssresource${PROJECTSS_LIB_SUFFIX}
  )

# setup platform libraries
set(PLATFORM_LIBS SDL SDLmain dsound dinput8 d3d9 d3dx9 dxguid)

################ end of file ################
