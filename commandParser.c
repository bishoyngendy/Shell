/**
 * Created by programajor on 10/5/17.
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "commandParser.h"

int argumentSize;
char **parsed;

char** getParsedArguments() {
    return parsed;
}

int parseCommand(char *command) {
    int s = 0;
    if (strlen(command) > 7) {
        if (command[0] == 'e' && command[1] == 'x' && command[2] == 'p' && command[3] == 'o' &&
            command[4] == 'r' && command[5] == 't' && command[6] == ' ') {
            s = 7;
        }
    }
    if (command[0] == '#') return 2; // return 2 in case of comments
    int len = strlen(command);
    if (command[len - 1] == '&' && command[len - 2] != ' ') {
        char *secondCommand = (char *) malloc((len + 2) * sizeof(char));
        int i;
        for (i = 0; i < len - 1; ++i) {
            secondCommand[i] = command[i];
        }
        secondCommand[i++] = ' ';
        secondCommand[i++] = '&';
        secondCommand[i] = '\0';
        return parseCommand(secondCommand);
    }

    argumentSize = 0;
    parsed = (char **) malloc(513 * sizeof(char *));
    bool isQuoteFound = false;
    int start = -1, end;
    int i;
    for (i = s; command[i] != '\0' && command[i] != '\n'; i++) {
        if (!isQuoteFound) {
            if (command[i] == '"') {
                start = i + 1;
                isQuoteFound = true;
            } else if(command[i] == ' ') {
                if (start != -1) {
                    end = i - 1;
                    parsed[argumentSize] = (char *) malloc((end - start + 2) * sizeof(char));
                    int j, index;
                    for (index = 0, j = start; j <= end; j++, index++) {
                        parsed[argumentSize][index] = command[j];
                    }
                    parsed[argumentSize][index] = '\0';
                    argumentSize++;
                    start=-1;
                }
            } else if (start == -1) {
                start = i;
            }
        } else if (command[i] == '"') {
            isQuoteFound = false;
            end = i - 1;
            if (end >= start) {
                parsed[argumentSize] = (char *) malloc((end - start + 2) * sizeof(char));
                int j, index;
                for (index = 0, j = start; j <= end; j++, index++) {
                    parsed[argumentSize][index] = command[j];
                }
                parsed[argumentSize][index] = '\0';
                argumentSize++;
            }
            start = -1;
        }
    }
    if (start != -1) {
        end = i - 1;
        parsed[argumentSize] = (char *) malloc((end - start + 2) * sizeof(char));
        int j, index;
        for(index = 0, j = start; j <= end; j++, index++) {
            parsed[argumentSize][index] = command[j];
        }
        parsed[argumentSize][index] = '\0';
        argumentSize++;
    }
    parsed[argumentSize] = NULL;
    if (isQuoteFound) {
        return 0;
    } else {
        char *sub = strchr(command, '=');
        if (sub != NULL && argumentSize == 1) {
            parsed[argumentSize] = (char *) malloc((strlen(command) - 1) * sizeof(char));
            int index = 0;
            for (i = 0; command[i] != '\0' && command[i] != '\n'; i++) {
                if (command[i] != '"') {
                    parsed[argumentSize - 1][index] = command[i];
                    index++;
                }
            }
            parsed[argumentSize - 1][index] = '\0';
        }
        return 1;
    }
}

int getArgumentSize() {
    return argumentSize;
}