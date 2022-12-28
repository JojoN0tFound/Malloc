#!/bin/sh

#compile test
make test

#export lib for linux
# export LD_LIBRARY_PATH=":"
# export LD_PRELOAD=`pwd`/libft_malloc.so

#export lib for macos
export DYLD_LIBRARY_PATH="."
export DYLD_INSERT_LIBRARIES="libft_malloc.so"

# echo "================================================"
# echo "=====================TEST 0====================="
# echo "================================================"
# echo "Ce test sert de comparatif pour les tests 1 et 2"
# echo "================================================\n"
# /usr/bin/time -l ./test00
# echo "\n================================================"
# echo "=====================TEST 1====================="
# echo "================================================"
# echo "Nous testons le nombre de page reclaim en allouant"
# echo "1024 * 1024 bytes pour le comparer au test 0"
# echo "PR test 1 - PR test 0 = PR par le malloc "
# echo "================================================\n"
# /usr/bin/time -l ./test01
# echo "\n================================================"
# echo "=====================TEST 2====================="
# echo "================================================"
# echo "Test du free des pages reclaims l'objectif est"
# echo "d'arriver a +3 par rapport au test 0"
# echo "================================================\n"
# /usr/bin/time -l ./test02
# echo "\n================================================"
# echo "=====================TEST 3====================="
# echo "================================================\n"
# ./test03
# echo "\n================================================"
# echo "=====================TEST 4====================="
# echo "================================================\n"
# ./test04
# echo "\n================================================"
# echo "=====================TEST 5====================="
# echo "================================================\n"
# ./test05
# echo "\n================================================"
# echo "=====================MYTEST====================="
# echo "================================================\n"
# ./mytest
# echo "================================================\n"

emacs
# vim
# bash
# ls
# cat src/print.c | less
