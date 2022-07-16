#include "libmy_shell.h"

int Parseline(INPUT_CH_ARR_ buf, COMMAND_STRING_ argv){

    INPUT_CH_ARR_ begin = NULL;
    //Number of arguments
    int argc = 0;
    int is_background;

    //if just EOF
    if(strlen(buf)==1 || strlen(buf) == 0){
        argv[0] = "EOF";
        return 0;
    }
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

int Builtin_Command(COMMAND_STRING_ argv){
    if(_DEBUG){
        return 0;
    }

    if(!strcmp(argv[0], "EOF")){
        return 1;
    }

    return 0;
}

int Eval(INPUT_CH_ARR_ cmdline){

    //So the compilers happy
    char* command[MAXLINE];
    //For the modified cmdline
    char buf[MAXLINE];
    int is_background = 0;

    pid_t proc_pid;

    strcpy(buf, cmdline);
    is_background = Parseline(buf, command);

    if(command[0] == NULL){
        Console_Write("Unsupported format\nExiting...\n", "Eval exit error");
        return 0;
    }
    
   if(Builtin_Command(command)){
        return 1;
    }

    proc_pid = Task_Fork(command, "Task fork Eval error");

    if(!is_background){
        int status;
        if(waitpid(proc_pid, &status, 0) < 0){
            perror("Waitpid error - Task cannot complete properly");
            exit(EXIT_FAILURE);
        }
    }

    return 1;
}

//Everyhting starts here
void Initalize_Shell(){

    char input[MAXLINE];
    Console_Write("Welcome to Shell_Emulator v.1.0\n", "Shell Write Error");

    do{
        memset(input, '\0', MAXLINE);
        Console_Write("shell$ ", "Shell Write Error");
        Console_Read(input, "Shell Read Error");
    } while(Eval(input));

}
