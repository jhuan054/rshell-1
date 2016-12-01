# include <iostream>
using namespace std;
# include "CommandLine.cpp"
# include "Execute.cpp"
//# include "Commands.cpp"
int main(){
    bool t = 1;
    
    do {
        char hostname[60];
        gethostname(hostname,60);
        cout << getlogin();
        cout << "@";
        cout << hostname;
	cout << "[ ";
	cout << getenv("PWD");
	cout << " ]";
        cout << "$ ";
        string readline;
        getline(cin,readline);
        CommandLine line = CommandLine(readline);
        Pchecker pcommands =  Pchecker();
        pcommands.process(line);
        vector<Pexecute> pexecute;
        for (int i = 0; i < pcommands.commandSize(); i++){
            Pexecute teo = Pexecute();
            pexecute.push_back(teo);
        }
        for (int i = 0; i < pcommands.commandSize(); i++){
            if (i == 0){
            
                pexecute.at(0).exe(pcommands.commandAt(0));
                t = pexecute.at(0).exitevl();
            } 
            else{
                if (pexecute.at(i).whetherNext(pexecute, pcommands.connectorOut(),i)){
                    pexecute.at(i).exe(pcommands.commandAt(i));
                    t = pexecute.at(i).exitevl();
                } 
            }
        }   
    }while (t); 
}

