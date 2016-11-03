#ifndef CommandLine_H
#define CommandLine_H	   
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm> 
#include <fstream>
   
using namespace std;


class CommandLine
{
    protected:
    string line;
    
    public:
    CommandLine() {};
    CommandLine(string line):line(line) {};
    
    virtual void exe(CommandLine line) {};
    
    string out()
    {
        string outline;
        cout<<outline<<endl;
        outline = this->line;
        return outline;
    }
};
#endif
