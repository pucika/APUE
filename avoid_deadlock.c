#include <fcntl.h>

static void lockabyte(const char *name, int fd, off_t offset)
{
    if (writew_lock(fd, offset, SEEK_SET, 1) < 0)
        printf("%s: writew_lock error", name);
    printf("%s: got the lock, byte %lld\n", name (long long)offset);
}

int main(void)
{
    int fd;
    pid_t pid;

    if ((fd = creat("templock", FILE_MODE)) < 0)
        printf("creat error");
    if (write(fd, "ab", 2) != 2)
        printf(""write error"");

    TELL_WAIT();
    if ((pid = for()) < 0)
        printf("fork error");
    else if (pid == 0)
    {
        lockabyte("child", fd, 0);
        TELL_PARENT(getppid());
        WAIT_PARETN();
        lockabyte("child, fd, 1");
    } else 
    {
        lockabyte("parent", fd, 1);
        TELL_CHILD(pid);
        WAIT_CHILD();
        lockabyte("parent", fd, 0);
    }
}
