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
    bool execte(CommandLine command)
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
                //this->line = programFail();
                //perror(this->out().c_str());
                //delete[] arg;
                setStatus(false);
                perror("rshell error");
                //kill(pid, SIGKILL);
            
            }
            delete[] arg;
            exit(EXIT_FAILURE);
        } 
        else if (pid < 0) 
        {
            // Error forking
           // delete[] arg;
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
        //if (WIFEXITED(child_status)) this->line = "t";
        //else this->line = "f";
        /*if (WEXITSTATUS(status) != 0) 
        {

           this->status = false;
        }*/
    delete[] arg;
        return WIFEXITED(child_status);
    }
    
    void setStatus(bool b){

        status = b;

        }
    bool getStatus(){
        return status;
    }   
    
};
#endif
