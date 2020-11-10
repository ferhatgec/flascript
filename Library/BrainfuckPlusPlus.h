/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef BRAINFUCK_PLUS_PLUS_H
#define BRAINFUCK_PLUS_PLUS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BRAINFUCK_PLUS_PLUS_VERSION "0.1"
#define BRAINFUCK_PLUS_PLUS_STATE "beta-1"

static void BfInterpreter(char *code) {
	int length = strlen(code);
    	char *ptr = (char *)calloc(1000, sizeof(char));
   	char *emulptr = ptr;
   	for (int i = 0; i < length; i++) {
        	if (code[i] == '>') { ptr++; } else if (code[i] == '<') { ptr--; } else if (code[i] == '+') { (*ptr)++;} else if (code[i] == '-') { (*ptr)--; } else if (code[i] == '.') { printf("%c", *ptr); } else if (code[i] == ',') { scanf("%c", ptr); } else if (code[i] == '[') {
            if (*ptr == 0) {
                for (int j = i; j < length; j++) {
                    i++;
                    if (code[j] == ']') {
                        i++;
                        break;
                    }
                }
            }
        } else if (code[i] == ']') {
            if (*ptr != 0) {
                for (int j = i; j > 0; j--) {
                    i--;
                    if (code[j] == '[') {
                        i++;
                        break;
                    }
                }
            }
        }
    }
}

static void Printer(char *buffer, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d-", buffer[i]);
    }
    printf("\n");
}

#endif // BRAINFUCK_PLUS_PLUS_H
