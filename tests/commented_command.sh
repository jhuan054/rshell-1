Script started on Fri 18 Nov 2016 10:48:45 PM PST
]0;jhuan054@hammer:~/wop/tests[?1034h[jhuan054@hammer tests]$ echo A #echo B
A
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ echo A #echo B[1@&[1@&[1@ 
A
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ echo A #&& echo B[1P[C[C[C[C[C[C[C[C[C#[K #&& echo C
A
B
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ ecgi A #; echo B
bash: ecgi: command not found
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ echo A #; echo B
A
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ e[Kecho A #; echo B[C[1P[1@|[1@|
A
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ echo A || [K[K[K&& echo B
A
B
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ echo A && echo B[1P[1P[1@|[1@|
A
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ echo A || echo B[1P[1P[1@;
A
B
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ ls -j && echo A
ls: invalid option -- 'j'
Try `ls --help' for more information.
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ ls -j && echo A[1P[1P[1@|[1@|
ls: invalid option -- 'j'
Try `ls --help' for more information.
A
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ ls -j || echo A[1P[1P[1P[1@;
ls: invalid option -- 'j'
Try `ls --help' for more information.
A
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ ls -j; echo A[2@ ||[C[C[C[C[C[C[C&&[C[C[C[C[C[C[C && [K[K[K||echo B
ls: invalid option -- 'j'
Try `ls --help' for more information.
B
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ echo A || echo B || echo C
A
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ echo A || echo B || echo C[1P[1P[1@&[1@&
A
C
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ echo A || echo B && echo C[C # print a[KA, B, C[C[1P[1P[1@&[1@&
A
B
C
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ ls
commented_command  exit.sh
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ ls- al[K[K[K[K -al
total 12
drwxr-xr-x 2 jhuan054 csmajs 4096 Nov 18 22:39 [0m[38;5;27m.[0m
drwxr-xr-x 3 jhuan054 csmajs 4096 Nov 18 22:22 [38;5;27m..[0m
-rw-r--r-- 1 jhuan054 csmajs    0 Nov 18 22:48 commented_command
-rw-r--r-- 1 jhuan054 csmajs  501 Nov 18 22:39 exit.sh
[m]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ ls -al[K[Kj
ls: invalid option -- 'j'
Try `ls --help' for more information.
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ echo A
A
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ echo AB CD
AB CD
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ help help
help: help [-dms] [pattern ...]
    Display information about builtin commands.
    
    Displays brief summaries of builtin commands.  If PATTERN is
    specified, gives detailed help on all commands matching PATTERN,
    otherwise the list of help topics is printed.
    
    Options:
      -d	output short description for each topic
      -m	display usage in pseudo-manpage format
      -s	output only a short usage synopsis for each topic matching
    	PATTERN
    
    Arguments:
      PATTERN	Pattern specifiying a help topic
    
    Exit Status:
    Returns success unless PATTERN is not found or an invalid option is given.
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ pwd
/home/csmajs/jhuan054/wop/tests
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ echo echo
echo
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ echa 
bash: echa: command not found
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ a[Kecha AB
bash: echa: command not found
]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ cal
    November 2016   
Su Mo Tu We Th Fr Sa
       1  2  3  4  5
 6  7  8  9 10 11 12
13 14 15 16 17 [7m18[27m 19
20 21 22 23 24 25 26
27 28 29 30

]0;jhuan054@hammer:~/wop/tests[jhuan054@hammer tests]$ exit
exit

Script done on Fri 18 Nov 2016 10:53:47 PM PST
