#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <grp.h>

using namespace std;

void listDirectoryContents(const string &directoryPath, bool showHidden, bool longFormat) {
    DIR *directory;
    struct dirent *entry;
    struct stat fileStat;

    directory = opendir(directoryPath.empty() ? "." : directoryPath.c_str());
    if (directory == nullptr) {
        cerr << "Cannot access " << directoryPath << ": No such directory" << endl;
        return;
    }

    while ((entry = readdir(directory)) != nullptr) {
        if (!showHidden && entry->d_name[0] == '.') continue;

        string fullPath = directoryPath + "/" + entry->d_name;
        if (stat(fullPath.c_str(), &fileStat) < 0) {
            perror("stat");
            continue;
        }

        if (longFormat) {
            cout << ((S_ISDIR(fileStat.st_mode)) ? 'd' : '-');
            cout << ((fileStat.st_mode & S_IRUSR) ? 'r' : '-');
            cout << ((fileStat.st_mode & S_IWUSR) ? 'w' : '-');
            cout << ((fileStat.st_mode & S_IXUSR) ? 'x' : '-');
            cout << ((fileStat.st_mode & S_IRGRP) ? 'r' : '-');
            cout << ((fileStat.st_mode & S_IWGRP) ? 'w' : '-');
            cout << ((fileStat.st_mode & S_IXGRP) ? 'x' : '-');
            cout << ((fileStat.st_mode & S_IROTH) ? 'r' : '-');
            cout << ((fileStat.st_mode & S_IWOTH) ? 'w' : '-');
            cout << ((fileStat.st_mode & S_IXOTH) ? 'x' : '-');

            cout << "\t" << fileStat.st_nlink << "\t";
            struct passwd *pw = getpwuid(fileStat.st_uid);
            struct group *gr = getgrgid(fileStat.st_gid);
            cout << (pw ? pw->pw_name : "unknown") << "\t";
            cout << (gr ? gr->gr_name : "unknown") << "\t";
            cout << fileStat.st_size << "\t";
            cout << entry->d_name << endl;

        } else {
            cout << entry->d_name << "\t";
        }
    }

    cout << endl;
    closedir(directory);
}

void lsCommand(vector<string> paths,bool showHidden, bool longFormat) {

    if (paths.empty()) {
        paths.push_back(".");
    }

    for (const auto &path : paths) {
        if (path == "..") {
            char currentDir[PATH_MAX];
            if (getcwd(currentDir, sizeof(currentDir)) != nullptr) {
                string parentDir = string(currentDir) + "/..";
                listDirectoryContents(parentDir, showHidden, longFormat);
            } else {
                perror("getcwd");
            }
        } else {
            listDirectoryContents(path, showHidden, longFormat);
        }
    }
}