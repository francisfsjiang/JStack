#ifndef __judged__checker__
#define __judged__checker__

#include <stdio.h>
#include <error.h>
#include <termios.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include <string.h>
#include <sys/user.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/syscall.h>

#include "util.h"

enum SYSCALL_STATUS{
    SS_ALLOW,
    SS_FORBIDDEN,
};

enum PROCESS_STATUS{
    PS_EXIT_SUCCESS = 0,
    PS_EXIT_ERROR,
    PS_SYSCALL,
    PS_TERM_BY_SIGNAL,
};



int syscall_checker(pid_t pid);
int parse_status(int status);


#endif /* defined(__judged__syscall_checker__) */
