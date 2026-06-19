#include "debug.h"

#ifdef DBG_MODE
char DEBUG_BUFFER[DEBUG_SIZE_BUFFER] = {0};
#endif

void print_debug(char *func_name, char *message)
{
	#ifdef DBG_MODE
	printf("%s: %s\n", func_name, message);
	#endif
}
