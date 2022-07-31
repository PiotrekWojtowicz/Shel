#ifndef MVMENT
#define MVMENT

#include "libmy_handlers.h"
#include <curses.h>
#include <readline/readline.h>
#include <stdio.h>

/* A static variable for holding the line. */
static char *line_read = (char *)NULL;

/* Read a string, and return a pointer to it.  Returns NULL on EOF. */
extern char* rl_gets();

#endif