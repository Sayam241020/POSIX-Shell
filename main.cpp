#include<bits/stdc++.h>
#include<unistd.h>
#include<pwd.h>
#include <fcntl.h>
#include <sys/wait.h>

using namespace std;
char input[4096];
char cur_dir[PATH_MAX];
string  home_dir;
char cwd[PATH_MAX];
char pre_dir[PATH_MAX];
char name[256];
struct passwd *password = getpwuid(getuid());
string currentDir;
string previousDir;

#include "header.h"

int main(){
    getcwd(cwd, sizeof(cwd));
    home_dir = cwd;
    getcwd(cur_dir,PATH_MAX);
    getcwd(pre_dir,PATH_MAX);
    gethostname(name,sizeof(name));
    getcwd(cur_dir,sizeof(cur_dir));
    currentDir = cur_dir;
    previousDir = cur_dir;

    while (true) {
        display();
        cin.getline(input, 1024);
        executeCommand((char*)"history_update");
        char* inputCopy = strdup(input);
        char* command = strtok(inputCopy, ";");

        while (command != nullptr) {
            command = trim(command);
            if (strlen(command) > 0) {
                string c = command;
                int found= c.find("|");
                if(found!=string::npos){
                    vector<char*>argc=execute_piped_commands(command);
                    vector<vector<char*>>commands;
                    for(int i=0; i<argc.size();i++){
                        vector<char*>t=token(argc[i]," ");
                        commands.push_back(t);
                    }
                    int aab = execute_pipeline(commands,commands.size());
                }
                else{
                executeCommand(command);
                }
            }

            command = strtok(nullptr, ";");
        }
        free(inputCopy);
    }
    
    return 0;
}