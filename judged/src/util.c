
#include "util.h"

void syscall_debug_str(char * const name, pid_t pid, ulong addr, ulong len)
{
    char * buffer;
    int long_size = sizeof(long);
    union u {
        long val;
        char chars[long_size];
    }data;
    int i;
    buffer = malloc(sizeof(char)*len);
    for(i=0;i<len;i+=long_size){
        data.val = ptrace(PTRACE_PEEKDATA, pid, addr+i, NULL);
        memcpy(buffer+i, data.chars, (size_t)long_size);
    }
    buffer[len]=0;
    syslog(LOG_DEBUG, "%s: %s", name, buffer);
}

void syscall_debug_const_str(char * const name, pid_t pid, ulong addr)
{
    char * buffer;
    int long_size = sizeof(long);
    int len = 100;
    union u {
        long val;
        char chars[long_size];
    }data;
    int i;
    buffer = malloc(sizeof(char)*len);
    for(i=0;i<len;i+=long_size){
        data.val = ptrace(PTRACE_PEEKDATA, pid, addr+i, NULL);
        memcpy(buffer+i, data.chars, (size_t)long_size);
        if (*(buffer+i)==0)break;
    }
    buffer[len]=0;
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
        case SYS_write:
            syslog(LOG_DEBUG, "%d SYS_write:", SYS_write);
            syslog(LOG_DEBUG, "fd: %lld", regs.rdi);
            syscall_debug_str("content:", pid, regs.rsi, regs.rdx);
            break;
        case SYS_read:
            syslog(LOG_DEBUG, "%d SYS_read:", SYS_read);
            syslog(LOG_DEBUG, "fd: %lld", regs.rdi);
            syscall_debug_str("content:", pid, regs.rsi, regs.rdx);
            break;
        case SYS_open:
            syslog(LOG_DEBUG, "%d SYS_open:", SYS_open);
            syscall_debug_const_str("filename:", pid, regs.rdi);
            break;
        case SYS_access:
            syslog(LOG_DEBUG, "%d SYS_access:", SYS_access);
            syscall_debug_const_str("filename:", pid, regs.rdi);
            break;
        default:
            break;
    }

}