#include "libmy_handlers.h"

void Console_Write(const void* buf, ERROR_MSSG_){

    if(write(STDOUT_FILENO, buf, strlen(buf))  == -1){
        perror(err_msg);
        exit(EXIT_FAILURE);
    }
}

void Console_Read(void* buf, ERROR_MSSG_){

    if(read(STDIN_FILENO, buf, MAXLINE) == -1){
        perror(err_msg);
        exit(EXIT_FAILURE);
    }
}

void Console_Signal_Set(void(*my_new_hanlder)(int, siginfo_t *, void*)){
    struct sigaction new_act;
    new_act.sa_flags = SA_SIGINFO | SA_RESTART;
    new_act.sa_sigaction = my_new_hanlder;

    if(sigaction(SIGCHLD, &new_act, NULL) == -1){
        perror("SIGCHLD could not have been set");
        _exit(EXIT_FAILURE);
    }

    if(sigaction(SIGINT, &new_act, NULL) == -1){
        perror("SIGCHLD could not have been set");
        _exit(EXIT_FAILURE);
    }

}

void Console_Handler(int signo, siginfo_t *info, void *context){

    char mssg[MAXLINE];
    switch (signo)
    {
    case SIGCHLD:
        sprintf(mssg, "[DEBUG] Child terminated\n[DEBUG] Returing to shell\n");
        Console_Write(mssg, "Handler write error");
        break;

    case SIGINT:
        Console_Write("\b\b  \b\b", "Error");
        break;
    
    default:
        break;
    };
}

void Console_Wait_Pid(const pid_t pid, ERROR_MSSG_){

    int stat_loc;
    if(waitpid(pid, &stat_loc,0) == -1){
        perror(err_msg);
        exit(EXIT_FAILURE);
    }
    
    if(stat_loc != 0){
        Console_Write("Child proccess execution failed\n", "Wait write error");
        exit(EXIT_FAILURE);
    }
}

pid_t Task_Fork(COMMAND_STRING_ command, ERROR_MSSG_){

    pid_t shell_child_id;

    char pid_data[MAXLINE];
    char eve_command[MAXLINE];
    sprintf(eve_command,"/bin/%s",command[0]);
        switch ((shell_child_id = fork())){

            case FORK_ERROR:
                perror(err_msg);
                exit(EXIT_FAILURE);

            case FORK_SCS:
                if(execv(eve_command, command) < 0){
                    perror("Cannot run command, error occured");
                    exit(EXIT_FAILURE);
                }

            default:
                sprintf(pid_data, "[DEBUG] Pid of the child %d\n", shell_child_id);
                Console_Write(pid_data,  "Write fork error");
                return shell_child_id; 
        }
}

void Console_AtExit(void){
    /*Temporarly empty exit*/
    exit(1);
}
