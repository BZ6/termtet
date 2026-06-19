#ifndef __DEBUG_H__
#define __DEBUG_H__


#include <stdio.h>

//#define DBG_MODE

#ifdef DBG_MODE
#define DEBUG_SIZE_BUFFER 100

extern char DEBUG_BUFFER[DEBUG_SIZE_BUFFER];
#endif

void print_debug(char *func_name, char *message);

#endif // __DEBUG_H__
