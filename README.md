# rshell
UCR CS100 Open Source Shell

##### Authors:
* Chengkuan Hong 
* Justin Huang 

## Introduction
This project construcs a shell to run some UNIX commands. It supports ||, && and ; connectors.

## Installation
Run these commands in your terminal to install and run rshell on your system
```Installation
$ git clone https://github.com/srich009/rshell.git

$ cd rshell

$ git checkout hw2

$ make

$ bin/rshell
```

## Bugs
* The builtin command ```cd``` has NOT been implemented yet in this version of the shell (hw2)
* The host name obtained by ```gethostname()``` is limited to a maximum of 64 characters. Any name longer than that will be truncated. The hostName buffer is set to "UNKNOWN_HOST" if a failure occurs.
* The user name obtained by ```gelogin_r()``` is limited to a maximum of 64 characters. Any name longer than that will be truncated. The userName buffer is set to "UNKNOWN_USER" if a failure occurs.
* If the user enters improperly formatted command line arguments erroneous behavior may occur
    * ```user@host$ && ls``` will not execute ls
    * ```user@host$ || ls``` will execute ls
    * ```user@host$ ; ls``` errors will most likely occur