#include "judger.h"

int get_file_fd(uint probelm_id, int * fd, const char * file_path, const char * target_name)
{
    char file_name[30];
    unsigned long len;
    strcpy(file_name, file_path);
    len = strlen(file_name);
    sprintf(file_name+len, "%d/", probelm_id);
    len = strlen(file_name);
    sprintf(file_name+len, "%s", target_name);
    *fd = open(file_name, O_RDONLY);
    if (*fd < 0) {
        syslog(LOG_INFO, "open file %s failed. %s", file_name, strerror(errno));
        return -1;
    }
    syslog(LOG_INFO, "open file %s", file_name);
    return 0;
}

int judge(run_param * run)
{
    //run_result result;
    char * temp_dir;
    //struct passwd *nobody= getpwnam("nobody");
    int pid, null_dev;
    int ret;
    
    int input_fd, output_fd;
    syslog(LOG_DEBUG, "%s", TEMP_DIR_TEMPLATE);
    temp_dir = mkdtemp(TEMP_DIR_TEMPLATE);
    if (temp_dir == NULL) {
        syslog(LOG_ERR, "err creating temp dir. %s", strerror(errno));
        return -1;
    }
    
    get_file_fd(run->problem_id, &input_fd, IO_DIR, "input.int");
    output_fd =
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