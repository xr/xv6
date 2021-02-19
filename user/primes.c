#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int sub(int pip[])
{
    // close write end needs to be placed here
    // if put after read() at line 12
    // the last call will not send anything here, thus read is pending here
    close(pip[1]);
    int pri;
    int more = read(pip[0], &pri, 1);

    if (more != 0)
    {
        printf("prime %d\n", pri);

        int child_pip[2];
        pipe(child_pip);

        if (fork() == 0)
        {
            sub(child_pip);
        }
        else
        {
            for (;;)
            {
                int d;
                int ret = read(pip[0], &d, 1);
                if (ret == 0)
                {
                    break;
                }
                if (d % pri != 0)
                {
                    write(child_pip[1], &d, 1);
                }
            }
            close(pip[0]);
            close(child_pip[1]);
            wait(0);
        }
    }

    exit(0);
}

int main(int argc, char *argv[])
{

    int p[2];
    pipe(p);

    if (fork() == 0)
    {
        sub(p);
    }
    else
    {
        close(p[0]);
        printf("prime %d\n", 2);
        for (uint8 id = 3; id <= 35; id++)
        {
            if (id % 2 != 0)
            {
                write(p[1], &id, 1);
            }
        }
        close(p[1]);
        wait(0);
    }
    exit(0);
}