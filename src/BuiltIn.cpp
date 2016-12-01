# ifndef Builtin_H
# define Builtin_H
# pragma GCC diagnostic ignored "-Wwrite-strings"
# include "CommandLine.cpp"
# define LSH_TOK_DELIM " \t\r\n\a"
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
    int num;
    
    public:
    BuiltIn()
    {
        num = 5;
    }
    
    vector<string> parse(string changePath){
               
                string changePathNew = "";
                //changePath = changePath + '/';
                string::iterator it = changePath.begin();
                if (*(it + changePath.size()-1) != '/') changePath = changePath + '/';
                it = changePath.begin();
                vector<unsigned> slash;
                vector<string> pathAtom;
                for (unsigned i = 0; i < changePath.size(); i++){
                    //cout<<(*(it+i) == '/')<<endl;
                    if (*(it+i) == '/') slash.push_back(i);
                    //if (*(it + i) == '.' && *(it + i +1) == '.') dot.push_back(i);
                }
                if (slash.size() == 0){ 
                    pathAtom.push_back(changePath);
                    return pathAtom;
                }
              
                if (slash.at(slash.size()-1) == (changePath.size()-1)){
                    for (unsigned i = 0; i < slash.size() ; i++){
                        if (i == 0){
                            string temp = changePath.substr(0, slash.at(0));
                            if (temp.length() != 0)
                            pathAtom.push_back(temp);
                        }
                        else{
                            string temp = changePath.substr(slash.at(i-1)+1, slash.at(i)-slash.at(i-1)-1);
                            pathAtom.push_back(temp);
                        }
                    }
                }
                else{
                    for (unsigned i = 0; i < slash.size(); i++){
                        if (i == 0){
                            string temp = changePath.substr(0, slash.at(0));
                            if (temp.length() != 0)
                            pathAtom.push_back(temp);
                        }
                        else if(i < slash.size()-1){
                            string temp = changePath.substr(slash.at(i)+1, slash.at(i+1)-slash.at(i)-1);
                            pathAtom.push_back(temp);
                        }
                        else{
                            string temp = changePath.substr(slash.at(i)+1, changePath.size()-slash.at(i)-1);
                            pathAtom.push_back(temp);
                        }
                    }
                }  
                return pathAtom;
    }
    
    string rshell_exit(char** arglist)
    {
        return "e";
    }
    
    string rshell_test(char** arglist)
    {
        int exist;
        struct stat sb;
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
    
    string rshell_cd(char** arglist){
        
        char *oldpwd = getenv("OLDPWD");
        char *pwd = getenv("PWD");
        if (arglist[1] == NULL) {
            setenv("OLDPWD",pwd,1);
            setenv("PWD",getenv("HOME"),1);
             char *home = getenv("HOME");
             if (chdir(home) != 0){
                 perror("rshell");
                setenv("OLDPWD",oldpwd,1);
                setenv("PWD",pwd,1);
                return "f";                
             };
        } else {
            if(string(arglist[1]) == "-"){
		
                setenv("OLDPWD",pwd,1);
                setenv("PWD",oldpwd,1);
                if (chdir(oldpwd) != 0) {
                perror("rshell");
                setenv("OLDPWD",oldpwd,1);
                setenv("PWD",pwd,1);
                return "f";
                } 
            }
            else if(string(arglist[1]) == "/"){
                setenv("OLDPWD",pwd,1);
                setenv("PWD","/",1);
                if (chdir(arglist[1]) != 0) {
                perror("rshell");
                setenv("OLDPWD",oldpwd,1);
                setenv("PWD",pwd,1);
                return "f";
                } 
            }
            else{

                vector<string> pwdVec = parse(string(pwd));
                vector<string> changePathVec = parse(string(arglist[1]));
                
                for (unsigned i = 0; i < changePathVec.size(); i++){
                    if (changePathVec.at(i) == "..") pwdVec.pop_back();
                    else pwdVec.push_back(changePathVec.at(i));
                }
                string newPwd = "/";
                for (unsigned i = 0; i < pwdVec.size(); i++){
                    newPwd = newPwd + pwdVec.at(i);
                    if (i < pwdVec.size() - 1)
                        newPwd = newPwd + '/';
                }
                setenv("OLDPWD",pwd,1);
                setenv("PWD",newPwd.c_str(),1);
                if (chdir(arglist[1]) != 0) {
                perror("rshell");
                setenv("OLDPWD",oldpwd,1);
                setenv("PWD",pwd,1);
                return "f";
            } 
            } 
            }
        
        return "s";
    }

    
    
    
    void exe(CommandLine command)
    {
        char* builtinCommand[]={
            "exit",
            "test",
            "[",
            "cd"//May be added later
        };
        
        
        char* arg;
        char* token;
        char* tokens[100]={NULL};
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
               else if (i == 3) this->line = rshell_cd(tokens);
            }
         }delete[] arg;
    }
    
    int num_evl()
    {
        return this->num;
    }

};

#endif
