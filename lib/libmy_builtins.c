#include "libmy_builtins.h"

/*
    File Globals 
    Needed to store the integral values of the program
*/

 static const char *builtins[]={
    "cd",
    "help",
    "exit",
    "EOF"
};

static Builtin_Info Builtin_Info_[ARRAY_LEN(builtins, char*)];

/*
    End of globals
*/

void Initialize_Built_Ins(void){
    //Initialize builitins struct
        Builtin_Info_[CD].command = "cd";
        Builtin_Info_[CD].description = "Implementation of popular change directory - (should) work like the original one\n";

        Builtin_Info_[HELP].command = "help";
        Builtin_Info_[HELP].description = "Help command used to display information about builtin commands\n";

       Builtin_Info_[EXIT].command = "exit";
       Builtin_Info_[EXIT].description = "Used to exit the shell\n";
}

int Find_Built_Command(COMMAND_STRING_ argv) PERF_IMPRV{

    //Linear time complexity
    //Possible bottlneck
    int command_count = ARRAY_LEN(builtins, char*);
    for( int i = 0; i < command_count; i++){
        if(!strcmp(argv[0], builtins[i]))
            return 1;
    }
    return -1;
}

int Execute_Built_In(COMMAND_STRING_ argv){
    //Check the BuiltIn
   if(!strcmp(argv[0], builtins[0])){
    //Run the change directory
        if(Command_Cd(argv[1]) == -1){
            Console_Write("\033[00;41mCouldn't change the directory\n\033[00;00m", "Cd Write error");
            return -1;
        } 
   }
   else if(!strcmp(argv[0], builtins[1])){
        Console_Write("Heh you're gonna need that using this shell\n\033[00;00m", "Builtin Write error");
       for(int i = 0; (ARRAY_LEN(builtins, char*)-1) > i; i++){
            Console_Write(Builtin_Info_[i].description, "Help Write error");
        } 
    }
    return 1;
}

int Command_Cd(INPUT_CH_ARR_ directory){
        if(!strcmp(directory,(char*)"~")){
            char *temp = NULL;
            if((temp = getlogin()) == NULL){
                Console_Write("Could not resolve the username\n", "Cd Write error");
                return -1;
            }
            char complete_the_path[32];
            sprintf(complete_the_path, "/home/%s", temp);
            if(chdir(complete_the_path)!=0){
             perror("Cannot change the directory");
                return -1;
            }
            return 0;
        }
        if(chdir(directory)!=0){
            perror("Cannot change the directory");
            return -1;
        }
    return 0;
}


