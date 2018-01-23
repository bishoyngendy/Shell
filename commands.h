/**
 * Created by programajor on 10/5/17.
 */

#ifndef SHELL_COMMANDS_H
#define SHELL_COMMANDS_H

#include <stdio.h>

/**
 * changes the current directory,
 * @param path the new path to go to.
 * @param argumentSize the number of arguments of the command
 */
void cd(const char* path, int argumentSize);

/**
 * prints all environment variables with their current values
 */
void printenv();

/**
 * get all environment variables either from user enteries data or from the environment.
 */
void excutePrintenv();

#endif //SHELL_COMMANDS_H
