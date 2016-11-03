# include <iostream>
using namespace std;
# include "CommandLine.cpp"
# include "Execute.cpp"
# include "Commands.cpp"
bool whetherNext(vector<Execute> execute, vector<CommandLine> connector,int pos); 
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
       // cout <<"before"<<endl;
        commands.exe(line);
        //cout<<"After"<<endl;
        vector<Execute> execute;
        //cout << commands->commandSize();
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
                if (whetherNext(execute, commands.connectorOut(),i)){
                    execute.at(i).exe(commands.commandAt(i));
                    t = execute.at(i).exitevl();
                } 
            }
        }   
    }while (t); 
}

bool whetherNext(vector<Execute> execute, vector<CommandLine> connector,int pos)
{
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