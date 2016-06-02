#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int n;
    int fd[2];
    pid_t pid;
    char line[100];

    if (pipe(fd) < 0)
        printf("pip error");
    if ((pid = fork()) < 0)
        printf("fork error");
    else if (pid > 0){
        close(fd[0]);
        write(fd[1], "hello world\n", 12);
    } else {
        close(fd[1]);
        n = read(fd[0], line, 100);
        printf("%d", n);
        read(STDOUT_FILENO, line, n);
    }
    exit(0);
}
