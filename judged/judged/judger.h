#ifndef __judged__judger__
#define __judged__judger__

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <syslog.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>


#define TEMP_DIR_TEMPLATE "/tmp/judgetmp.XXXXXXXX"


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
int judge(run_info * run);





#endif /* defined(__judged__judger__) */
