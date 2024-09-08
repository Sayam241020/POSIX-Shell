#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <cstring>
#include <string>
#include <sys/stat.h>
#include <dirent.h>

using namespace std;

// Function to search for a file or directory in a given directory
bool searchInDirectory(const string& directory, const string& target) {
    DIR *dir = opendir(directory.c_str());
    if (dir == nullptr) {
        perror("Error: Unable to open directory");
        return false;
    }

    struct dirent *entry;
    bool found = false;

    while ((entry = readdir(dir)) != nullptr) {
        // Skip "." and ".."
        if (entry->d_type == DT_DIR && (string(entry->d_name) == "." || string(entry->d_name) == "..")) continue;

        // Check if the current entry matches the search target
        if (string(entry->d_name) == target) {
            found = true;
            break;
        }
    }

    closedir(dir);
    return found;
}

// Function to search for a file or directory in the current directory and its immediate subdirectories
bool searchInCurrentDirectory(const string& target) {
    char currentPath[PATH_MAX];
    if (getcwd(currentPath, sizeof(currentPath)) == nullptr) {
        perror("Error: Unable to get current working directory");
        return false;
    }

    // First, search in the current directory
    if (searchInDirectory(currentPath, target)) {
        return true;
    }

    // Then, search in immediate subdirectories
    DIR *dir = opendir(currentPath);
    if (dir == nullptr) {
        perror("Error: Unable to open directory");
        return false;
    }

    struct dirent *entry;
    bool found = false;

    while ((entry = readdir(dir)) != nullptr) {
        string name = entry->d_name;

        // Skip "." and ".."
        if (entry->d_type == DT_DIR && (name == "." || name == "..")) continue;

        // Only process subdirectories at the immediate level
        if (entry->d_type == DT_DIR) {
            string newPath = string(currentPath) + "/" + name;

            // Search for the target in the subdirectory
            if (searchInDirectory(newPath, target)) {
                found = true;
                break;
            }
        }
    }

    closedir(dir);
    return found;
}

// int main(int argc, char *argv[]) {
//     if (argc != 2) {
//         cout << "Usage: " << argv[0] << " <file_or_directory_name>" << endl;
//         return 1;
//     }

//     string target = argv[1];

//     if (searchInCurrentDirectory(target)) {
//         cout << "True" << endl;
//     } else {
//         cout << "False" << endl;
//     }

//     return 0;
// }
