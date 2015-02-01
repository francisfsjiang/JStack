#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

struct run_param{
	uint id;
	uint lang;
	uint tl;
	uint ml;
	uint cl;
	char * code;
};
char cbuf[1000];
char buffer[1000];

int main(int argc,const char* argv[])
{
	int sock_fd;
	int fd;
	struct sockaddr_in sock_addr;
	int ret;
	int lang_id=atoi(argv[1]);
	struct run_param p;
	sock_fd = socket(PF_INET, SOCK_STREAM,0);

	sock_addr.sin_family = PF_INET;
	sock_addr.sin_port = htons(23333);
	sock_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	printf("start\n");
	ret = connect(sock_fd, (struct sockaddr *) &sock_addr, sizeof(sock_addr));
	if (ret < 0){
		printf("con failed.%s\n",strerror(errno));
		exit(1);
	}
	
	p.id = lang_id;
	p.lang = 0;
	p.tl = 1000;
	p.ml = 1001;
	const char* filename;
	switch(lang_id){
		case 0:
			filename="test_code/c/main.c";
			break;
		case 1:
			filename="test_code/cxx/main.cpp";
			break;
		default:
			return -1;
			break;
	}
	fd = open(filename,O_RDONLY);
	printf("open fd %d.\n",fd);
	ret = read(fd, cbuf, sizeof(cbuf));
	p.cl=ret;
	printf("read %d.\n", ret);
	close(fd);
	memcpy(buffer, &p, 20);
	memcpy(buffer+20, &cbuf, strlen(cbuf));
	printf("%s\n", buffer);
	ret = send(sock_fd, buffer, 20+strlen(cbuf), 0);
	if (ret < 0){
		printf("send failed.\n");
	}
	printf("%d sended.\n",ret);

	return 0;
}
