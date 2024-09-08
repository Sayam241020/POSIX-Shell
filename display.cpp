#include<bits/stdc++.h>
#include<unistd.h>
#include<pwd.h>
#include <sys/wait.h>
using namespace std;
extern string  home_dir;
extern string currentDir;
extern struct passwd *password;
extern char name[256];
void display(){
    // char name[256];
    // char curr_dir[256];
    // gethostname(name,sizeof(name));
    // getcwd(curr_dir,sizeof(curr_dir));
    // struct passwd *password = getpwuid(getuid());
    // string currentDir = curr_dir;
    if (currentDir.find(home_dir) == 0) {
        currentDir.replace(0, home_dir.length(), "~");
    }
    cout<<password->pw_name<<"@"<<name<<":"<<currentDir<<"> ";
    cout.flush();
}