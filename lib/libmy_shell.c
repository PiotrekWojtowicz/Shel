#include "libmy_shell.h"

int Parseline(INPUT_CH_ARR_ buf, COMMAND_STRING_ argv){

    INPUT_CH_ARR_ begin = NULL;
    //Number of arguments
    int argc = 0;
    int is_background;

    //!
    //What we are doing here is me get rid of the '\n' char
    buf[strlen(buf)-1] = ' ';
    while(*buf && (*buf == ' ')) // <--- ignore leading blank spaces inside the command
        buf++; 

    while((begin = strchr(buf, ' '))){
        /*
            The strchr is returning the first occurence of the character or NULL if not found
            This ensures us each time the 'begin' will point to the beginning of the command
            or the arguments. What is left is to skip unnecessary blank spaces which the 
            last while is taking care of.
        */
       argv[argc++] = buf;
       *begin = '\0';
       buf = begin + 1;

       while(*buf && (*buf == ' '))
            buf++;
    }
    argv[argc] = NULL;

    if((is_background = (*argv[argc-1] == BACKGROUND_CH_)) != 0)
        argv[--argc] = NULL; //if the last char indicated background proccess, skip it

    return is_background;
}

void BuiltinCommand(COMMAND_STRING_ argv){
    return DEBUG_MODE(0);
}

int Eval(INPUT_CH_ARR_ cmdline){

    //So the compilers happy
    COMMAND_STRING_ command = NULL;
    //For the modified cmdline
    char buf[MAXLINE];
    int is_background = 0;

    pid_t Process_id;

    strcpy(buf, cmdline);
    is_background = Parseline(buf, command);

    if(command[0] == NULL)
        return;
    
    if(Builtin_Command(command)){
        Execute_Command(command);
    }

    //..

}

void Initalize_Shell(){
    
    //NULL so the compiler's happy
    INPUT_CH_ARR_ input = NULL;

    //Evaluate input
    do{
        
        Console_Write("Welcome to Shell_Emulator v.1.0", "Shell Write Error");
        Console_Write("\nshell$ ", "Shell Write Error");
        Console_Read(input, "Shell Read Error");

    } while(Eval(input));

}
