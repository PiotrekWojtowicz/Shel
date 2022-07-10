#ifndef MY_HANDS_1_0
#define MY_HANDS_1_0

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>
#include <string.h>

#define MAXARGS 128
#define MAXLINE 64
#define CONSOLE_ERROR 1
#define FORK_ERROR -1
#define FORK_SCS 0

#define ARRAY_LEN(ARRAY_NAME, TYPE)(sizeof(ARRAY_NAME)/sizeof(TYPE))

//System call wrapers
extern void Console_Child_Signal_Set(__sighandler_t handler);
extern void Console_Wait_Pid(const pid_t pid, char *err_msg);
extern void Console_Write(const void* buf, char *err_msg);
extern void Console_Read(void* buf, char *err_msg);
extern void Task_Fork(char *err_msg);

//Signal hanlders
extern void Console_Child_Hanlder(int n);

//Failure exit handling

#endif