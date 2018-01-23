/**
 * Created by programajor on 10/5/17.
 */

#include "environment.h"
#include "fileProcessing.h"
#include "variables.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>

char **sources;

const char *environmentVariables[] = {
        "PATH", "HOME", "TERM", "PS1", "MAIL", "TEMP", "JAVA_HOME", "ORACLE_HOME", "TZ", "PWD",
        "HISTFILE", "HISTFILESIZE", "HOSTNAME", "LD_LIBRARY_PATH", "USER", "DISPLAY", "SHEL",
        "TERMCAP", "OSTYPE", "MACHTYPE", "EDITOR", "PAGER", "MANPATH" };

void setupLogAndHistoryFiles();
void appendToLogFile();
void appendToHistoryFile(char *command);

void setUpSources();

char** getSources() {
    return sources;
}

void closeAction() {
    exit(0);
}

void setupEnvironment() {
    setupLogAndHistoryFiles();
    signal(SIGCHLD, appendToLogFile);
    signal(SIGINT, closeAction);
}

bool isEnvironmentVariable(char *key) {
    int length = sizeof(environmentVariables) / sizeof(environmentVariables[0]);
    for (int i = 0; i < length; i++) {
        if (strcmp(environmentVariables[i], key) == 0) return true;
    }
    return false;
}

void setUpSources() {
    free(sources);
    int index = 0;
    sources = (char **) malloc(20 * sizeof(char *));
    char *temp = lookupVariable("PATH");
    if (strcmp(temp, "NA") == 0) {
        temp = (char *) malloc(514 * sizeof(char));
        strcpy(temp, getenv("PATH"));
    }
    char *path;
    path = (char *) malloc(strlen(temp) * sizeof(char));
    strcpy(path, temp);
    char *token = strtok(path, ":");
    while (token != NULL) {
        sources[index] = (char *) malloc(strlen(token) + 1);
        strcpy(sources[index], token);
        index++;
        token = strtok(NULL, ":");
    }
    sources[index] = NULL;
}

void setupLogAndHistoryFiles() {
    char history[] = "/Shell_History";
    char log[] = "/Shell_Log";
    char *home = getenv("HOME");

    char *historyFileName = malloc(strlen(home) + 15);
    strcpy(historyFileName, home);
    strcat(historyFileName, history);
    setHistoryFileName(historyFileName);

    char *logFileName = malloc(strlen(home) + 11);
    strcpy(logFileName, home);
    strcat(logFileName, log);
    setLogFileName(logFileName);
}

void appendToLogFile() {
    FILE* logFile = getLogFile();
    if (logFile != NULL) {
        appendToFile(logFile, "child process was terminated");
        closeFile(logFile);
    } else {
        printf("ERROR: cannot open log file'n");
    }
}

void appendToHistoryFile(char *command) {
    FILE* historyFile = getWritableHistoryFile();
    if (historyFile != NULL) {
        appendToFile(historyFile, command);
        closeFile(historyFile);
    } else {
        printf("ERROR: cannot open history file\n");
    }
}

void showHistory() {
    char command[514];
    FILE* historyFile = getReadableHistoryFile();
    if (historyFile == NULL) {
        printf("ERROR: cannot open history file\n");
    } else {
        while (fgets(command, 514, historyFile)) {
            printf("%s", command);
        }
        closeFile(historyFile);
    }
}
