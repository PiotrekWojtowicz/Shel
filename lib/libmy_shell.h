#ifndef MY_SHELL_1_0
#define MY_SHELL_1_0

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>
#include <string.h>

#ifndef MY_HANDS_1_0
#define TERMINATE_SHELL_
#endif

//else include my_hanlder header
#include "libmy_handlers.h"

#ifndef COMMAND_STRING_
#define COMMAND_STRING_ char **
#endif 

//Shell functions 
extern COMMAND_STRING_ Initalize_Shell();
extern void eval(char *cmdline);
extern int parseline(char *buf, char **argv);
extern int builtin_command(char **argv);

#endif