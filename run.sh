#!/bin/sh

# autocompil
make re
make test

#						WARNING
# for 0 to 2 test please use /usr/bin/time before the exec

#export lib for linux
export LD_LIBRARY_PATH="."
export LD_PRELOAD=`pwd`/libft_malloc.so

#export lib for macos
# export DYLD_LIBRARY_PATH="."
# export DYLD_INSERT_LIBRARIES="libft_malloc.so"

# valgrind $@
$@
