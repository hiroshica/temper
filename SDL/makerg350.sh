#/bin/bash
export PATH=/opt/rg350-toolchain/usr/bin:$PATH
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/lib:/usr/lib:/opt/gcw0-toolchain/usr/lib/
make -f Makefile.rg350
