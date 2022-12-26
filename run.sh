#!/bin/sh

#compile test
make test

#export lib for linux
export LD_LIBRARY_PATH=":"
export LD_PRELOAD=`pwd`/libft_malloc.so

#export lib for macos
# export DYLD_LIBRARY_PATH="."
# export DYLD_INSERT_LIBRARIES="libft_malloc.so"

# echo "==========TEST 0=========="
# echo "=========================="
# ./test00
# echo "=========================="
# echo "==========TEST 1=========="
# echo "=========================="
# ./test01
# echo "=========================="
# echo "==========TEST 2=========="
# echo "=========================="
# ./test02
# echo "=========================="
# echo "==========TEST 3=========="
# echo "=========================="
# ./test03
# echo "=========================="
# echo "==========TEST 4=========="
# echo "=========================="
# ./test04
# echo "=========================="
# echo "==========TEST 5=========="
# echo "=========================="
# ./test05
# echo "=========================="
#echo "==========MYTEST=========="
# echo "=========================="
# ./mytest
# echo "=========================="

emacs
#echo "MERCI BEBOU <3 <3"