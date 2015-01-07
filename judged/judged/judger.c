#include "judger.h"

char TEMP_DIR_TEMPLATE[] = "/tmp/judgetmp.XXXXXX";

char *code_file_name[]={
        "code.c",
        "code.cpp",
        "code.java",
};

char *compile_cmd[]={
        "gcc code.c -o code",
        "g++ code.cpp -o cpp"
};

void get_file_fd(uint probelm_id, int * fd, const char * file_path, const char * target_name, int mode)
{
    char file_name[30];
    unsigned long len;
    strcpy(file_name, file_path);
    len = strlen(file_name);
    sprintf(file_name+len, "/%d/", probelm_id);
    len = strlen(file_name);
    sprintf(file_name+len, "%s", target_name);
    *fd = open(file_name, mode);
    syslog(LOG_INFO, "open file %s", file_name);
}

void prepare_files(run_param* run, int * input_fd, int * output_fd, int * code_fd)
{
    get_file_fd(run->problem_id, input_fd, INPUT_DIR, "test.in", O_RDONLY);
    *output_fd = open("code.out", O_WRONLY|O_CREAT);
    ftruncate(*output_fd, 0);
    syslog(LOG_DEBUG, "code num : %s.",code_file_name[run->lang]);
    syslog(LOG_DEBUG, "code file : %s.",code_file_name[run->lang]);
    *code_fd = open(code_file_name[run->lang], O_WRONLY|O_CREAT);
    ftruncate(*code_fd, 0);
};

int judge(run_param * run)
{
    //run_result result;
    char * temp_dir;
    //struct passwd *nobody= getpwnam("nobody");
    int pid, null_dev;
    int ret;
    
    int input_fd, output_fd, code_fd;

    temp_dir = mkdtemp(TEMP_DIR_TEMPLATE);
    if (temp_dir == NULL) {
        syslog(LOG_ERR, "err creating temp dir. %s", strerror(errno));
        return -1;
    }
    syslog(LOG_DEBUG, "temp_dir made %s.", TEMP_DIR_TEMPLATE);
    
    chdir(temp_dir);
    
    prepare_files(run, &input_fd, &output_fd, &code_fd);
    if (input_fd <0 || output_fd<0 || code_fd<0)
    {
        syslog(LOG_ERR, "file prepare failed. %s", strerror(errno));
    }

    ret = (int)write(code_fd, run->code, strlen(run->code));
    if (ret < 0) {
        syslog(LOG_ERR, "code write err. %s", strerror(errno));
        return -1;
    }
    close(code_fd);
    
    syslog(LOG_INFO, "exec %s", compile_cmd[run->lang]);
    execl(compile_cmd[run->lang], NULL);
    
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
        chdir("temp_dir");
        
        dup2(null_dev, STDERR_FILENO);
        
        
    }
    else if (pid > 0){
        
    }
    
    return 0;
}