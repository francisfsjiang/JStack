//
//  syscall_checker.h
//  judged
//
//  Created by Neveralso on 15/1/7.
//  Copyright (c) 2015年 neveralso. All rights reserved.
//

#ifndef __judged__checker__
#define __judged__checker__

#include <stdio.h>
#include <error.h>
#include <termios.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/syscall.h>

enum check_status_code{
    CS_SUCCESS = 0,
    CS_ERROR,
    CS_SYSCALL,
    CS_ALLOW,
    CS_FORBIDDEN,
};

int syscall_checker(pid_t pid);
int check_status(int status);


#endif /* defined(__judged__syscall_checker__) */
