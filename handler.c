/**
 * Created by programajor on 10/11/17.
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "handler.h"
#include "variables.h"
#include "environment.h"

void handleExpression(char *sub, char *expression, int argumentSize) {
    int index = strlen(expression) - strlen(sub);
    if (argumentSize != 1 || index == 0 || strlen(sub) == 1 || strlen(expression) < 3) {
        printf("ERROR: command not found\n");
    } else {
        char *key = (char *) malloc(index + 2);
        int j;
        for (j = 0; j < index; j++) {
            key[j] = expression[j];
        }
        key[j]='\0';

        char *value;
        int k;
        if (expression[index + 1] == '$') {
            value = (char *) malloc(strlen(sub) - 1);
            for (j = index + 2, k = 0; j < strlen(expression); j++, k++) {
                value[k] = expression[j];
            }
            value[k]='\0';

            char *check = lookupVariable(value);
            if (strcmp(check, "NA") == 0) {
                if (isEnvironmentVariable(value)) {
                    setVariable(key, getenv(value));
                } else {
                    setVariable(key, "");
                }
            } else {
                setVariable(key, lookupVariable(value));
            }
        } else {
            value = (char *) malloc(strlen(sub));
            for (j = index + 1, k = 0; j < strlen(expression); j++, k++) {
                value[k] = expression[j];
            }
            value[k]='\0';
            setVariable(key, value);
        }
    }
}

char* handleVariablesBeforeParsing(char* command) {
    for(int ind = 0; ind < strlen(command); ind++) {
        if (command[ind] == '$') {
            char *temp = (char *) malloc(strlen(command));
            int j, k;
            for (j = 0, k = ind + 1; command[k]!='\0' && command[k]!= '\\'; k++, j++) {
                temp[j] = command[k];
            }
            temp[j] = '\0';
            char *check = lookupVariable(temp);
            if (strcmp(check, "NA") == 0) {
                if (isEnvironmentVariable(temp)) {
                    int len = strlen(command);
                    char *variableValue = getenv(temp);
                    char *backup= (char *) malloc(strlen(command));
                    strcpy(backup, command);
                    if (backup[k] == '\\') {
                        command = (char *) malloc(ind + strlen(variableValue) + len - k);
                    } else {
                        command = (char *) malloc(ind + strlen(variableValue) + len - k + 1);
                    }
                    int x;
                    for(x = 0; x < ind; x++) {
                        command[x] = backup[x];
                    }
                    int y;
                    for (x = ind, y = 0; x < ind + strlen(variableValue); ++x, y++) {
                        command[x] = variableValue[y];
                    }
                    if (backup[k] == '\\') {
                        y = k + 1;
                    } else {
                        y = k;
                    }
                    for (x = ind + strlen(variableValue); y < strlen(backup); ++x, ++y) {
                        command[x] = backup[y];
                    }
                    command[x] = '\0';
                } else {
                    int len = strlen(command);
                    char *variableValue = "";
                    char *backup = (char *) malloc(strlen(command));
                    strcpy(backup, command);
                    if (backup[k] == '\\') {
                        command = (char *) malloc(ind + strlen(variableValue) + len - k);
                    } else {
                        command = (char *) malloc(ind + strlen(variableValue) + len - k + 1);
                    }
                    int x;
                    for(x = 0; x < ind; x++) {
                        command[x] = backup[x];
                    }
                    int y;
                    for (x = ind, y = 0; x < ind + strlen(variableValue); ++x, y++) {
                        command[x] = variableValue[y];
                    }
                    if (backup[k] == '\\') {
                        y = k + 1;
                    } else {
                        y = k;
                    }
                    for (x = ind + strlen(variableValue); y < strlen(backup); ++x, ++y) {
                        command[x] = backup[y];
                    }
                    command[x] = '\0';
                }
            } else {
                int len = strlen(command);
                char *variableValue = lookupVariable(temp);
                char *backup = (char *) malloc(strlen(command));
                strcpy(backup, command);
                if (backup[k] == '\\') {
                    command = (char *) malloc(ind + strlen(variableValue) + len - k);
                } else {
                     command = (char *) malloc(ind + strlen(variableValue) + len - k + 1);
                }
                int x;
                for(x = 0; x < ind; x++) {
                    command[x] = backup[x];
                }
                int y;
                for (x = ind, y = 0; x < ind + strlen(variableValue); ++x, y++) {
                    command[x] = variableValue[y];
                }
                if (backup[k] == '\\') {
                    y = k + 1;
                } else {
                    y = k;
                }
                for (x = ind + strlen(variableValue); y < strlen(backup); ++x, ++y) {
                    command[x] = backup[y];
                }
                command[x] = '\0';
            }
        }
    }
    return command;
}

void handleVariables(char** parsed, int argumentSize) {
    for (int i = 0; i < argumentSize; i++) {
        for(int ind = 0; ind < strlen(parsed[i]); ind++) {
            if (parsed[i][ind] == '$') {
                char *temp = (char *) malloc(strlen(parsed[i]));
                int j, k;
                for (j = 0, k = ind + 1; parsed[i][k]!='\0' && parsed[i][k]!= '\\'; k++, j++) {
                    temp[j] = parsed[i][k];
                }
                temp[j] = '\0';
                char *check = lookupVariable(temp);
                if (strcmp(check, "NA") == 0) {
                    if (isEnvironmentVariable(temp)) {
                        int len = strlen(parsed[i]);
                        char *variableValue = getenv(temp);
                        char *backup= (char *) malloc(strlen(parsed[i]));
                        strcpy(backup, parsed[i]);
                        if (backup[k] == '\\') {
                            parsed[i] = (char *) malloc(ind + strlen(variableValue) + len - k);
                        } else {
                            parsed[i] = (char *) malloc(ind + strlen(variableValue) + len - k + 1);
                        }
                        int x;
                        for(x = 0; x < ind; x++) {
                            parsed[i][x] = backup[x];
                        }
                        int y;
                        for (x = ind, y = 0; x < ind + strlen(variableValue); ++x, y++) {
                            parsed[i][x] = variableValue[y];
                        }
                        if (backup[k] == '\\') {
                            y = k + 1;
                        } else {
                            y = k;
                        }
                        for (x = ind + strlen(variableValue); y < strlen(backup); ++x, ++y) {
                            parsed[i][x] = backup[y];
                        }
                        parsed[i][x] = '\0';
                    } else {
                        int len = strlen(parsed[i]);
                        char *variableValue = "";
                        char *backup = (char *) malloc(strlen(parsed[i]));
                        strcpy(backup, parsed[i]);
                        if (backup[k] == '\\') {
                            parsed[i] = (char *) malloc(ind + strlen(variableValue) + len - k);
                        } else {
                            parsed[i] = (char *) malloc(ind + strlen(variableValue) + len - k + 1);
                        }                        int x;
                        for(x = 0; x < ind; x++) {
                            parsed[i][x] = backup[x];
                        }
                        int y;
                        for (x = ind, y = 0; x < ind + strlen(variableValue); ++x, y++) {
                            parsed[i][x] = variableValue[y];
                        }
                        if (backup[k] == '\\') {
                            y = k + 1;
                        } else {
                            y = k;
                        }
                        for (x = ind + strlen(variableValue); y < strlen(backup); ++x, ++y) {
                            parsed[i][x] = backup[y];
                        }
                        parsed[i][x] = '\0';
                    }
                } else {
                    int len = strlen(parsed[i]);
                    char *variableValue = lookupVariable(temp);
                    char *backup = (char *) malloc(strlen(parsed[i]));
                    strcpy(backup, parsed[i]);
                    if (backup[k] == '\\') {
                        parsed[i] = (char *) malloc(ind + strlen(variableValue) + len - k);
                    } else {
                        parsed[i] = (char *) malloc(ind + strlen(variableValue) + len - k + 1);
                    }
                    int x;
                    for(x = 0; x < ind; x++) {
                        parsed[i][x] = backup[x];
                    }
                    int y;
                    for (x = ind, y = 0; x < ind + strlen(variableValue); ++x, y++) {
                        parsed[i][x] = variableValue[y];
                    }
                    if (backup[k] == '\\') {
                        y = k + 1;
                    } else {
                        y = k;
                    }
                    for (x = ind + strlen(variableValue); y < strlen(backup); ++x, ++y) {
                        parsed[i][x] = backup[y];
                    }
                    parsed[i][x] = '\0';
                }
            }
        }
    }
//    handleHomeMark(parsed, argumentSize);
}

void handleHomeMark(char** parsed, int argumentSize) {
    for (int i = 0; i < argumentSize; i++) {
        if (parsed[i][0] == '~') {
            char *backup= (char *) malloc(strlen(parsed[i]));
            strcpy(backup, parsed[i]);
            char *check = lookupVariable("HOME");
            if (strcmp(check, "NA") == 0) {
                char *home = getenv("HOME");
                parsed[i] = (char *) malloc(strlen(home) + strlen(backup));
                strcpy(parsed[i], home);
                int k, j = strlen(home);
                for (k = 1; k < strlen(backup); k++, j++) {
                    parsed[i][j] = backup[k];
                }
                parsed[i][j] = '\0';
            } else {
                parsed[i] = (char *) malloc(strlen(check) + strlen(backup));
                strcpy(parsed[i], check);
                int k, j = strlen(check);
                for (k = 1; k < strlen(backup); k++, j++) {
                    parsed[i][j] = backup[k];
                }
                parsed[i][j] = '\0';
            }
        }
    }
}
