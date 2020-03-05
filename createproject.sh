#!/bin/bash
#
function usages
{
    echo ""
    echo "$0 : create CMake project"
    echo " usage : $0 [linux/mingw/win32/rg350] [debug/debugmaster/finalmaster]"
    echo ""
    echo "linux/mingw/win32/rg350  : target system"
    echo "debug/debugmaster/finalmaster : build type"
}
####
function makeproject
{
export PROJECTDIR=$PWD/project
export SRCDIR=../../../project
export CMAKEMODULEDIR=$PWD/CMake

COMPILE_TYPE="$1"

    if [ "$1" = "linux" ] ; then
	echo "create linux type"
	PROJDIR=build/"$COMPILE_TYPE"/$2
	PTARGET='Unix Makefiles'
	PTARGET_OPT=""
	TOOLCHAIN=-DCMAKE_TOOLCHAIN_FILE=$CMAKEMODULEDIR/LinuxSetup.cmake
	LINUXMACHINE=`uname -m`

    elif  [ "$1" = "rg350" ] ; then
	echo "create RG350PROJECT type"
	PROJDIR=build/$1/$2
	PTARGET='Unix Makefiles'
	PTARGET_OPT=""
	TOOLCHAIN=-DCMAKE_TOOLCHAIN_FILE=$CMAKEMODULEDIR/mips32-linux-gcc.cmake

    elif  [ "$1" = "mingw" ] ; then
	echo "create mingw type"
	PROJDIR=build/$1/$2
	PTARGET='MSYS Makefiles'
	PTARGET_OPT=""
	#TOOLCHAIN=-DCMAKE_TOOLCHAIN_FILE=$PROJECTDIR/CMake/MingWSetup.cmake
	#TOOLCHAIN=-DCMAKE_TOOLCHAIN_FILE=$PROJECTDIR/CMake/ToolChain-i586-mingw32.cmake
	TOOLCHAIN=-DCMAKE_TOOLCHAIN_FILE=$CMAKEMODULEDIR/Windows-GNU.cmake

    elif  [ "$1" = "win32" ] ; then
	echo "create win32 type"
	PROJDIR=build/$1/$2
	PTARGET='Visual Studio 9 2008'
	PTARGET_OPT=""
	TOOLCHAIN=""

    else
	usages
	exit 1
    fi
# create project
    mkdir -p $PROJDIR
    pushd $PROJDIR ; cmake -G "$PTARGET" $PTARGET_OPT -DCOMPILE_TYPE="$COMPILE_TYPE" -DMODEL="$COMPILE_TYPE" -DCMAKE_BUILD_TYPE="$2" -DLINUX_OS="$LINUXMACHINE" -DCMAKE_MODULE_PATH="$CMAKEMODULEDIR" $TOOLCHAIN $SRCDIR ; popd
}
####
if [ $# -eq 1 ] ; then
    usages
	makeproject $1 debug
	exit 0
elif [ $# -ne 2 ] ; then
    usages
    exit 1
fi
#### start
makeproject $1 $2
exit 0

#### end of file ####
