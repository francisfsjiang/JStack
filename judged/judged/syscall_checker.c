//
//  syscall_checker.c
//  judged
//
//  Created by Neveralso on 15/1/7.
//  Copyright (c) 2015年 neveralso. All rights reserved.
//

#include "syscall_checker.h"


const int syscall_white[] = {
    0
};

int _bin_search(int syscall, int start, int end)
{
    int mid = (start + end) >>1;
    if (start > end) {
        return 0;
    }
    if (syscall_white[mid] == syscall) return 1;
    else if (syscall_white[mid] > syscall) return _bin_search(syscall, start, mid-1);
    else return _bin_search(syscall, mid+1, end);
}

int _search(int syscall)
{
    return _bin_search(syscall, 0, sizeof(syscall_white)/4-1);
}

int syscall_checker(int syscall)
{
    return _search(syscall);
}