#ifndef Program_H
#define Program_H
# include "CommandLine.cpp"
# define LSH_TOK_DELIM " \t\r\n\a"
# include<stdio.h>
# include <string.h>
# include <cstring>
# include <unistd.h>
# include <stdlib.h> 
#include <sys/types.h>
#include <sys/wait.h> 
//#include "Execute.cpp"
class Program : public CommandLine
{
    protected:
    bool status;
    
    public:
    Program(){ status = true;}
    void exe(CommandLine command)
    {
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
        tokens[pos] = NULL;

        pid_t pid;
        int child_status;
        pid = fork();
        if (pid == 0) 
        {
        // Child process
            if (execvp(tokens[0], tokens) == -1)
            {
                setStatus(false);
                perror("rshell error");
                exit(5);
            }
            delete[] arg;
        } 
        else if (pid < 0) 
        {
            // Error forking
            perror("rshell error");
        } 
        else 
        {
            // Parent process
            do 
            {
                waitpid(pid, &child_status, WUNTRACED);
                //waitpid(pid, &child_status, 0);
            } while (!WIFEXITED(child_status) && !WIFSIGNALED(child_status));
           // delete[] arg;
            
        }

        if (WEXITSTATUS(child_status) == 5) 
        {

           this->status = false;
        }
        delete[] arg;

    }
    
    void setStatus(bool b){

        status = b;

        }
    bool getStatus(){
        return status;
    }   
    
};
#endif
