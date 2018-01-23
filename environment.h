/**
 * Created by programajor on 10/5/17.
 */

#ifndef SHELL_ENVIRONMENT_H
#define SHELL_ENVIRONMENT_H

#include <stdbool.h>

/**
 * checks if a key is a name of an environment variable or not
 * @param key the variable name
 * @return true if key is an environment variable else false
 */
bool isEnvironmentVariable(char *key);

/**
 * sets up the paths of bins from the current $PATH variable
 */
void setUpSources();

/**
 * Used to initialize the terminal environment
 */
void setupEnvironment();

/**
 * shows the history on the terminal.
 */
void showHistory();

/**
 * adds extra commands to the history file
 * @param command the command to be added to history
 */
void appendToHistoryFile(char *command);

/**
 * @return the current sources to search for commands in them.
 */
char** getSources();

#endif //SHELL_ENVIRONMENT_H
