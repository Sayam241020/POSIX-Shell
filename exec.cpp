#include<bits/stdc++.h>
#include<unistd.h>
#include<pwd.h>
#include <fcntl.h>
#include <sys/wait.h>
using namespace std;

extern string  home_dir;
extern string currentDir;
extern string previousDir;
extern char cwd[PATH_MAX];
extern char pre_dir[PATH_MAX];
extern char cur_dir[PATH_MAX];
extern char input[4096];

void executeCommand(char* cmd) {
    vector<char*> args = token(cmd, " ");
    string c = cmd;
    int f1= c.find(">");
    int f2= c.find("<");

    if (args.empty()) return;

    else if(f1!=string::npos || f2!=string::npos){
        execute_command_with_redirection(args,home_dir);
        return ;
        }

    else if (strcmp(args[0], "cd") == 0) {
        cd_func(args);
        return ;
    } 
    else if (strcmp(args[0], "history_update") == 0) {
        update_history("history.txt",input);
        return;
        }

    else if (strcmp(args[0], "pwd") == 0) {
        pwd(args.size()-1);
        return ;
    } 
    else if (strcmp(args[0], "history") == 0) {
        if(args.size()==2){
            print_history(args,"history.txt");
            return ;
        }
        if(args.size()>3 || stoi(args[1])<0){
            perror("Invalid Arguments with History");
            return ;
        }
        print_history(args,"history.txt");
        return ;
    } 

    else if (strcmp(args[0], "pinfo") == 0) {
        pid_t pid;
        if (args.size()>3){
            perror("Invalid Arguments with Pinfo");
            return ;
        }
        if (args.size() == 2) 
            pid = getpid();
        else 
            pid = stoi(args[1]);

        printProcessInfo(pid);
        return ;
        }




    else if (strcmp(args[0], "ls") == 0) {
        bool showall = false;
        bool showlong = false;
        vector<string> paths;
        for (int  i = 1; i < args.size()-1; i++) {
            if (strcmp(args[i], "-a") == 0) {
            showall = true;
        } else if (strcmp(args[i], "-l") == 0) {
            showlong = true;
        }
        else if ((strcmp(args[i], "-al") == 0) || (strcmp(args[i], "-la") == 0)) {
            showlong = true;
            showall = true;
        } 
         else {
            paths.push_back(args[i]);
        }
        }
        lsCommand(paths, showall, showlong);
        return ;
    } 

    else if (strcmp(args[0], "search") == 0) {
        if(args.size()>3){
            cout<<"Invalid Arguments with search"<<"\n";
            return;
        }
        if (searchInCurrentDirectory(args[1])){
            cout<<"true"<<endl;
        }
        else cout<<"false"<<endl;
        return ;
    }
    else if (strcmp(args[0], "echo") == 0) {
        echo(input);
    }
    else{
        vector<string> stringArgs(args.begin(), args.end()-1);
        background_foreground_call(stringArgs);
        return;
    }


    //else if (strcmp(args[0], "echo") == 0) {
    //     echo(args);
    //  } 
     //else {
    //     bool background = false;
    //     char* ampersand = strchr(cmd, '&');
    //     if (ampersand) {
    //         background = true;
    //         *ampersand = '\0'; // Replace '&' with null terminator
    //     }
    //     executeExternalCommand(args, background);
    // }
}
