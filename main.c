#include "lib/libmy_handlers.h"

int main(){

    //Set the signal handler for child proccesses
    Console_Signal_Set(Console_Handler);
    //Start shell
    Initalize_Shell();

    return 0;
}
