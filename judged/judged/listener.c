#include <errno.h>
#include "listener.h"
#include "judger.h"

char buffer[MAX_BUFFER_SIZE];

int parse_run_param(char * recv_buffer, ssize_t recv_size, run_param * param)
{
    if (recv_size <= 16) {
        return -1;
    }
    param = (run_param *)recv_buffer;
    return 0;
}

void main_loop(int socket_fd)
{
    struct sockaddr_in in_addr;
    socklen_t in_addr_len;
    int in_socket_fd;
    ssize_t recv_size;
    run_param run;
    int ret;
    while (1) {
        in_socket_fd = accept(socket_fd, (struct sockaddr *)&in_addr, &in_addr_len);
        syslog(LOG_INFO, "accept from %s.", inet_ntoa(in_addr.sin_addr));
        recv_size = recv(in_socket_fd, buffer, sizeof(buffer), 0);
        if (recv_size < 0) {
            syslog(LOG_ERR, "recv failed");
            continue;
        }
        syslog(LOG_INFO, "recv %zd bytes", recv_size);
        ret = (int)send(in_socket_fd, "success", sizeof("success"), 0);
        if (ret < 0) {
            syslog(LOG_ERR, "reply failed. %s", strerror(errno));
            continue;
        }
        ret = parse_run_param(buffer, recv_size, &run);
        if (ret < 0){
            syslog(LOG_ERR, "recv data size error.");
            continue;
        }
        syslog(LOG_INFO, "run id:%d lang:%d tl:%d ml:%d.",
                run.problem_id,
                run.lang,
                run.time_limit,
                run.mem_limit);
        syslog(LOG_DEBUG, "code : %s",run.code);

        judge(&run);
    }
}

void prepare_listen()
{
    int socket_fd;
    int ret;
    struct sockaddr_in sock_addr;
    socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        syslog(LOG_ERR, "socket create failed.");
        exit(EXIT_FAILURE);
    }
    
    sock_addr.sin_family = PF_INET;
    sock_addr.sin_port = htons(LISTEN_PORT);
    sock_addr.sin_addr.s_addr = htonl(inet_addr(LISTEN_ADDR));
    
    ret = bind(socket_fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr));
    if (ret < 0) {
        syslog(LOG_ERR, "socket bind failed. %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    ret = listen(socket_fd, 8);
    if (ret < 0) {
        syslog(LOG_ERR, "socket listen failed.");
        exit(EXIT_FAILURE);
    }
    
    main_loop(socket_fd);
    
}

