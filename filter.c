#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXLINE 100

int main(void)
{
    char line[MAXLINE];
    FILE *fpin;
    
    if ((fpin = popen("./myuclc","r")) == NULL)
        printf("popen error");
    for (; ;){
        fputs("prompt> ", stdout);
        fflush(stdout);
        if (fgets(line, MAXLINE, fpin) == NULL)
            break;
        if (fputs(line, stdout) == EOF)
            printf("fputs error to pip");
    }
    if (pclose(fpin) == -1)
        printf("pclose error");
    putchar('\n');
    exit(0);
}

