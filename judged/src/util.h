#ifndef __judged__util__
#define __judged__util__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

#include <sys/user.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <syscall.h>


void syscall_debug(int pid);

#endif /* defined(__judged__util__) */