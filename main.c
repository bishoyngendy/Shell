/**
 * Created by programajor on 10/5/17.
 */

#include <stdio.h>
#include <string.h>
#include <zconf.h>
#include <stdlib.h>
#include <wait.h>
#include "commands.h"
#include "fileProcessing.h"
#include "environment.h"
#include "commandParser.h"
#include "variables.h"
#include "handler.h"

char command[514];

void startShell(bool readFromFile);
void shellLoop(bool inputFromFile);

void executeCommand(char ** parsed, int argumentSize);

/**
 * entry point to the application
 * @param argc the number of arguments when running the app.
 * @param argv the arguments when running the app.
 */
int main (int argc, char *argv[]) {
    setupEnvironment();
    if (argc == 2) {
        seBatchFileName(argv[1]);
        startShell(true);
    } else if (argc == 1) {
        startShell(false);
    } else {
        printf("%s\n", "invalid command");
    }
    return 0;
}

void startShell(bool readFromFile) {
    cd("", 1); // let shell starts from home
    if (readFromFile) {
        shellLoop(true);
    } else {
        shellLoop(false);
    }
}

void shellLoop(bool inputFromFile) {
    bool fromFile = inputFromFile;
    FILE* batchFile;
    if (fromFile) {
        batchFile = getCommandsBatchFile();
        if (batchFile == NULL) {
            printf("%s\n", "ERROR : batch file does not exist or cannot be opened");
            return;
        }
    }
    while (true) {
        if (fromFile) {
            if(fgets(command, 514, batchFile) == NULL) break;
            printf("%s", command);
        } else {
            printf("Shell >> ");
            if (fgets(command, 514, stdin) == NULL) break;
        }
        command[strlen(command) - 1] = '\0';
        if (command[strlen(command) - 2] == '\r') command[strlen(command) - 2] = '\0';
        appendToHistoryFile(command);
        if (strlen(command) > 512) {
            printf("ERROR: very long command line\n");
            continue;
        }

        char *sep = strchr(command, '=');
        int parseStatus;
        if (sep == NULL) {
            char* newCommand = handleVariablesBeforeParsing(command);
            parseStatus = parseCommand(newCommand);
        } else {
            parseStatus = parseCommand(command);
        }

        if (parseStatus == 0) { // invalid command
            printf("ERROR: invalid command\n");
            continue;
        } else if (parseStatus == 2) continue; // comment line will be ignored

        char** parsed = getParsedArguments();
        int argumentSize = getArgumentSize();
        if (argumentSize == 0) continue;
        if (strcmp(parsed[0], "exit") == 0 || strcmp(parsed[0], "Exit") == 0) break; // Exit command
        if (strcmp(parsed[0], "cd") == 0) {
            handleVariables(parsed, argumentSize);
            cd(parsed[1], argumentSize);
            continue;
        } else if (strcmp(parsed[0], "history") == 0 && parsed[1] == NULL) {
            showHistory();
            continue;
        }
        if (strcmp(parsed[0], "printenv") == 0 && parsed[1] == NULL) {
            setUpSources();
            printenv();
            continue;
        }

        if (sep != NULL) {
            handleVariables(parsed, argumentSize);
        }
        handleHomeMark(parsed, argumentSize);

        setUpSources();
        char *sub = strchr(parsed[0], '=');
        if (sub != NULL) {
            handleExpression(sub, parsed[0], argumentSize);
        } else {
            executeCommand(parsed, argumentSize);
        }
    }
}

void executeCommand(char ** parsed, int argumentSize) {
    bool runInBackground = false;
    if (strcmp(parsed[argumentSize - 1], "&") == 0) {
        runInBackground = true;
        parsed[argumentSize - 1] = NULL;
    }
    int status;
    pid_t id = fork();
    if (id > 0) { // Parent process
        if (!runInBackground) {
            do {
                waitpid(id, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    } else if (id == 0) { // Child process
        if (access(parsed[0], F_OK) != -1) { // check current directory to run command
            if (execv(parsed[0], parsed) == -1) {
                perror("ERROR ");
                exit(0);
            }
        } else {
            char **sources = getSources();
            for (int i = 0; sources[i] != NULL; i++) { // check other directories from PATH
                char *executablePath = (char *) malloc(strlen(sources[i]) + strlen(parsed[0]) + 2);
                strcpy(executablePath, sources[i]);
                strcat(executablePath, "/");
                strcat(executablePath, parsed[0]);
                if (access(executablePath, F_OK) != -1) {
                    parsed[0] = (char *) malloc(strlen(executablePath) + 1);
                    strcpy(parsed[0], executablePath);
                    if (execv(parsed[0], parsed) == -1) {
                        perror("ERROR ");
                        exit(0);
                    }
                    return;
                }
            }
            // command didn't match any, exit the child process
            printf("ERROR: command not found\n");
        }
    }
}