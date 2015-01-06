#include <errno.h>
#include "listener.h"

char buffer[MAX_BUFFER_SIZE];

int parse_run_info(char * recv_buffer, ssize_t recv_size, run_info * run_info)
{
    if (recv_size <= 12) {
        return -1;
    }
    run_info->problem_id = (uint)recv_buffer[0];
    run_info->time_limit = (uint)recv_buffer[4];
    run_info->mem_limit = (uint)recv_buffer[8];
    run_info->code_len = (uint)(recv_size - 12);
    run_info->code = &buffer[12];
    return 0;
}

void main_loop(int socket_fd)
{
    struct sockaddr in_addr;
    socklen_t in_addr_len;
    int in_socket_fd;
    ssize_t recv_size;
    run_info run;
    int ret;
    while (1) {
        in_socket_fd = accept(socket_fd, &in_addr, &in_addr_len);
        syslog(LOG_INFO, "accept from %s.", in_addr.sa_data);
        recv_size = recv(in_socket_fd, buffer, sizeof(buffer), 0);
        if (recv_size < 0) {
            syslog(LOG_ERR, "recv failed");
            continue;
        }
        syslog(LOG_INFO, "recv %zd bytes", recv_size);
        ret = (int)send(in_socket_fd, 0, sizeof(0), 0);
        if (ret < 0) {
            syslog(LOG_ERR, "reply failed.");
            continue;
        }
        parse_run_info(buffer, recv_size, &run);
        
    }
}

void prepare_listen()
{
    int socket_fd;
    int ret;
    struct sockaddr sock_addr;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        syslog(LOG_ERR, "socket create failed.");
        exit(EXIT_FAILURE);
    }
    
    sock_addr.sa_family = AF_INET;
    strcpy(sock_addr.sa_data, LISTEN_ADDR);
    
    ret = bind(socket_fd, &sock_addr, sizeof(LISTEN_ADDR));
    if (ret < 0) {
        syslog(LOG_ERR, "socket bind failed. %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    ret = listen(socket_fd, 8);
    if (ret < 0) {
        syslog(LOG_ERR, "socket listen failed.");
        exit(EXIT_FAILURE);
    }
    
}

