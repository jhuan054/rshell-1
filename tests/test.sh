#!/bin/sh
test -e BuiltIn.cpp && echo BuiltIn.cpp exists
test -d BuiltIn.cpp || echo directory BuiltIn.cpp does not exist
[ -e BuiltIn.cpp ] && echo BuiltIn.cpp exists
[ -f BuiltIn.cpp ] && echo file BuiltIn.cpp exists
mkdir Demo
touch demo.cpp
test -d Demo && echo directory Demo exists
test -f demo.cpp && echo file demo.cpp exists
rm demo.cpp
rm -r Demo
[ -d Demo ] || echo directory Demo does not exist
test -f demo.cpp || echo file demo.cpp does not exist
exit
