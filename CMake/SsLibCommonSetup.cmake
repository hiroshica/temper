##########################################################################################
# common setup (SsLib)
##########################################################################################
# add graphic include
set(SSLIB_SOURCE_DIR ${PROJECT_SOURCE_DIR}/sdk)

#include_directories(
#	"${SSLIB_SOURCE_DIR}/SsIrrlicht/include"
#	"${SSLIB_SOURCE_DIR}/SsIrrlicht/include/irr"
#	"${SSLIB_SOURCE_DIR}/SsIrrlicht/srcs/irr"
#	"${SSLIB_SOURCE_DIR}/SsIrrlicht/srcs/irr/zlib"
#	"${SSLIB_SOURCE_DIR}/SsIrrlicht/srcs/irr/jpeglib"
#	"${SSLIB_SOURCE_DIR}/SsIrrlicht/srcs/irr/libpng"
#)

# include path
set(SSLIB_INCLUDE_PATH "${SSLIB_SOURCE_DIR}/SsLib/include")
include_directories(${SSLIB_INCLUDE_PATH})

################ end of file ################
