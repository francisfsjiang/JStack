//
//  syscall_checker.c
//  judged
//
//  Created by Neveralso on 15/1/7.
//  Copyright (c) 2015年 neveralso. All rights reserved.
//

#include "checker.h"

//find from bits/syscall.h unistd_64.h
const long syscall_white[] = {
        59,         //execv
};

int _bin_search(long syscall, int start, int end)
{
    int mid = (start + end) >>1;
    if (start > end) {
        return 0;
    }
    if (syscall_white[mid] == syscall) return 1;
    else if (syscall_white[mid] > syscall) return _bin_search(syscall, start, mid-1);
    else return _bin_search(syscall, mid+1, end);
}

int _search(long syscall)
{
    return _bin_search(syscall, 0, sizeof(syscall_white)/4-1);
}

int syscall_checker(pid_t pid)
{
    int ret;
    long syscall = ptrace(PTRACE_PEEKUSER, pid, (void *)(8*ORIG_RAX), NULL);
    syslog(LOG_DEBUG, "find syscall id : %ld.\n", syscall);
    ret =  _search(syscall);
    if (ret){
        return CS_ALLOW;
    }
    else {
        return CS_FORBIDDEN;
    }
}

int check_status(int status){
    syslog(LOG_DEBUG, "get status code :%d", status);
    if (WIFEXITED(status)) //call ing exit(3) or _exit(2), or by returning from main().
    {
        if (WEXITSTATUS(status) == 0)
            return CS_SUCCESS;
        else
            return CS_ERROR;
    }

    if (WIFSIGNALED(status))
        return CS_ERROR;

    if (WIFSTOPPED(status))
    {
        int sig = WSTOPSIG(status);
        syslog(LOG_DEBUG, "get stopped sig : %d", sig);
        if (sig == SIGTRAP)
        {
            return CS_SYSCALL;
        }
    }
    return CS_SUCCESS;
}