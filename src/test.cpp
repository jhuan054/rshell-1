# include<iostream>
# include<unistd.h>
# include <string>
using namespace std;
int test(){
    string s;
    string::iterator it;
    s = "absd||fsfd";
    exit(0);
    it = s.begin();
    //if (*it == 'a') return;
    return 0;
}
int main(){
    cout<<test();
    if (test() == 1)
    cout<< 1;
}