#include "lib/libmy_handlers.h"
int main(){


    //set the signal handler for child proccesses
    Console_Child_Signal_Set(Console_Child_Hanlder);

    //So the compilter's happy
    char **command = NULL;

    //Perform the task with the command
    Task_Fork(command, "Fork error");

    return 0;
}
