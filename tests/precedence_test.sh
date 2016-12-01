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
<<<<<<< HEAD
 (echo A) || (echo L && echo D)
=======
>>>>>>> caba6b563c8fb07c2aa7da1ee4f7a8a32deac8c7
