#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int p[2];
    char a = 'a';

    pipe(p);
    int pid = fork();
    if (pid == 0)
    {
        read(p[0], &a, 1);
        close(p[0]);
        printf("%d: received ping\n", getpid());
        write(p[1], &a, 1);
        close(p[1]);
        exit(0);
    } else {
        write(p[1], &a, 1);
        close(p[1]);
        wait((int *) 0);
        read(p[0], &a, 1);
        close(p[0]);
        printf("%d: received pong\n", getpid());
        exit(0);
    }
}