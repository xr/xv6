#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

#define STDIN_FILENO 0
#define MAXLINE 1024
int main(int argc, char *argv[])
{
    char line[MAXLINE];
    char *params[MAXARG];
    int n, args_index = 0;
    int i;

    char *cmd = argv[1];
    for (i = 1; i < argc; i++)
        params[args_index++] = argv[i];

    while ((n = read(STDIN_FILENO, line, MAXLINE)) > 0)
    {
        if (fork() == 0) // child process
        {
            char *arg = (char *)malloc(sizeof(line));
            int index = 0;
            for (i = 0; i < n; i++)
            {
                if (line[i] == ' ' || line[i] == '\n')
                {
                    arg[index] = 0;
                    params[args_index++] = arg;
                    index = 0;
                    arg = (char *)malloc(sizeof(line));
                }
                else
                    arg[index++] = line[i];
            }
            arg[index] = 0;

            // 每个子进程都有单独一个params，这里吧最后一个设置为0 或为null
            // https://stackoverflow.com/questions/4711449/what-does-the-symbol-0-mean-in-a-string-literal
            // c语言字符串，或者字符数组最后中断符号，不写的话，c编译器也会隐式加上
            params[args_index] = 0;
            exec(cmd, params);
        }
        else
            wait((int *)0);
    }
    exit(0);
}
