# include <iostream>
using namespace std;
# include "CommandLine.cpp"
# include "Execute.cpp"
# include "Commands.cpp"
int main(){
    bool t = 1;
    
    do {
        char hostname[60];
        gethostname(hostname,60);
        cout << getlogin();
        cout << "@";
        cout << hostname;
        cout << "$ ";
        string readline;
        getline(cin,readline);
        CommandLine line = CommandLine(readline);
        Commands commands =  Commands();
        commands.exe(line);
        vector<Execute> execute;
        for (int i = 0; i < commands.commandSize(); i++){
            Execute teo = Execute();
            execute.push_back(teo);
        }
        for (int i = 0; i < commands.commandSize(); i++){
            if (i == 0){
            
                execute.at(0).exe(commands.commandAt(0));
                t = execute.at(0).exitevl();
            } 
            else{
                if (execute.at(i).whetherNext(execute, commands.connectorOut(),i)){
                    execute.at(i).exe(commands.commandAt(i));
                    t = execute.at(i).exitevl();
                } 
            }
        }   
    }while (t); 
}

