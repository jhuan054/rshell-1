
#ifndef Execute_H
#define Execute_H
#pragma GCC diagnostic ignored "-Wwrite-strings"
# define LSH_TOK_DELIM " \t\r\n\a"
//# define LSH_TOK_DELIM " "
# include <stdio.h>
# include <string.h>
# include <cstring>
# include <unistd.h>
# include <stdlib.h> 
# include <sys/types.h>
# include <sys/wait.h> 
# include "Program.cpp"
# include "BuiltIn.cpp"
class Execute : public CommandLine
{
    protected:
    bool cont;
    bool exitShell; 
    
    public:
    Execute()
    {
        
        exitShell = true;
    }
    void exe(CommandLine command){
        char* arg;
        char* token;
        char* tokens[100];
        int pos = 0;

        arg = new char [command.out().length() +1];

	    strcpy (arg, command.out().c_str());

        token = strtok(arg, LSH_TOK_DELIM);

        while (token != NULL) {
            tokens[pos] = token;

            pos++;
            token = strtok(NULL, LSH_TOK_DELIM);

        }
    
        char* builtinCommand[]={
            "exit",
            "test",
            "[",
            "]"
        };
        BuiltIn builtin =  BuiltIn();
        Program program =  Program();
        if(tokens[0] == NULL){
            this->cont = 0;
        }

        for (int i = 0; i < builtin.num_evl(); i++) {

            if (strcmp(tokens[0], builtinCommand[i]) == 0) {
                if ( i == 0 || i == 1) builtin.exe(command);
                else{
                    if (strcmp(tokens[pos-1], builtinCommand[3]==0)) builtin.exe(command);
                    else{
                        cout<<"rshell error: missing ]"<<endl;
                        return;
                    }
                }
                if(builtin.out()=="e"){

                    this->exitShell = 0;
                }
                delete[] arg;

                return;
            }
        }
        program.exe(command);
        if (program.getStatus()) 
        {
            this->cont = 1;
        }
        else this->cont = 0;
        delete[] arg;
        return;
    } 
    
    bool exitevl(){
        return this->exitShell;
    }
    
    bool contevl(){
        return this->cont;
    }

    bool whetherNext(vector<Execute> execute, vector<CommandLine> connector,int pos){
        bool leftCommand = execute.at(0).contevl();
        if (connector.at(pos-1).out() == ";"){
            return 1;
        }
        for (int i = 0; i < pos - 1; i++){
            if (connector.at(i).out() == ";"){
                leftCommand = execute.at(i+1).contevl();
            }
        
            if (connector.at(i).out() == "&&"){
                leftCommand = leftCommand && execute.at(i+1).contevl();
            }
            if (connector.at(i).out() == "||"){
                leftCommand = leftCommand || execute.at(i+1).contevl();
            }
        }

        
        if (connector.at(pos-1).out() == "&&"){
            if (leftCommand) return 1;
            else return 0;
        }
        if (connector.at(pos-1).out() == "||"){
            if (!leftCommand) return 1;
            else return 0;
        }
        cout<< "Terribly wrong"<<endl;
        return false;
    }
};
/*int main(){
    CommandLine test = CommandLine(" [ src ");
    Execute ex;
    ex.exe(test);
}*/
#endif
