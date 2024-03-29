#include "libmy_builtins.h"
#include "libmy_handlers.h"
#include "libmy_shell.h"
#include <stdlib.h>
#include <string.h>

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

static Builtin_Info Builtin_Info_[ARRAY_LEN(builtins, char*)];

/*
    End of globals
*/

void Initialize_Built_Ins(void){
    //Initialize builitins struct
    //
    //   New idea - fetch the text from a file.
    //
        Builtin_Info_[CD].command = "\033[00;41;5m * cd * \033[00;00m\n"; // CD builtin
        Builtin_Info_[CD].description = "Implementation of popular change directory - should work like the original one\n";

        Builtin_Info_[HELP].command = "\033[00;41;5m * help * \033[00;00m\n"; //help builtin
        Builtin_Info_[HELP].description = "Help command used to display information about builtin commands\n";

        Builtin_Info_[SETCOL].command = "\033[00;41;5m * setcolors * \033[00;00m\n"; //xterm color set
        Builtin_Info_[SETCOL].description = "Sets the font its size and background color. Requires three arguments:  \033[00;21m<FontName> <FontSize> <BackgroundColor>\033[00;00m\n";

       Builtin_Info_[EXIT].command = "\033[00;41;5m * exit * \033[00;00m\n"; //exit builtin
       Builtin_Info_[EXIT].description = "Used to exit the shell\nUse the -f option to FORCE exit\n";
}

int Find_Built_Command(COMMAND_STRING_ argv) PERF_IMPRV{

    //Linear time complexity
    //Possible bottlneck
    int command_count = ARRAY_LEN(builtins, char*);
    for( int i = 0; i < command_count; i++){
        if(!strcmp(argv[0], builtins[i])){
            return 1;
        }
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
        if(Command_Exit(argv) == 0)
            return 0;
    }
   else if(!strcmp(argv[0], builtins[3])){
	//Run set colors
	if(Command_SetColors(argv) == 0){
	    return 0;
	}	
   }
    return 1;
}

int Command_SetColors(COMMAND_STRING_ argv){

    // 	FONT 		    FONT SIZE 		BG_COLOR
    if(argv[1] == NULL || argv[2] == NULL || argv[3] == NULL)
	    return 0;

    //Opening the Xresources file
    int file_desc;
    if((file_desc = open(XTERM_COFNIG, O_APPEND | O_WRONLY)) == -1){
	perror("Could not open Xresources");
	exit(EXIT_FAILURE);
    }

    //Write to file
    char temp_array[64];
    sprintf(temp_array, "xterm*faceName: %s\n", argv[1]);

    if(write(file_desc, temp_array, (sizeof("xterm*faceName: ")+strlen(argv[1]))) == -1){
        perror("Could not update Xresources");
	exit(EXIT_FAILURE);
    }

    bzero(temp_array, 64);
    sprintf(temp_array, "xterm*faceSize: %s\n", argv[2]);

    if(write(file_desc, temp_array, (sizeof("xterm*faceSize: ")+ARRAY_LEN(argv[2],char*))+1) == -1){
        perror("Could not update Xresources");
	exit(EXIT_FAILURE);
    }

    bzero(temp_array, 64);
    sprintf(temp_array, "xterm*background: %s\n", argv[3]);

    if(write(file_desc, temp_array, (sizeof("xterm*background: ")+strlen(argv[3]))) == -1){
        perror("Could not update Xresources");
	exit(EXIT_FAILURE);
    } 

    return 1;

}

int Command_Cd(INPUT_CH_ARR_ directory){
        //if no dir just skip
        if(directory == NULL){
            Console_Write("\033[00;41mNo directory specified\n\033[00;00m", "Cd Write error");
            return -1;
        }

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
    int wraps = screen_width/(COLUMN_SIZE);
    INPUT_CH_ARR_ store_temp[COLUMN_SIZE];
    memset(store_temp, '\0', (COLUMN_SIZE*sizeof(char *)));
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
    memset(store_temp, '\0',(COLUMN_SIZE*sizeof(char *)));
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

int Command_Exit(COMMAND_STRING_ argv){
    //Force
    if(argv[1]!=NULL)//check if exists
    if(!strcmp(argv[1], "-f")){
        _exit(EXIT_FAILURE);
    }
    //Exit command wraper
    //Check if any kids exist if so then dont exit
    if(waitpid(-1, NULL, WNOHANG | WUNTRACED) == 0){
        Console_Write("Cannot close\nChild proccess in progress\nSee the -f option\n", "Exit Write error");
        return 0;
    }
    else
        exit(EXIT_SUCCESS);
}
