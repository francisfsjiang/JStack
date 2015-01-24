#ifndef __judged__listener__
#define __judged__listener__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <syslog.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "judger.hpp"

#define LISTEN_PORT 23333
#define LISTEN_ADDR "0.0.0.0" 

#define MAX_BUFFER_SIZE 0x10000C //1MB + 12B


void prepare_listen();

#endif /* defined(__judged__listener__) */
