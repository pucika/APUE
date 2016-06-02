#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int c;
    while ((c = getchar()) != EOF){
        if (isupper(c))
            c = tolower(c);
        if (putchar(c) == EOF)
            printf("output error");
        if (c == '\n')
            fflush(stdout);
    }
    exit(0);
}
