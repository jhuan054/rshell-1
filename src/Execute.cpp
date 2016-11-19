
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
# include "Commands.cpp"
class Execute : public CommandLine
{
    protected:
    bool cont;
    bool exitShell; 
    
    public:
    Execute()
    {
        cont = true;
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
                    if (strcmp(tokens[pos-1], builtinCommand[3])==0) builtin.exe(command);
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


class Pexecute{
    protected:
    bool cont;
    bool exitShell;
    
    public:
    Pexecute()
    {
        cont = true;
        exitShell = true;
    }    
    
    void exe(CommandLine command){
        std::size_t leftParentheseFound = command.out().find("(");
        std::size_t rightParentheseFound = command.out().find(")");
        if ( leftParentheseFound == string::npos && rightParentheseFound == string::npos){
            Commands commands = Commands();
            commands.exe(command.out());
            vector<Execute> execute;
            for (int i = 0; i < commands.commandSize(); i++){
                Execute teo = Execute();
                execute.push_back(teo);
            }
            for (int i = 0; i < commands.commandSize(); i++){
                if (i == 0){
            
                    execute.at(0).exe(commands.commandAt(0));
                    this->exitShell = execute.at(0).exitevl();
                    if ( this->exitShell == false) return;
                } 
                else{
                    if (execute.at(i).whetherNext(execute, commands.connectorOut(),i)){
                        execute.at(i).exe(commands.commandAt(i));
                        this->exitShell = execute.at(i).exitevl();
                        if ( this->exitShell == false) return;
                    } 
                }
            } 
            if (commands.commandSize() == 1) this->cont = execute.at(commands.commandSize()-1).contevl();
            else{
                if (execute.at(commands.commandSize()-1).contevl() == true && commands.connectorOut().at(commands.commandSize() - 2).out() == "&&") this->cont = execute.at(commands.commandSize() - 2).contevl();
                else this->cont = execute.at(commands.commandSize()-1).contevl();
            }
        }
        else{
            Pchecker pcommands = Pchecker();
            pcommands.process(command.out());
            vector<Pexecute> pexecute;
            for (int i = 0; i < pcommands.commandSize(); i++){
                Pexecute teo = Pexecute();
                pexecute.push_back(teo);
            }
            for (int i = 0; i < pcommands.commandSize(); i++){
                if (i == 0){
            
                    pexecute.at(0).exe(pcommands.commandAt(0));
                    this->exitShell = pexecute.at(0).exitevl();
                    if ( this->exitShell == false) return;
                } 
                else{
                    if (pexecute.at(i).whetherNext(pexecute, pcommands.connectorOut(),i)){
                        pexecute.at(i).exe(pcommands.commandAt(i));
                        this->exitShell = pexecute.at(i).exitevl();
                        if ( this->exitShell == false) return;
                    } 
                }
            }  
            if (pcommands.commandSize() == 1) this->cont = pexecute.at(pcommands.commandSize()-1).contevl();
            else{
                if (pexecute.at(pcommands.commandSize()-1).contevl() == true && pcommands.connectorOut().at(pcommands.commandSize() - 2).out() == "&&") this->cont = pexecute.at(pcommands.commandSize() - 2).contevl();
                else this->cont = pexecute.at(pcommands.commandSize()-1).contevl();
            }            
        }
    }
    
    bool exitevl(){
        return this->exitShell;
    }
    
    bool contevl(){
        return this->cont;
    }
    
    bool whetherNext(vector<Pexecute> execute, vector<CommandLine> connector,int pos){
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
#endif
