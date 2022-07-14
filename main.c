#include "lib/libmy_handlers.h"
int main(){


    //set the signal handler for child proccesses
    Console_Child_Signal_Set(Console_Child_Hanlder);

    Initalize_Shell();
    return 0;
}
