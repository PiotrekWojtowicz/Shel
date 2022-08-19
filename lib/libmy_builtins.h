#ifndef BUILTINS
#define BUILTINS

#include "libmy_handlers.h" 

//Built in commands section
const enum Builtins{CD, HELP, EXIT, SETCOL,
 EEOF};

//BuiltIns description
typedef struct{
    INPUT_CH_ARR_ command;
    INPUT_CH_ARR_ description;
} Builtin_Info;

#ifndef COLUMN_SIZE
#define COLUMN_SIZE 40
#endif

//Initialize builtins
extern void Initialize_Built_Ins(void);
extern int Builtin_Command(COMMAND_STRING_ argv);
//Builtin modules
extern int Command_Help(void);
extern int Command_Cd(INPUT_CH_ARR_ directory);
extern int Command_Exit(COMMAND_STRING_ argv);
extern int Command_SetColors(COMMAND_STRING_ argv);
//Exeption for end of file
extern int Eof_Exeption(void);
//Wraper created to quickly find a builtin
extern int Find_Built_Command(COMMAND_STRING_ argv) PERF_IMPRV;

//Soft wrap the command description
extern void Soft_Wrap(INPUT_CH_ARR_ description)PERF_IMPRV;

#endif
