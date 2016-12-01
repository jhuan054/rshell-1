# include <iostream>
# include <cstdlib>
# include <cmath>
# include <vector>
# include <algorithm> 
# include <fstream>
# include "CommandLine.cpp"
# include <string>

using namespace std;
class Pchecker; 
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
            || *(it + i) == ';' || *(it + i) == '#')//|| *(it + i) == '('|| *(it + i) == ')')
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
                //cout<<";1"<<add<<endl;
                this->connector.push_back( CommandLine(add));
                if (i < connector.size() - 1)
                {
                   add = needToParse.substr(connector.at(i)+1, 
                   connector.at(i+1)-connector.at(i)-1);
                            // cout<<";2"<<add<<endl;
                   this->command.push_back( CommandLine(add));
                }
                else 
                {
                    //cout<<needToParse.size()<<" "<<connector.at(i)<<endl;
                    add = needToParse.substr(connector.at(i)+1, 
                    needToParse.size() - connector.at(i)-1);
                              //cout<<";3"<<add<<endl;
                    /*if(add.length() != 0)
                    {
                    this->command.push_back(CommandLine(add));
                    }*/
                    
                }
            }
            
        
        }
                        // outputting vecotrs -------------------------------------------------------------
                /*for(int i = 0; i < command.size();i++)
                {
                    cout << " DIP " <<command.at(i).out()<<endl;
                     //exec()
                }
                cout << " FIN "<<endl;
                for(int i = 0; i < connector.size();i++)
                {
                    cout << this->connector.at(i).out()<<endl;
                     //exec()
                }
                cout << " FIN "<<endl;*/
        
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





//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Pchecker{     
    protected:
    vector<CommandLine> command;// put in command
    vector<CommandLine> connector;
  //  vector<CommandLine> paren;

    public:
   
            
            
            
          /*  Pchecker(CommandLine commandline)
            {
                 int start = Openfinder(0,commandline);
                 int end = end_finder(start+1,commanline);
                 string a = commandline.substr(start, start - end)
                 Commandline temp = Commandline(a);
                 temp.exe(temp);
                 command.push_back(commandline.substr(0,end));
                 string b = commandline.substr(end);
                 CommandLine z = CommandLine(z);
                 z.exe();
                 
            }*/
    void exe(CommandLine commandline)
    {
        //cout<<"exe  "<<commandline.out()<<endl;
        vector<unsigned> connector;
        string add;
        string needToParse = commandline.out();
        string::iterator it = needToParse.begin();
        for (unsigned i = 0; i < needToParse.size(); i++)
        {
            if ((*(it + i) == '&' && *(it + i +1) == '&') || 
            (*(it + i) == '|' && *(it + i +1) == '|')
            || *(it + i) == ';' || *(it + i) == '#')//|| *(it + i) == '('|| *(it + i) == ')')
            { 
                connector.push_back(i);
            }
        }
        if (connector.size() == 0) 
        {
            add = needToParse;
            //cout<<add<<endl;
            this->command.push_back(CommandLine(add));
        }
        for (unsigned i = 0; i < connector.size(); i++)
        {
            
            if (i == 0 && *it != '#')
            {
                add = needToParse.substr(0, connector.at(0));
               // cout<<add<<endl;
                //cout<<add.length()<<endl;
                if(add != " " && add != "||" && add != "#" && add != "&&" && add.length() != 0 && add != ";")
                        {
                        this->command.push_back(CommandLine(add));
                        //cout<<"test"<<add<<endl;
                        }
            }
            
            if (*(it+connector.at(i)) == '#') return;
    
            if (*(it+connector.at(i)) == '|')
            {
                add = needToParse.substr(connector.at(i),2);
                //cout<<add<<endl;
                this->connector.push_back(CommandLine(add));
                if (i < connector.size() - 1){
                   add = needToParse.substr(connector.at(i)+2, 
                   connector.at(i+1)-connector.at(i)-2);
                   //cout<<add<<endl;
                   if(add != " " && add != "||" && add != "#" && add != "&&" && add.length() != 0 && add != ";")
                        {
                        this->command.push_back(CommandLine(add));
                       // cout<<add<<endl;
                        }
                }
                else {
                    add = needToParse.substr(connector.at(i)+2,
                    needToParse.size() - connector.at(i));
                    //cout<<add<<endl;
                    if(add != " " && add != "||" && add != "#" && add != "&&" && add.length() != 0 && add != ";")
                        {
                        this->command.push_back(CommandLine(add));
                        //cout<<add<<endl;
                        }
                }
            }
            
            if (*(it+connector.at(i)) == '&'){
                add = needToParse.substr(connector.at(i),2);
                //cout<<add<<endl;
                this->connector.push_back(CommandLine(add));
                if (i < connector.size() - 1){
                   add = needToParse.substr(connector.at(i) + 2, 
                   connector.at(i + 1) - connector.at(i) - 2);
                   //cout<<add<<endl;
                    if(add != " " && add != "||" && add != "#" && add != "&&" && add.length() != 0 && add != ";")
                        {
                        this->command.push_back(CommandLine(add));
                        //cout<<add<<endl;
                        }
                }
                else {
                    add = needToParse.substr(connector.at(i) + 2, 
                    needToParse.size() - connector.at(i) - 2);
                    //cout<<add<<endl;
                    if(add != " " && add != "||" && add != "#" && add != "&&" && add.length() != 0 && add != ";")
                        {
                        this->command.push_back(CommandLine(add));
                        //cout<<add<<endl;
                        }
                }
            }
            
            if (*(it+connector.at(i)) == ';')
            {
                add = needToParse.substr(connector.at(i),1);
                //cout<<add<<endl;
                this->connector.push_back( CommandLine(add));
                if (i < connector.size() - 1)
                {
                   add = needToParse.substr(connector.at(i)+1, 
                   connector.at(i+1)-connector.at(i)-1);
                   cout<<add<<endl;
                   //cout<< "hhhhhh"<< add <<endl;
                    if (add != " " && add != "||" && add != "#" && add != "&&" && add.length() != 0 && add != ";")
                    {
                        //cout<<"add = echo"<<endl;
                        this->command.push_back(CommandLine(add));
                        //cout<<add<<endl;
                    }
                }
                else 
                {
                    add = needToParse.substr(connector.at(i)+1, 
                    needToParse.size() - connector.at(i)-1);
                    //cout<<add<<endl;
                   if(add.length() != 0)// || add != " ")
                    {
                        //cout<< " hrokydork" << add<<endl;
                        if(add != " " && add != "||" && add != "#" && add != "&&" && add.length() != 0 && add != ";")
                        {
                        this->command.push_back(CommandLine(add));
                       // cout<<add<<endl;
                        }
                    }
                }
            }
            
        
        }
                                // outputting vecotrs -------------------------------------------------------------
               /* for(int i = 0; i < command.size();i++)
                {
                    cout << " DIP " <<command.at(i).out()<<endl;
                     //exec()
                }
                cout << " FIN "<<endl;
                for(int i = 0; i < connector.size();i++)
                {
                    cout << this->connector.at(i).out()<<endl;
                     //exec()
                }
                cout << " FIN "<<endl;*/
        
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
    
        int Openfinder(int from, CommandLine commandline)
        {string bleh = commandline.out();
       // cout <<"in opens"<<endl;
             for(unsigned int i = from; i< bleh.length();i++)
            {
                
                if(bleh.at(i)== '(')
                {
                   return i;
                }
            }
       //     cout <<"closing opens"<<endl;
            return -1;
        }
        int end_finder(int from, CommandLine commandline)
        {
            int count = 1;
         //   cout <<"in fins"<<endl;
            for(unsigned int i = from; i< commandline.out().size();i++)
            {
                if(commandline.out().at(i)== '(')
                {
                   count++;
                }
                if(commandline.out().at(i)== ')')
                {
                   count--;
                   if(count == 0)
                   {
                       return i;
                   }
                }
            }
         //   cout <<"fins finds"<<endl;
            return -1;
        }
        bool TooLittle(CommandLine commandline)
        {
            int count = 0;
         //   cout <<"in fins"<<endl;
            for(unsigned int i = 0; i< commandline.out().size();i++)
            {
                if(commandline.out().at(i)== '(')
                {
                   count++;
                }
                if(commandline.out().at(i)== ')')
                {
                   count--;
                  
                }
            }
         //   cout <<"fins finds"<<endl;
         if(count == 0)
            {return false;}
            
            return true;
        }
        
     void process(CommandLine commandline)
            {
                 int start = Openfinder(0,commandline);
                 int end = end_finder(start+1,commandline);   
                 vector<int> starts;
                 vector<int> distance;
                 string whole = commandline.out();
                int a = 0;
                int b = 0;
                int d = 0;
                a = Openfinder(a+d, commandline);
                
                while(a != -1)
                {
                
                 b = end_finder(a+1, commandline);
                starts.push_back(a);
                d = b-a;
                distance.push_back(d);
                a = Openfinder(a+d, commandline);//right?
                    
                }
                if(start == -1 && end == -1)
                {
                   this->exe(commandline); 
                }
                else if(start != -1 && end == -1)
                {
                    cout<< "MISSING CLOSING PARENTHESES"<<endl;
                }
                else if(start == -1 && end != -1)
                {
                    cout<< "MISSING OPENING PARENTHESIS"<<endl;
                }
                else if(TooLittle(commandline))
                {
                    cout <<"WRONG AMOUNT OF PARENTHESES"<<endl;
                }
                else
                {
               // cout << "PWOERNWIN" << endl;
                int below = 0;
                string temp = whole;
                
                //------------------------------
                /*
                cout<< "rinting starts location"<<endl;
                for(int i = 0; i < starts.size();i++)
                {cout<<starts.at(i)<<endl;}
                cout<<"finished"<<endl;*/
                //--------------------
                for(unsigned int i = 0; i < starts.size();i++)
                {
                     temp = whole.substr(below, starts.at(i)-below);
                     //cout << whole<<endl;
                      //cout <<"OWPEO"<< temp.substr(0,1) << endl;
                    if(whole.substr(0,1)== "(" && below == 0)
                     {
                         
                         command.push_back(whole.substr(1, distance.at(0)-1));
                        below = starts.at(i)+distance.at(i)+1;
                        
                     }
                     else{
                     if(temp.length() != 0) 
                     {
                  //   cout << "DEMONSTRATE" << temp << "EDEMONSTRATE"<<endl;
                    
                    this->exe(temp);
                    
                     temp = whole.substr(starts.at(i), distance.at(i));
                //     cout<< "temp atm"<<temp<<endl;
                     temp = temp.substr(1);
                     temp = temp.substr(0,temp.length());
                     //cout << " HERE "<<temp  << endl;
                     command.push_back(temp);
                     below = starts.at(i)+distance.at(i)+1;
                   //  cout<<"nextChar" << whole.substr(below,starts.at(i))<<endl;
                   //  cout<<"wrongs " << whole.at(starts.at(i))<<endl;
                     }            
                     }
                }
                if(whole.substr(below).length() != 0)
                {
              //  cout << "WIEHRIH" <<whole.substr(below)<<endl;
                this->exe(whole.substr(below));
                }
                // outputting vecotrs -------------------------------------------------------------
                /*for(unsigned int i = 0; i < command.size();i++)
                {
                    cout << " COP " <<command.at(i).out()<<endl;
                     //exec()
                }
                cout << " FIN "<<endl;
                for(unsigned int i = 0; i < connector.size();i++)
                {
                    cout << connector.at(i).out()<<endl;
                     //exec()
                }
                cout << " FIN "<<endl;
                */
            }
       
        
        //something about no perentheses
            }
    

};

/*{
    CommandLine test = CommandLine( "  echo c|| echo d  || echo e #roepopso");  //"(echo a || echo b ); ( ( echo c&& echo d ) || echo e ) ; (echo f && echo g)");
    Pchecker ex = Pchecker();
    ex.process(test);
    Commands cmds;
    cmds.exe(CommandLine("echo a||echo b;"));
}*/

