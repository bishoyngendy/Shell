/**
 * Created by programajor on 10/5/17.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fileProcessing.h"

char *historyFileName;
char *logFileName;
char *batchFileName;

void setHistoryFileName(char *historyFileNameParam) {
    historyFileName = (char *) malloc(strlen(historyFileNameParam) * sizeof(char));
    strcpy(historyFileName, historyFileNameParam);
}

void setLogFileName(char *logFileNameParam) {
    logFileName = (char *) malloc(strlen(logFileNameParam) * sizeof(char));
    strcpy(logFileName, logFileNameParam);
}

void seBatchFileName(char *batchFileNameParam) {
    if (batchFileNameParam[0] == '~') {
        char *home = getenv("HOME");
        batchFileName = (char *) malloc((strlen(home) + strlen(batchFileNameParam)) * sizeof(char));
        strcpy(batchFileName, home);
        for (int i = 1, j = (int) strlen(home); i < strlen(batchFileNameParam); j++, i++) {
            batchFileName[j] = batchFileNameParam[i];
        }
    } else {
        batchFileName = (char *) malloc(strlen(batchFileNameParam) * sizeof(char));
        strcpy(batchFileName, batchFileNameParam);
    }
}

void appendToFile(FILE* file, char *text) {
    fprintf(file, "%s\n", text);
}

FILE* getReadableHistoryFile() {
    return fopen(historyFileName, "r");
}

FILE* getWritableHistoryFile() {
    return fopen(historyFileName, "a");
}

void closeFile(FILE* file) {
    if (file != NULL) {
        fclose(file);
    }
}

FILE* getLogFile() {
    return fopen(logFileName, "a");
}

FILE* getCommandsBatchFile() {
    return fopen(batchFileName, "r");
}