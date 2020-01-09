#/bin/bash
export PATH=/opt/gcw0-toolchain/usr/bin:$PATH
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/lib:/usr/lib:/opt/gcw0-toolchain/usr/lib/
cd SDL ; make -f Makefile.rg350 $1 ; cd ..
