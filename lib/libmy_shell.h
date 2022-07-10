#ifndef MY_SHELL_1_0
#define MY_SHELL_1_0

//Shell functions
extern void eval(char *cmdline);
extern int parseline(char *buf, char **argv);
extern int builtin_command(char **argv);

#endif