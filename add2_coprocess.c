#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#define MAXLINE 100

static void sig_pipe(int);

int main(void)
{
    int n, fd1[2], fd2[2];
    pid_t pid;
    char line[MAXLINE];

    if (signal(SIGPIPE, sig_pipe) == SIG_ERR)
        printf("signal error");

    if (pipe(fd1) < 0 || pipe(fd2) < 0)
        printf("pipe error");

    if ((pid = fork()) < 0){
        printf("pipe error");
    } else if (pid > 0) {
        close(fd1[0]);
        close(fd2[1]);

        while(fgets(line, MAXLINE, stdin) != NULL)
        {
            n = strlen(line);
            if (write(fd1[1], line, n) != n)
                printf("write error to pipe");
            if ((n = read(fd2[0], line, MAXLINE)) < 0)
                printf("read error from pipe");
            if (n == 0){
                printf("child closed pipe");
                break;
            }
            line[n] = 0;
            if (fputs(line, stdout) == EOF)
                printf("fputs error");
        }

        if (ferror(stdin))
            printf("fputs error");
        exit(0);
    } else {
        close(fd1[1]);
        close(fd2[0]);
        if (fd1[0] != STDIN_FILENO) {
            if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO)
                printf("dup2 error to stdin");
            close(fd1[0]);
        }

        if (fd2[1] != STDOUT_FILENO){
            if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO)
                printf("dup2 error to stdout");
            close(fd2[1]);
        }

        if (execl("./add2", "add2", (char *)0) < 0)
            printf("execl error");
    }
    exit(0);
}

static void sig_pipe(int signo)
{
    printf("SIGPIPE caught\n");
    exit(1);
}
