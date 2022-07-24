#ifndef BUILTINS
#define BUILTINS

#include "libmy_handlers.h" 

//Built in commands section
const enum Builtins{CD, HELP, EXIT, EEOF};

//BuiltIns description
typedef struct{
    INPUT_CH_ARR_ command;
    INPUT_CH_ARR_ description;
} Builtin_Info;

//Initialize builtins
extern void Initialize_Built_Ins(void);
extern int Builtin_Command(COMMAND_STRING_ argv);
//Builtin modules
extern int Command_Help(void);
extern int Command_Cd(INPUT_CH_ARR_ directory);
extern int Comand_Exit(void);
extern int Eof_Exeption(void);
extern int Find_Built_Command(COMMAND_STRING_ argv) PERF_IMPRV;

#endif