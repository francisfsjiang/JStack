#include "judger.h"


int judge(run_info * run)
{
    run_result result;
    char * temp_dir;
    struct pwd* nobody= getpwnam("nobody");
    int pid, null_dev;
    int ret;
    
    temp_dir = mkdtemp(TEMP_DIR_TEMPLATE);
    if (temp_dir == NULL) {
        syslog(LOG_ERR, "err creating temp dir. %s", strerror(errno));
        return -1;
    }
    
    
    
    pid = fork();
    if (pid < 0) {
        syslog(LOG_ERR,"judge fork error");
        return -1;
    }
    if (pid == 0) {
        ret = chroot(temp_dir);
        if (ret < 0) {
            syslog(LOG_ERR, "chroot failed. %s", strerror(errno));
            exit(EXIT_FAILURE);
        }
        chdir("/");
        null_dev = open("/dev/null", O_RDWR);
        dup2(null_dev, STDERR_FILENO);
        
        
    }
    else if (pid > 0){
        
    }
    
    return 0;
}