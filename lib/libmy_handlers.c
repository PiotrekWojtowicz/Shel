#include "libmy_handlers.h"

void Console_Write(const void* buf, char *err_msg){

    if(write(STDOUT_FILENO, buf, strlen(buf))  == -1){
        perror(err_msg);
        exit(EXIT_FAILURE);
    }
}

void Console_Read(void* buf, char *err_msg){

    if(read(STDIN_FILENO, buf, strlen(buf))  == -1){
        perror(err_msg);
        exit(EXIT_FAILURE);
    }
}

void Console_Child_Signal_Set(__sighandler_t handler){

    if(signal(SIGCHLD, handler) == SIG_ERR){
        Console_Write("Signal set error!", "Child Singal Set Write error");
        exit(EXIT_FAILURE);
    }
}

void Console_Child_Hanlder(int n){

    char mssg[MAXLINE];
    sprintf(mssg, "Child terminated\nReturing to shell\n");

    Console_Write(mssg, "Handler write error");
}

void Console_Wait_Pid(const pid_t pid, char *err_msg){

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

void Task_Fork(char *err_msg){

    const int paren_id = getpid();
    pid_t shell_child_id;

    char pid_data[MAXLINE];
        switch ((shell_child_id = fork())){

            case FORK_ERROR:
                perror(err_msg);
                exit(EXIT_FAILURE);

            case FORK_SCS:
                Console_Write("Forked successfuly!\n", "Write during fork error");
                exit(EXIT_SUCCESS);
                //execv
                break;

            default:
                sprintf(pid_data, "Pid of the child %d\n", shell_child_id);
                Console_Write(pid_data,  "Write fork error");
                Console_Wait_Pid(shell_child_id, "Console wait error");
                break;
        }
}