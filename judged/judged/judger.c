#include "judger.h"

void get_input_fd(uint probelm_id, int * fd, const char * file_path)
{
    char file_name[20];
    unsigned long len;
    strcpy(file_name, file_path);
    len = strlen(file_path);
    itoa(probelm_id, file_name + len, 10);
    
    
}

int judge(run_param * run)
{
    run_result result;
    char * temp_dir;
    struct passwd *nobody= getpwnam("nobody");
    int pid, null_dev;
    int ret;
    
    int input_fd, output_fd;
    
    temp_dir = mkdtemp(TEMP_DIR_TEMPLATE);
    if (temp_dir == NULL) {
        syslog(LOG_ERR, "err creating temp dir. %s", strerror(errno));
        return -1;
    }
    //input_file = open(const char *, <#int, ...#>)
    //output_file = open(<#const char *#>, <#int, ...#>)
    null_dev = open("/dev/null", O_RDWR);
    
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
        
        dup2(null_dev, STDERR_FILENO);
        
        
    }
    else if (pid > 0){
        
    }
    
    return 0;
}