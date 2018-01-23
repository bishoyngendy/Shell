/**
 * Created by programajor on 10/5/17.
 */

#ifndef SHELL_FILE_PROCESSING_H
#define SHELL_FILE_PROCESSING_H

#include <stdio.h>


/**
 * sets the name of the history file.
 * @param historyFileNameParam the name of the history file
 */
void setHistoryFileName(char *historyFileNameParam);

/**
 * sets the name of the log file.
 * @param logFileNameParam the name of the log file
 */
void setLogFileName(char *logFileNameParam);

/**
 * sets the name of the batch file.
 * @param batchFileNameParam the name of the batch file
 */
void seBatchFileName(char *batchFileNameParam);

/**
 * append a text to a file.
 * @param file the file to append to.
 * @param text the text to be appended.
 */
void appendToFile(FILE* file, char *text);

/**
 * @return history file in readable format.
 */
FILE* getReadableHistoryFile();

/**
 * @return history file in writable format.
 */
FILE* getWritableHistoryFile();

/**
 * @return log file in writable format.
 */
FILE* getLogFile();

/**
 * @return batch file in readable format.
 */
FILE* getCommandsBatchFile();

/**
 * closes a file
 * @param file the file to be closed
 */
void closeFile(FILE* file);

#endif //SHELL_FILE_PROCESSING_H
