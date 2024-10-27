#!/bin/bash

echo 11111 > in_file
echo 22222 > in_PROTECT_file
./move in_file out_file &> res_file
if [ ! $? == 0 ] || [ -f in_file ] || [ ! -f out_file ]; then
    echo "Error in test 1"
fi 
echo 11111 > in_file
rm out_file
strace -e trace=openat -P in_file -e fault=openat:error=EACCES:when=1 ./move in_file out_file &> res_file
if [ ! $? == 1 ] || [ ! -f in_file ] || [ -f out_file ]; then
    echo "Error in test 2"
fi
strace -e trace=openat -P out_file -e fault=openat:error=EACCES:when=1 ./move in_file out_file &> res_file
if [ ! $? == 2 ] || [ ! -f in_file ] || [ -f out_file ]; then
    echo "Error in test 3"
fi
strace -e trace=read -e fault=read:error=EINTR:when=2 ./move in_file out_file &> res_file
if [ ! $? == 3 ] || [ ! -f in_file ] || [ -f out_file ]; then
    echo "Error in test 4"
fi
strace -e trace=write -e fault=write:error=EINTR:when=1 ./move in_file out_file &> res_file
if [ ! $? == 4 ] || [ ! -f in_file ] || [ -f out_file ]; then
    echo "Error in test 5"
fi
strace -e trace=close -e fault=close:error=EACCES:when=3 ./move in_file out_file &> res_file
if [ ! $? == 5 ] || [ ! -f in_file ] || [ ! -f out_file ]; then
    echo "Error in test 6"
fi
strace -e trace=unlink -e fault=unlink ./move in_file out_file &> res_file
if [ ! $? == 6 ] || [ ! -f in_file ] || [ ! -f out_file ]; then
    echo "Error in test 7"
fi
LD_PRELOAD=./unlink.so ./move in_PROTECT_file out_file &> res_file
if [ ! $? == 0 ] || [ ! -f in_file ] || [ ! -f out_file ]; then
    echo "Error in test 8"
fi