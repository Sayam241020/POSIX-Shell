#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <cstring>

using namespace std;
extern string  home_dir;
extern string currentDir;
extern struct passwd *password;
extern char name[256];


int foreGroundProcess(vector<string>& args) {
    vector<char*> argv;
    for (const auto& arg : args) {
        argv.push_back(const_cast<char*>(arg.c_str()));
    }
    argv.push_back(nullptr);

    pid_t pid = fork();
    int status;

    if (pid == 0) { 
        if (execvp(argv[0], argv.data()) == -1) {
            perror("Error executing command");
            exit(EXIT_FAILURE);
        }
    } 
    else if (pid < 0) { 
        perror("Fork failed");
        return -1;
    } 
    else { 
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        
        if (WIFEXITED(status)) {
            cout << "Foreground process exited with status " << WEXITSTATUS(status) << endl;
        } else if (WIFSIGNALED(status)) {
            cout << "Foreground process killed by signal " << WTERMSIG(status) << endl;
        }
    }
    
    return 1;
}

int backGroundProcess(vector<string>& args) {
    vector<char*> argv;
    for (const auto& arg : args) {
        argv.push_back(const_cast<char*>(arg.c_str()));
    }
    argv.push_back(nullptr);

    pid_t pid = fork();

    if (pid == 0) { 
        pid_t childpid = getpid();
        cout << "Background process started with PID: " << childpid << endl;
        
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        if (execvp(argv[0], argv.data()) == -1) {
            perror("Error executing command");
        }
        exit(EXIT_FAILURE);
    } 
    else if (pid < 0) {
        perror("Fork failed");
    }
    return 1;
}

int background_foreground_call(vector<string>& args) {
    if (args.back() == "&") { 
        args.pop_back();
        return backGroundProcess(args);
    } 
    else {  
        return foreGroundProcess(args);
    }
}
