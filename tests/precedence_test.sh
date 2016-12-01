#!/bin/sh
(echo A)
(echo A || echo B)
(echo A && echo B)
(echo A || echo B && echo C)
(echo A && echo B && echo C)
echo A || (echo B || echo C)
echo A || (echo B && echo C)
echo A && (echo B || echo C)
echo A && (echo B && echo C)

echo A || (echo B || echo C); echo D
echo A || (echo B && echo C) || echo D
echo A && (echo B || echo C) && echo D
echo A && (echo B && echo C)  && echo D; echo P

(echo A || (echo B) || echo C)&& echo D
(echo A || (echo B && echo C) || echo D)
(echo A && (echo B || echo C)) && echo D
echo A && (echo B && echo C)  && (echo D || echo P)

echo A && echo B || echo C && echo D
(echo A && echo B) || (echo C && echo D)

((echo A && echo B) || echo C && echo D)

((echo A && echo B) || (echo C && echo D))

((echo A && echo B) || echo C && echo D)))
((echo A && echo B) || echo C && echo D))
(echo A && echo B) || echo C && echo D)
echo A && echo B) || echo C && echo D)



echo Generating bug
 (echo A) || (echo L && echo D)
