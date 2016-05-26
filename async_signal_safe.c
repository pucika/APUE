#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
static void my_alarm(int signo)
{
    struct passwd* rootptr;
    printf("in signal handler\n");
    if ((rootptr = getpwnam("root")) == NULL)
        printf("getpwnam(root) error");
    printf("in signal, %s\n", rootptr->pw_name);
    alarm(1);
}

int main(void)
{
    struct passwd* ptr;
    signal(SIGALRM, my_alarm);
    alarm(2);
    for (; ;)
    {
        printf("in for loop\n");
        if ((ptr = getpwnam("zdl")) ==NULL)
            printf("getpwnam error");
        if (strcmp(ptr->pw_name, "zdl") != 0)
            printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
    }
}
