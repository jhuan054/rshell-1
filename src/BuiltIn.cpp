# ifndef Builtin_H
# define Builtin_H
# pragma GCC diagnostic ignored "-Wwrite-strings"
# include "CommandLine.cpp"
# define LSH_TOK_DELIM " \t\r\n\a"
//# define LSH_TOK_DELIM " "
# include<stdio.h>
# include <string.h>
# include <cstring>
# include <unistd.h>
# include <stdlib.h> 
# include <sys/types.h>
# include <sys/wait.h> 
#include <sys/stat.h>
#include <time.h>

class BuiltIn : public CommandLine
{
    
    protected:
    int num;// = 1;
    
    public:
    BuiltIn()
    {
        num = 3;
    }
    
    string rshell_exit(char** arglist)
    {
        return "e";
    }
    
    string rshell_test(char** arglist)
    {
        int exist;
        struct stat sb;
        //cout<<arglist[1]<<endl;
        //cout<<arglist[2]<<endl;
        if (string(arglist[1]) != "-e"  && string(arglist[1]) != "-f" && string(arglist[1]) != "-d"){
            
            exist = stat(arglist[1], &sb);
            if (exist == 0) cout<<"(True)"<<endl;
            else cout<<"(False)"<<endl;
        }
        else if ( string(arglist[1]) == "-e" ){
            exist = stat(arglist[2], &sb);
            if (exist == 0) cout<<"(True)"<<endl;
            else cout<<"(False)"<<endl;
        }
        else if ( string(arglist[1]) == "-f"){
            exist = stat(arglist[2], &sb);
            if(S_ISREG(sb.st_mode)) cout<<"(True)"<<endl;
            else cout<<"(False)"<<endl;
        }
        else if ( string(arglist[1]) == "-d"){
            exist = stat(arglist[2], &sb);
            if(S_ISDIR(sb.st_mode)) cout<<"(True)"<<endl;
            else cout<<"(False)"<<endl;
        }
        return "s";
    }
    
    
    void exe(CommandLine command)
    {
        char* builtinCommand[]={
            "exit",
            "test",
            "[" //May be added later
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
               if (i == 0) this->line = rshell_exit(tokens);
               else if (i == 1) this->line = rshell_test(tokens);
               else if (i == 2) this->line = rshell_test(tokens);
            }
         }delete[] arg;
    }
    
    int num_evl()
    {
        return this->num;
    }

};

#endif