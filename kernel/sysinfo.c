#include "types.h"
#include "sysinfo.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "syscall.h"
#include "defs.h"

extern uint nproc(void);

uint64
sys_sysinfo(void)
{
  uint64 si; // user pointer to struct sysinfo
  struct sysinfo info;

  if(argaddr(0, &si) < 0)
    return -1;

  info.freemem = free_memory();
  info.nproc = nproc();

  struct proc *p = myproc();

  if(copyout(p->pagetable, si, (char *)&info, sizeof(info)) < 0)
      return -1;
    return 0;
  
}
