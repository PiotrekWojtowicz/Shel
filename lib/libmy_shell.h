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

#ifndef COMMAND_STRING_
#define COMMAND_STRING_ char **
#endif 

#ifndef INPUT_CH_ARR_
#define INPUT_CH_ARR_ char *
#endif

#ifndef BACKGROUND_CH_
#define BACKGROUND_CH_ '&'
#endif

//possible performance improvement
#define PERF_IMPRV

//#define DEBUG_MODE

#ifdef DEBUG_MODE
#define _DEBUG 1
#else
#define _DEBUG 0
#endif

#ifndef BUILTINS
#define BUILTINS

//Built in commands section
const enum Builtins{CD, HELP, EXIT};

//BuiltIns description
typedef struct{
    INPUT_CH_ARR_ command;
    INPUT_CH_ARR_ description;
} Builtin_Info;
#endif

//else include my_hanlder header
#include "libmy_handlers.h"

//Initialize builtins
extern void Initialize_Built_Ins(void);

//Shell functions 
extern void Initalize_Shell();
extern int Eval(INPUT_CH_ARR_ cmdline);
extern int Parseline(INPUT_CH_ARR_ buf, COMMAND_STRING_ argv);
extern int Builtin_Command(COMMAND_STRING_ argv);
extern int Find_Built_Command(COMMAND_STRING_ argv) PERF_IMPRV;
extern int Execute_Built_In(COMMAND_STRING_ argv);
#endif