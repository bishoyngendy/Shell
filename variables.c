/**
 * Created by programajor on 10/5/17.
 */

#include <stdio.h>
#include <string.h>
#include "variables.h"

typedef struct Variable {
    char *key;
    char *value;
} Variable;

Variable variables[501];
int lastIndex = -1;

char* lookupVariable(char *key) {
    for (int i = 0; i <= lastIndex; ++i) {
        if (strcmp(variables[i].key, key) == 0) {
            return variables[i].value;
        }
    }
    return "NA";
}

void setVariable(char *key, char *value) {
    for (int i = 0; i <= lastIndex; ++i) {
        if (strcmp(variables[i].key, key) == 0) {
            variables[i].value = value;
            return;
        }
    }

    if (lastIndex == 500) return;

    Variable variable;
    variable.key = key;
    variable.value = value;
    variables[++lastIndex] = variable;
}

void printAllVariables() {
    for (int i = 0; i <= lastIndex; ++i) {
        printf("key: ");
        printf("%s", variables[i].key);
        printf(", value: ");
        printf("%s", variables[i].value);
        printf("\n");
    }
}