# ifndef Builtin_H
# define Builtin_H
# pragma GCC diagnostic ignored "-Wwrite-strings"
# include "CommandLine.cpp"
# define LSH_TOK_DELIM " \t\r\n\a"
# include<stdio.h>
# include <string.h>
# include <cstring>
# include <unistd.h>
# include <stdlib.h> 
# include <sys/types.h>
# include <sys/wait.h> 
class BuiltIn : public CommandLine
{
    
    protected:
    int num;// = 1;
    
    public:
    BuiltIn()
    {
        num =1;
    }
    string rshell_exit(char** arglist)
    {
        return "e";
    }
    
    void exe(CommandLine command)
    {
        char* builtinCommand[]={
            "exit",
            //"cd"
            //"help"; May be added later
        };
        
        char* arg;
        char* token;
        char* tokens[100];
        int pos = 0;
        arg = new char [command.out().length() +1];
	    strcpy (arg, command.out().c_str());

        token = strtok(arg, LSH_TOK_DELIM);

        while (token != NULL)
        {
            tokens[pos] = token;
            pos++;
            token = strtok(NULL, LSH_TOK_DELIM);
        }
        
        for (int i = 0; i < this->num; i++) 
        {
            if (strcmp(tokens[0], builtinCommand[i]) == 0) {
               // delete[] arg;
            this->line = rshell_exit(tokens);
            }
         }delete[] arg;
    }
    
    int num_evl()
    {
        return this->num;
    }

};

#endif