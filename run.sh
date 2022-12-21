#!/bin/sh
make test
export LD_LIBRARY_PATH=":"
export LD_PRELOAD=`pwd`/libft_malloc.so

# echo "==========TEST 0=========="
# ./test00
# echo "==========TEST 1=========="
# ./test01
# echo "==========TEST 2=========="
# ./test02
# echo "==========TEST 3=========="
# ./test03
# echo "==========TEST 4=========="
# ./test04
# echo "==========TEST 5=========="
# ./test05 | less
# echo "==========MYTEST=========="
export TEST coucou
env