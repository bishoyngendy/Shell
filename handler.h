//
// Created by programajor on 10/11/17.
//

#ifndef SHELL_HANDLER_H
#define SHELL_HANDLER_H

/**
 * replaces the $var with its value
 */
void handleVariables(char** parsed, int argumentSize);

/**
 * replaces the $var with its in the command
 */
char* handleVariablesBeforeParsing(char* command);

/**
 * handles assigning values to variables
 */
void handleExpression(char *sub, char *expression, int argumentSize);

/**
 * replaces ~ with the home directory.
 */
void handleHomeMark(char** parsed, int argumentSize);

#endif //SHELL_HANDLER_H
