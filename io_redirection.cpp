#include<bits/stdc++.h>
#include<unistd.h>
#include<pwd.h>
#include <fcntl.h>
#include <sys/wait.h>
using namespace std;

void execute_command_with_redirection(vector<char*> args,string &home_dir) {
    int input_fd = STDIN_FILENO;
    int output_fd = STDOUT_FILENO;
    cout<<"hello"<<"\n";
    for (int i = 0; i < args.size(); ++i) {
        if (strcmp(args[i], "<") == 0) {
            // Input redirection
            string file = home_dir+args[i+1];
            input_fd = openat(AT_FDCWD, file.c_str(), O_RDWR | O_APPEND | O_CREAT, 00644);
            if (input_fd < 0) {
                perror("Input file error");
                return;
            }
            args.erase(args.begin() + i, args.begin() + i + 2);
            i--;
        } else if (strcmp(args[i], ">") == 0) {
            // Output redirection (overwrite)
            string file = home_dir+args[i+1];
            output_fd = openat(AT_FDCWD, file.c_str(), O_RDWR | O_APPEND | O_CREAT, 00600);
            if (output_fd < 0) {
                perror("Output file error");
                return;
            }
            args.erase(args.begin() + i, args.begin() + i + 2);
            i--;
        } else if (strcmp(args[i], ">>") == 0) {
            // Output redirection (append)
            string file = home_dir+args[i+1];
            output_fd = openat(AT_FDCWD, file.c_str(), O_RDWR | O_APPEND | O_CREAT, 00644);
            if (output_fd < 0) {
                perror("Output file error");
                return;
            }
            args.erase(args.begin() + i, args.begin() + i + 2);
            i--;
        }
    }

    // Fork and execute command
    // pid_t pid = fork();
    // if (pid == 0) {
        if (input_fd != STDIN_FILENO) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        if (output_fd != STDOUT_FILENO) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }
        execvp(args[0], args.data());
        perror("execvp");
        exit(EXIT_FAILURE);
    // } else if (pid < 0) {
    //     perror("fork");
    // } else {
    //     wait(nullptr);
    // }

    if (input_fd != STDIN_FILENO) close(input_fd);
    if (output_fd != STDOUT_FILENO) close(output_fd);
}
