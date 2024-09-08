#include<bits/stdc++.h>
#include<unistd.h>
#include<pwd.h>
#include <sys/wait.h>
using namespace std;

void pwd(int argv)
{
    if(argv>1)
    {
        perror("Invalid Arguments for pwd");
        return;
    }
    char Pwd[PATH_MAX];
    getcwd(Pwd,PATH_MAX);
    if(Pwd!=nullptr)
    {
        
        cout<<Pwd<<endl;
    }
    else{
        perror("pwd");
    }
    return ;
}