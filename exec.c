#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char* env_init[] = {"USER=unknown", "PATH=/tmp:.", NULL};

int main(void)
{
    pid_t pid;
    if ((pid = fork()) < 0){
        printf("fork error");
    } else if (pid == 0) {
        if (execle("/home/zdl/code/mycode/APUE/echoall", 
                    "echoall", "myarg1", "MY ARG2", (char*)0, env_init) < 0)
            printf("execle error");
    }

    if (waitpid(pid, NULL, 0) < 0)
        printf("wait error");

    if ((pid = fork()) < 0){
        printf("fork error");
    } else if (pid == 0) {
        if (execlp("echoall", "echoall", "only 1 arg", (char*)0) < 0)
            printf("execlp error");
    }

    exit(0);
    
}
