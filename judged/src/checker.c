
#include "checker.h"
#include "syscall_table.h"

int syscall_counter[sizeof(syscall_table)];

int debug_flag;
void syscall_checker_init()
{
    memset(syscall_counter, 0, sizeof(syscall_counter));
    debug_flag = 0;
}



int syscall_checker(pid_t pid)
{

    int ret;
    ulong syscall;
    struct user_regs_struct regs;
    //long syscall = ptrace(PTRACE_PEEKUSER, pid, (void *)(8*ORIG_RAX), NULL);
    ptrace(PTRACE_GETREGS, pid, NULL, &regs);
    syscall = regs.orig_rax;
    syslog(LOG_DEBUG, "find syscall id : %ld.\n", syscall);
    //if (syscall == 11){
    //    debug_flag = 1;
    //}
    //if (debug_flag)
    //syscall_debug(pid);
    return SS_ALLOW;
    if (syscall_table[syscall] == 1){
        return SS_ALLOW;
    }
    else if (syscall_table[syscall] == 2
            && syscall_counter[syscall] < syscall_limit[syscall]){
        syscall_counter[syscall]++;
        return SS_ALLOW;
    }
    else {
        return SS_FORBIDDEN;
    }
}

int parse_status(int status){
    //syslog(LOG_DEBUG, "get status code :%d", status);
    if (WIFEXITED(status)) //call ing exit(3) or _exit(2), or by returning from main().
    {
        if (WEXITSTATUS(status) == 0)
            return PS_EXIT_SUCCESS;
        else
            return PS_EXIT_ERROR;
    }

    if (WIFSIGNALED(status))
        return PS_TERM_BY_SIGNAL;

    if (WIFSTOPPED(status))
    {
        int sig = WSTOPSIG(status);
        //syslog(LOG_DEBUG, "get stopped sig : %d", sig);
        if (sig == SIGTRAP)
        {
            return PS_SYSCALL;
        }
    }
    return PS_EXIT_ERROR;
}