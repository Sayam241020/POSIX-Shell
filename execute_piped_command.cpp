#include<bits/stdc++.h>
#include<unistd.h>
#include<pwd.h>
#include <fcntl.h>
#include <sys/wait.h>
using namespace std;

vector<char*>execute_piped_commands(char *line){
  vector<char*>commands;
  char *command;

  command = strtok(line, "|");
  while (command) {
        while (isspace((unsigned char)*command)) command++;

        char* end = command + strlen(command) - 1;
        while (end > command && isspace((unsigned char)*end)) end--;
        *(end + 1) = '\0';
        if (*command != '\0') {
            commands.push_back(command);
        }

        command = strtok(NULL, "|");
    }
  return commands;
}

void execute_command(vector<char*>args, int input_fd, int output_fd) {
  pid_t pid;
  pid_t wpid;
  int status;

  if ((pid = fork()) == 0) {
    if (input_fd != STDIN_FILENO) {
      dup2(input_fd, STDIN_FILENO);
      close(input_fd);
    }

    if (output_fd != STDOUT_FILENO) {
      dup2(output_fd, STDOUT_FILENO);
      close(output_fd);
    }

    if (execvp(args[0], args.data()) == -1) {
      perror("execvp");
      exit(EXIT_FAILURE);
    }
  } else if (pid < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  } else {
    wpid = waitpid(pid, &status, 0);
  }
}


int execute_pipeline(vector<vector<char*>> commands, int n) {
    int num_commands = commands.size();
    if (num_commands == 0) return 1;

    int pipefds[2];
    int input_fd = STDIN_FILENO;

    for (int i = 0; i < num_commands; ++i) {
        if (i < num_commands - 1) {
            if (pipe(pipefds) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }
        int output_fd = (i == num_commands - 1) ? STDOUT_FILENO : pipefds[1];
        execute_command(commands[i], input_fd, output_fd);
        if (input_fd != STDIN_FILENO) close(input_fd);
        if (output_fd != STDOUT_FILENO) close(output_fd);
        input_fd = pipefds[0];
    }
    if (input_fd != STDIN_FILENO) {
        close(input_fd);}
    return 1;
}