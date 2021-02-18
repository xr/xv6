#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    
    
int child_pid, wpid;
int status = 0;

//Father code (before child processes start)

for (int id = 1; id <= 35; id++)
{
    if ((child_pid = fork()) == 0) {
        //child code
        exit(0);
    }
}


while ((wpid = wait(&status)) > 0); // this way, the father waits for all the child processes 

//Father code (After all child processes end)
    
}