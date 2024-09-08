#include<bits/stdc++.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>

using namespace std;

void printProcessInfo(pid_t pid) {
    char procPath[256], statPath[256], exePath[256];
    sprintf(procPath, "/proc/%d", pid);
    sprintf(statPath, "/proc/%d/stat", pid);
    sprintf(exePath, "/proc/%d/exe", pid);

    // Reading process status from /proc/[pid]/stat
    ifstream statFile(statPath);
    if (!statFile) {
        cout << "Error: Process with PID " << pid << " does not exist." << endl;
        return;
    }

    string line;
    getline(statFile, line);
    statFile.close();

    // Tokenize the line
    istringstream iss(line);
    string comm, state;
    long rss;
    int field = 1;
    while (iss >> line) {
        if (field == 2) comm = line;  // Command name
        else if (field == 3) state = line;  // Process status
        else if (field == 24) rss = stol(line);  // Resident Set Size (memory)
        field++;
    }

    // Get the executable path
    char exeRealPath[PATH_MAX];
    ssize_t len = readlink(exePath, exeRealPath, sizeof(exeRealPath) - 1);
    if (len != -1) exeRealPath[len] = '\0';
    else strcpy(exeRealPath, "N/A");

    // Convert memory from pages to KB
    long pageSize = sysconf(_SC_PAGESIZE) / 1024;  // in KB
    long memory = rss * pageSize;  // in KB

    // Output the process information
    cout << "pid -- " << pid << endl;
    cout << "Process Status -- " << state << endl;
    cout << "memory -- " << memory << " KB" << endl;
    cout << "Executable Path -- " << exeRealPath << endl;
}

