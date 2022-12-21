#!/bin/sh
make test
export LD_LIBRARY_PATH=":"
export LD_PRELOAD=`pwd`/libft_malloc.so


echo "========SHELLTEST========="
# ./test05
./mytest