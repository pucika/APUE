#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

#define PAGER "${PAGER:-more}"
#define MAXLINE 100

int main(int argc, char* argv[])
{
    char line[MAXLINE];
    FILE *fpin, *fpout;

    if (argc != 2)
        printf("usage: a.out <pathname>");
    if ((fpin = fopen(argv[1], "r")) == NULL)
        printf("can't open %s", argv[1]);

    if ((fpout = popen(PAGER, "w")) == NULL)
        printf("popen error");
    while(fgets(line, MAXLINE, fpin) != NULL)
    {
        if (fputs(line, fpout) == EOF)
            printf("fputs error to pipe");
    }
    if (ferror(fpin))
        printf("fgets errror");
    if (pclose(fpout) == -1)
        printf("pclose error");
    exit(0);
}
