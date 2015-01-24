#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/syslog.h>

#include "listener.hpp"

#define LOCK_FILE "/var/run/judged.pid"
#define LOCK_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

//extern int lockfile(int);

int already_running()
{
    int fd, ret;
    char buf[16];
    fd = open(LOCK_FILE, O_RDWR|O_CREAT, LOCK_MODE);
    if (fd < 0) {
        syslog(LOG_ERR, "can't open %s : %s", LOCK_FILE, strerror(errno));
    }
    ret = lockf(fd, F_TLOCK, 0);
    if (ret < 0) {
        if (errno == EACCES || errno == EAGAIN) {
            close(fd);
            return -1;
        }
        syslog(LOG_ERR, "can't lock %s : %s", LOCK_FILE, strerror(errno));
        exit(EXIT_FAILURE);
    }
    ftruncate(fd, 0);
    sprintf(buf, "%ld", (long)getpid());
    write(fd, buf, strlen(buf)+1);
    return 0;
}


void start_daemon()
{
    int pid,ret;
    
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }
    
    //become leader of new session
    ret = setsid();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    
    //ensure not session leader
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }
    
    umask(0);
    ret = chdir("/");
    if (ret < 0) {
        exit(EXIT_FAILURE);
    }
    
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

void open_log()
{
    //open_log("judged", LOG_PID, LOG_DAEMON);
    setlogmask(LOG_UPTO(LOG_DEBUG));
    openlog ("judged", LOG_CONS | LOG_PID | LOG_NDELAY | LOG_PERROR, LOG_DAEMON);
    syslog(LOG_ALERT, "log started.");
}

int main(int argc, const char * argv[]) {
    //int ret;
    open_log();
    /*start_daemon();
    ret = already_running();
    if (ret < 0) {
        syslog(LOG_ERR, "daemon already running");
        exit(EXIT_FAILURE);
    }*/
    
    prepare_listen();
    
    return 0;
}
