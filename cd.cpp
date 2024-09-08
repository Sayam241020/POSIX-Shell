#include<bits/stdc++.h>
#include<unistd.h>
#include<pwd.h>
#include <sys/wait.h>
using namespace std;
extern char cwd[PATH_MAX];
extern string currentDir;
extern string previousDir;
extern string  home_dir;
extern char cur_dir[PATH_MAX];
extern char pre_dir[PATH_MAX];

void cd_func(vector<char*>args) {
    int n=args.size()-1;
    if (n > 2) {
        cout<< "Invalid Arguments for cd"<<"\n";
        return;
    }
    string targetPath;
    if(n==1 || (n==2 && strcmp(args[1],"~")==0) ) 
      {
        int flag = chdir(cwd);
        if(flag==-1) 
        {
            perror("Error");
            return;
        }
        currentDir = home_dir;
        return ;
      }
    else if(n==2 && strcmp(args[1],"-")!=0){
        int flag = chdir(args[1]);
        if(flag==-1){
            perror("No Such Directory or File exists");
            return;
        }
        previousDir = currentDir;
        strcpy(pre_dir,cur_dir);
        getcwd(cur_dir,PATH_MAX);
        currentDir = cur_dir;
        return;
    }

    else{
        int flag = chdir(previousDir.c_str());
        if (flag == -1) {
            perror("No such directory or file exists");
            return;
        }
        // Swap current and previous directories
        string temp = currentDir;
        currentDir = previousDir;
        previousDir = temp;
        getcwd(cur_dir, PATH_MAX);

    }
}