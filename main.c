#include "lib/libmy_handlers.h"
int main(){


    //set the signal handler for child proccesses
    Console_Child_Signal_Set(Console_Child_Hanlder);

    //char cmdline[MAXLINE];
    Task_Fork("Fork error");
    //Console_Write("shell$ ", "Write shell error");
    //Console_Read(cmdline, "Read error");


    return 0;
}
