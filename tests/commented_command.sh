#!/bin/sh
echo beginning tests
echo A #echo B
echo A #&& echo B
echo A && echo B #&& echo C
echo A #; echo B
echo A #|| echo B
#multi
echo A && echo B
echo A || echo B
echo A; echo B
ls -j && echo A
ls -j || echo A
ls -j; echo A
ls -j && echo A || echo B
echo A || echo B || echo C
echo A || echo B && echo C
echo A && echo B && echo C  # print A, B, C
#single
ls
ls -al
ls -j
echo A
echo AB CD
help help
pwd
echo echo
echa AB
cal
