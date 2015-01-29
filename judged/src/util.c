
#include "util.h"

void syscall_debug_str(char * const name, pid_t pid, ulong addr, ulong len)
{
    char * buffer;
    long pos;
    int i;
    buffer = malloc(sizeof(char)*len);
    for(i=0;i<len;i++){
        pos = ptrace(PTRACE_PEEKDATA, pid, addr+i, NULL);
        memcpy(buffer+i, (void*)pos, sizeof(char));
    }
    buffer[len]=0;
    syslog(LOG_DEBUG, "%s: %s", name, buffer);
}

void syscall_debug_const_str(char * const name, pid_t pid, ulong addr)
{
    char * buffer;
    int len = 100;
    int i;
    long pos;
    buffer = malloc(sizeof(char)*len);
    for(i=0;i<len;i++){
        pos = ptrace(PTRACE_PEEKDATA, pid, addr+i, NULL);
        memcpy(buffer+i, (void*)pos, sizeof(char));
        if(*(buffer+i)==0)break;
    }
    syslog(LOG_DEBUG, "%s: %s", name, buffer);
}

void syscall_debug(int pid)
{
    //%rdi, %rsi, %rdx, %rcx, %r8, %r9
    //long orig_eax;
    //long params[3];
    struct user_regs_struct regs;
    ptrace(PTRACE_GETREGS, pid, NULL, &regs);
    //orig_eax = ptrace(PTRACE_PEEKUSER, pid, 8 * ORIG_RAX, NULL);
    //params[0] = ptrace(PTRACE_PEEKUSER, pid, 8 * RDI, NULL);
    //params[1] = ptrace(PTRACE_PEEKUSER, pid, 8 * RSI, NULL);
    //params[2] = ptrace(PTRACE_PEEKUSER, pid, 8 * RDX, NULL);
    switch (regs.orig_rax){
        case SYS_execve:
            syslog(LOG_DEBUG, "%d SYS_execve:", SYS_execve);
            //syscall_debug_const_str("path", pid, regs.rsp);
            break;
        case SYS_write:
            syslog(LOG_DEBUG, "%d SYS_write:", SYS_write);
            syscall_debug_str("content", pid, regs.rsi, regs.rdx);
            syslog(LOG_DEBUG, "fd: %lld", regs.rdi);
            break;
        case SYS_open:
            syslog(LOG_DEBUG, "%d SYS_open:", SYS_open);
            //syslog(LOG_DEBUG, "path: %s", (char*)params[0]);
            break;
        default:
            break;
    }

}