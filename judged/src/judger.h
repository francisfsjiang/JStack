#ifndef __judged__judger__
#define __judged__judger__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/user.h>

#include "checker.h"

#define INPUT_DIR "/tmp/data"

typedef struct
{
    uint problem_id;
    uint lang;
    uint time_limit;
    uint mem_limit;
    uint code_len;
    char * code;
}run_param;

enum status_code{
    AC=0, //Accepted
    WA, //Wrong Answer
    PE, //Presentation Error
    CE, //Compile Error
    RE, //Runtime Error
    TLE, //Time Limit Exceeded
    MLE, //Memory Limit Exceeded
    OLE, //Output Limit Exceeded
    FIN,
};

enum lang{
    C=0,
    CXX,
    JAVA,
    CSH,
    PY,
    RB,
    
};



typedef struct
{
    enum status_code code;
    uint time_used;
    uint mem_used;
}run_result;
int judge(run_param * run);





#endif /* defined(__judged__judger__) */
