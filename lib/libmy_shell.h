#ifndef MY_SHELL_2_1
#define MY_SHELL_2_1

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>
#include <string.h> 
#include <fcntl.h>


#ifndef MY_HANDS_1_0
#define TERMINATE_SHELL_
#endif

#ifndef COMMAND_STRING_
#define COMMAND_STRING_ char **
#endif 

#ifndef INPUT_CH_ARR_
#define INPUT_CH_ARR_ char *
#endif

#ifndef BACKGROUND_CH_
#define BACKGROUND_CH_ '&'
#endif

//check for possible performance improvement
//if you are interested in commiting to this repo, pls look for this macro
#define PERF_IMPRV

//#define DEBUG_MODE

#ifdef DEBUG_MODE
#define _DEBUG 1
#else
#define _DEBUG 0
#endif

//else include my_hanlder header
#include "libmy_handlers.h"
#include "libmy_builtins.h"
#include "libmy_movement.h"

//Shell functions 
extern void Initalize_Shell();
extern int Eval(INPUT_CH_ARR_ cmdline);
extern int Parseline(INPUT_CH_ARR_ buf, COMMAND_STRING_ argv);
extern int Execute_Built_In(COMMAND_STRING_ argv);
#endif
