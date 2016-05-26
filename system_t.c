#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int status;
    if ((status = system("date")) < 0)
        printf("system() error");
    if ((status = system("nosuchcommand")) < 0)
        printf("system() error");
    if ((status = system("who; exit 44")) < 0)
        printf("system() error");
    exit(0);
}
