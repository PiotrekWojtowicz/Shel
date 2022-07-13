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

#ifndef INPUT_CH_ARR_
#define INPUT_CH_ARR_ char *
#endif

#ifndef BACKGROUND_CH_
#define BACKGROUND_CH_ '&'
#endif

#define DEBUG_MODE

#ifdef DEBUG_MODE
#define _DEBUG(val) val
#else
#define _DEBUG
#endif

//Shell functions 
extern void Initalize_Shell();
extern int Eval(INPUT_CH_ARR_ cmdline);
extern int Parseline(INPUT_CH_ARR_ buf, COMMAND_STRING_ argv);
extern int Builtin_Command(COMMAND_STRING_ argv);
extern void Execute_Command(COMMAND_STRING_ argv);

#endif