// #ifndef FUNCTION_H
// #define FUNCTION_H


// void display()
// void echo(vector<char*>args)
// void executeCommand(char* cmd)
// vector<char*>execute_piped_commands(char *line)
// void execute_command(vector<char*>args, int input_fd, int output_fd)
// int execute_pipeline(vector<vector<char*>> commands, int n)
// int foreGroundProcess(vector<string>& args)
// int backGroundProcess(vector<string>& args)
// int background_foreground_call(vector<string>& args)
// void update_history(const char *filename, const std::string &newLine)
// void print_history(vector<char*>args,const char* filename)
// void execute_command_with_redirection(vector<char*> args,string &home_dir)
// void listDirectoryContents(const string &directoryPath, bool showHidden, bool longFormat)
// void lsCommand(vector<string> paths,bool showHidden, bool longFormat)
// void printProcessInfo(pid_t pid)
// void pwd(int argv)
// bool searchInDirectory(const string& directory, const string& target)
// bool searchInCurrentDirectory(const string& target)
// vector<char*> token(char* str, const char* delimiter)
// char* trim(char* str)
// void cd_func(vector<char*>args)

// #endif

#include "execute_piped_command.cpp"
#include "search.cpp"
#include "foreground_background.cpp"
#include "cd.cpp"    
#include "history.cpp"                
#include "token.cpp"
#include "display.cpp"
#include "echo.cpp" 
#include "io_redirection.cpp"        
#include "pinfo.cpp"
#include "ls.cpp"                      
#include "pwd.cpp"
#include "exec.cpp"     


