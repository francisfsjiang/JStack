#ifndef __judged__judger__
#define __judged__judger__

#include <stdio.h>

typedef struct
{
    uint problem_id;
    uint time_limit;
    uint mem_limit;
    uint code_len;
    char * code;
}run_info;

enum status_code{
    AC, //Accepted
    WA, //Wrong Answer
    PE, //Presentation Error
    CE, //Compile Error
    RE, //Runtime Error
    TLE, //Time Limit Exceeded
    MLE, //Memory Limit Exceeded
    OLE, //Output Limit Exceeded
};

typedef struct
{
    enum status_code code;
    uint time_used;
    uint mem_used;
}run_result;
run_result judge(run_info * run);

#endif /* defined(__judged__judger__) */
