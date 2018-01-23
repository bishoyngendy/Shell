/**
 * Created by programajor on 10/5/17.
 */

#ifndef SHELL_VARIABLES_H
#define SHELL_VARIABLES_H

/**
 * check if a variable is available in the session variables or not.
 * @param key the name of the variable
 * @return true if present else false.
 */
char* lookupVariable(char *key);

/**
 * sets a new session variable or override its value
 * @param key the name of the variable
 * @param value the value of the variable
 */
void setVariable(char *key, char *value);

/**
 * Used for debugging
 */
void printAllVariables();

#endif //SHELL_VARIABLES_H
