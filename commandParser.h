/**
 * Created by programajor on 10/5/17.
 */

#ifndef SHELL_COMMAND_PARSER_H
#define SHELL_COMMAND_PARSER_H

/**
 * parses the given command to a list of arguments
 * which can be returned using getParsedArguments()
 * @param command the string to be parsed.
 * @return 0 in case of invalid command,
 * 1 in case of parsing success, 3 in case the command is a comment
 */
int parseCommand(char *command);

/**
 * return the parsed arguments from the function parseCommand()
 * @return the parsed arguments from the function parseCommand()
 */
char** getParsedArguments();

/**
 * @return the number of arguments resulting from parsing the command
 */
int getArgumentSize();

#endif //SHELL_COMMAND_PARSER_H
