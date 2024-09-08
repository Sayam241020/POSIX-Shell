#include<bits/stdc++.h>
#include<unistd.h>
#include<pwd.h>
#include <sys/wait.h>
using namespace std;

vector<char*> token(char* str, const char* delimiter) {
    vector<char*> tokens;
    char* token = strtok(str, delimiter);
    while (token != nullptr) {
        tokens.push_back(token);
        token = strtok(nullptr, delimiter);
    }
    tokens.push_back(nullptr);
    return tokens;
}

char* trim(char* str) {
    char* end;

    // Trim leading space
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0)  // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    *(end + 1) = 0;

    return str;
}
