#include "libmy_builtins.h"

/*
    File Globals 
    Needed to store the integral values of the program
*/

//the cd, help and exit should always be on 1st 2nd and 3rd place in the lookup table below
 static const char *builtins[]={
    "cd",
    "help",
    "exit",
    "setcolors",
    "EOF"
};

static const char *xterm_query = "xrdb -merge ~/.Xresources";

static Builtin_Info Builtin_Info_[ARRAY_LEN(builtins, char*)];

/*
    End of globals
*/

void Initialize_Built_Ins(void){
    //Initialize builitins struct
        Builtin_Info_[CD].command = "\033[00;41;5m * cd * \033[00;00m\n"; // CD builtin
        Builtin_Info_[CD].description = "Implementation of popular change directory - should work like the original one\n";

        Builtin_Info_[HELP].command = "\033[00;41;5m * help * \033[00;00m\n"; //help builtin
        Builtin_Info_[HELP].description = "Help command used to display information about builtin commands\n";

        Builtin_Info_[SETCOL].command = "\033[00;41;5m * setcolors * \033[00;00m\n"; //xterm color set
        Builtin_Info_[SETCOL].description = "Fetches the colors from the xterm ~/.Xresources. To set your custom colors edit the ~/.Xresources\n";

       Builtin_Info_[EXIT].command = "\033[00;41;5m * exit * \033[00;00m\n"; //exit builtin
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
    //Run help command 
        if(Command_Help() != 0){
            Console_Write("\033[00;41mCouldn't change the directory\n\033[00;00m", "Cd Write error");
        }
    }
    else if(!strcmp(argv[0], builtins[2])){
        //Run the exit command
        if(Command_Exit() == 0)
            return 0;
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

void Soft_Wrap(INPUT_CH_ARR_ description)PERF_IMPRV{
    //Literally to many memory copying
    //Can be a SERIOUS problem for low cache CPUs
    int screen_width = strlen(description);
    int wraps = screen_width/COLUMN_SIZE;
    INPUT_CH_ARR_ store_temp[COLUMN_SIZE];
    memset(store_temp, '\0', COLUMN_SIZE);
    //Go throught all break points and display them
    for(int i = 0; i < wraps; i++){
        //If somehow last line
        if(screen_width-(COLUMN_SIZE*i) < 0)
            break;
        memcpy(store_temp, (description+(i*COLUMN_SIZE)), COLUMN_SIZE);
        Console_Write(store_temp, "Wrap write error handler");
        Console_Write("\n", "Wrap write error handler");
    }
    //at the end dont forget the last line
    //flush the memory
    memset(store_temp, '\0', COLUMN_SIZE);
    //fill with remaining line
    int temp = (screen_width-(wraps*COLUMN_SIZE));
    memcpy(store_temp, (description+(wraps*COLUMN_SIZE)),temp);
    Console_Write(store_temp, "Wrap write error hanlder");
}

int Command_Help(void){
        Console_Write("\033[00;44m[#] Help manual\033[00;00m\n\n", "Builtin Write error");
       for(int i = 0; (ARRAY_LEN(builtins, char*)-1) > i; i++){
            Console_Write(Builtin_Info_[i].command, "Help Write error");
            Soft_Wrap(Builtin_Info_[i].description); 
        } 
        return 0;
}

int Command_Exit(void){
    //Exit command wraper
    //Check if any kids exist if so then dont exit
    int temp_status;
    if(waitpid(-1, temp_status, WNOHANG | WUNTRACED) == 0){
        Console_Write("Cannot close\nChild proccess in progress\n", "Exit Write error");
        return 0;
    }
    else
        exit(EXIT_SUCCESS);
}

