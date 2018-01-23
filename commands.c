/**
 * Created by programajor on 10/5/17.
 */

#include <stdio.h>
#include <string.h>
#include <zconf.h>
#include <stdlib.h>
#include <wait.h>
#include "commands.h"
#include "variables.h"
#include "environment.h"

extern char **environ;

void cd(const char* path, int argumentSize) {
    if (argumentSize > 2) {
        printf("ERROR: too many arguments for cd\n");
        return;
    }
    int changeDirectoryId;
    char *tempHome = lookupVariable("HOME");
    char *home;
    if (strcmp(tempHome, "NA") == 0) {
        home = getenv("HOME");
    } else {
        home = (char*) malloc(strlen(tempHome) * sizeof(char));
        strcpy(home, tempHome);
    }

    if (argumentSize == 1 || strcmp(path, "~") == 0) {
        changeDirectoryId = chdir(home);
    } else if (path[0] == '~') {
        char *temp = (char *) malloc(strlen(path) + strlen(home));
        int j, k;
        for (j = 0; j < strlen(home); j++) {
            temp[j] = home[j];
        }
        for (k = 1; k < strlen(path); j++, k++) {
            temp[j] = path[k];
        }
        temp[j] = '\0';
        changeDirectoryId = chdir(temp);
        if (changeDirectoryId != 0) {
            free(temp);
            temp = (char *) malloc(strlen(path) + 6);
            int j = 6, k;
            strcpy(temp, "/home/");
            for (k = 1; k < strlen(path); j++, k++) {
                temp[j] = path[k];
            }
            temp[j] = '\0';
            changeDirectoryId = chdir(temp);
            free(temp);
        }
    } else {
        changeDirectoryId = chdir(path);
    }

    if (changeDirectoryId != 0) {
        printf("ERROR: cannot change directory\n");
    }
}

void printenv() {
    char *printenv = "printenv";
    int status;
    pid_t id = fork();
    if (id > 0) { // Parent process
        do {
            waitpid(id, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    } else if (id == 0) { // Child process
        if (access(printenv, F_OK) != -1) { // check current directory to run command
            excutePrintenv();
        } else {
            char **sources = getSources();
            for (int i = 0; sources[i] != NULL; i++) { // check other directories from PATH
                char *executablePath = (char *) malloc(strlen(sources[i]) + strlen(printenv) + 2);
                strcpy(executablePath, sources[i]);
                strcat(executablePath, "/");
                strcat(executablePath, printenv);
                if (access(executablePath, F_OK) != -1) {
                    excutePrintenv();
                    return;
                }
            }
            // command didn't match any, exit the child process
            printf("ERROR: command not found\n");
        }
    }
}

void excutePrintenv() {
    for(char **current = environ; *current; current++) {
        char *temp = (char *) malloc(strlen(*current) * sizeof(char));
        strcpy(temp, *current);
        int i = 0;
        while (temp[i] != '=') {
            i++;
        }

        char var[i + 1];
        for (int j = 0; j < i; j++) {
            var[j] = temp[j];
        }
        var[i] = '\0';

        char *res = lookupVariable(var);
        if (strcmp(res, "NA") == 0) {
            puts(*current);
        } else {
            char* message = (char *) malloc(strlen(var) + strlen(res) + 1);
            strcpy(message, var);
            strcat(message, "=");
            strcat(message, res);
            puts(message);
        }
    }
}