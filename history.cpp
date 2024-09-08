#include<bits/stdc++.h>
#include<unistd.h>
#include<pwd.h>
#include <fcntl.h>
#include <sys/wait.h>
using namespace std;
extern string home_dir;

void update_history(const char *filename, const std::string &newLine) {
    int MAX_LINES = 20;
    int BUFFER_SIZE = 4096;
    string file = home_dir+"/history.txt";
    int fd = openat(AT_FDCWD, file.c_str(), O_RDWR | O_APPEND | O_CREAT, 00600);
    if (fd < 0) {
        perror("Failed to open file");
        return;
    }

    vector<std::string> lines;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    string currentLine;

    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        for (ssize_t i = 0; i < bytesRead; ++i) {
            if (buffer[i] == '\n') {
                lines.push_back(currentLine);
                currentLine.clear();
            } else {
                currentLine += buffer[i];
            }
        }
    }

    if (!currentLine.empty()) {
        lines.push_back(currentLine);
    }

    lines.insert(lines.begin(), newLine);

    if (lines.size() > MAX_LINES) {
        lines.pop_back();
    }

    // Rewind the file descriptor to the beginning
    if (lseek(fd, 0, SEEK_SET) < 0) {
        perror("Failed to seek to start of file");
        close(fd);
        return;
    }

    // Truncate the file to clear its content
    if (ftruncate(fd, 0) < 0) {
        perror("Failed to truncate file");
        close(fd);
        return;
    }

    // Write the updated lines back to the file
    for (const auto &line : lines) {
        std::string toWrite = line + "\n";
        if (write(fd, toWrite.c_str(), toWrite.size()) < 0) {
            perror("Failed to write to file");
            close(fd);
            return;
        }
    }

    // Close the file
    close(fd);
}

void print_history(vector<char*>args,const char* filename){
    string file = home_dir+"/history.txt";
    int fd = openat(AT_FDCWD, file.c_str(), O_RDWR | O_APPEND | O_CREAT, 00600);
    if (fd < 0) {
        perror("Failed to open file");
        return;
    }
    int BUFFER_SIZE = 4096;
    vector<std::string> lines;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    string currentLine;

    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        for (ssize_t i = 0; i < bytesRead; ++i) {
            if (buffer[i] == '\n') {
                lines.push_back(currentLine);
                currentLine.clear();
            } else {
                currentLine += buffer[i];
            }
        }
    }

    if (!currentLine.empty()) {
        lines.push_back(currentLine);
    }
    int x;
    if(args.size()==2) x=10;
    else x=stoi(args[1]);
    for(int i=0; i<min(x, static_cast<int>(lines.size()));i++){
         cout<<lines[i]<<"\n";
    }

    // Rewind the file descriptor to the beginning
    if (lseek(fd, 0, SEEK_SET) < 0) {
        perror("Failed to seek to start of file");
        close(fd);
        return;
    }
    close(fd);
}