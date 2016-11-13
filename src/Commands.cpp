# include <iostream>
# include <cstdlib>
# include <cmath>
# include <vector>
# include <algorithm> 
# include <fstream>
# include "CommandLine.cpp"
# include <string>

using namespace std;

class Commands : public CommandLine
{
    protected:
    vector<CommandLine> command;
    vector<CommandLine> connector;

    public:
    void exe(CommandLine commandline)
    {
        vector<unsigned> connector;
        string add;
        string needToParse = commandline.out();
        string::iterator it = needToParse.begin();
        for (unsigned i = 0; i < needToParse.size(); i++)
        {
            if ((*(it + i) == '&' && *(it + i +1) == '&') || 
            (*(it + i) == '|' && *(it + i +1) == '|')
            || *(it + i) == ';' || *(it + i) == '#'|| *(it + i) == '('|| *(it + i) == ')')
            { 
                connector.push_back(i);
            }
        }
        if (connector.size() == 0) 
        {
            add = needToParse;
            this->command.push_back(CommandLine(add));
        }
        for (unsigned i = 0; i < connector.size(); i++)
        {
            
            if (i == 0 && *it != '#')
            {
                add = needToParse.substr(0, connector.at(0));
                this->command.push_back(CommandLine(add));
            }
            
            if (*(it+connector.at(i)) == '#') return;
    
            if (*(it+connector.at(i)) == '|')
            {
                add = needToParse.substr(connector.at(i),2);
                this->connector.push_back(CommandLine(add));
                if (i < connector.size() - 1){
                   add = needToParse.substr(connector.at(i)+2, 
                   connector.at(i+1)-connector.at(i)-2);
                   this->command.push_back(CommandLine(add));
                }
                else {
                    add = needToParse.substr(connector.at(i)+2,
                    needToParse.size() - connector.at(i));
                    this->command.push_back(CommandLine(add));
                }
            }
            
            if (*(it+connector.at(i)) == '&'){
                add = needToParse.substr(connector.at(i),2);
                this->connector.push_back(CommandLine(add));
                if (i < connector.size() - 1){
                   add = needToParse.substr(connector.at(i) + 2, 
                   connector.at(i + 1) - connector.at(i) - 2);
                   this->command.push_back(CommandLine(add));
                }
                else {
                    add = needToParse.substr(connector.at(i) + 2, 
                    needToParse.size() - connector.at(i) - 2);
                    this->command.push_back(CommandLine(add));
                }
            }
            
            if (*(it+connector.at(i)) == ';')
            {
                add = needToParse.substr(connector.at(i),1);
                this->connector.push_back( CommandLine(add));
                if (i < connector.size() - 1)
                {
                   add = needToParse.substr(connector.at(i)+1, 
                   connector.at(i+1)-connector.at(i)-1);
                   this->command.push_back( CommandLine(add));
                }
                else 
                {
                    add = needToParse.substr(connector.at(i)+1, 
                    needToParse.size() - connector.at(i)-1);
                    this->command.push_back(CommandLine(add));
                }
            }
            
            if (*(it+connector.at(i)) == '(')
            {cout << "OPERNER DETECTED";
                add = needToParse.substr(connector.at(i),1);
                this->connector.push_back( CommandLine(add));
                if (i < connector.size() - 1)
                {
                   add = needToParse.substr(connector.at(i)+1, 
                   connector.at(i+1)-connector.at(i)-1);
                   this->command.push_back( CommandLine(add));
                }
                else 
                {
                    add = needToParse.substr(connector.at(i)+1, 
                    needToParse.size() - connector.at(i)-1);
                    this->command.push_back(CommandLine(add));
                }
            }
            
            if (*(it+connector.at(i)) == ')')
            {cout << "CLOSER DETECTED";
                add = needToParse.substr(connector.at(i),1);
                this->connector.push_back( CommandLine(add));
                if (i < connector.size() - 1)
                {
                   add = needToParse.substr(connector.at(i)+1, 
                   connector.at(i+1)-connector.at(i)-1);
                   this->command.push_back( CommandLine(add));
                }
                else 
                {
                    add = needToParse.substr(connector.at(i)+1, 
                    needToParse.size() - connector.at(i)-1);
                    this->command.push_back(CommandLine(add));
                }
            }
        }
        
    }
    
    int commandSize(){
        return this->command.size();
    }
    
    CommandLine commandAt(int i){
        return this->command.at(i);
    }
    
    vector<CommandLine> connectorOut(){
        return this->connector;
    }
};