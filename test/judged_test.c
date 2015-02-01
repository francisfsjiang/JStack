#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <unistd.h>

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
	
	p.id = 0;
	p.lang = lang_id;
	p.tl = 1000;
	p.ml = 1001;
	const char* filename;
	switch(lang_id){
		case 0:
			filename="test_code/c/main.c";
			break;
		case 1:
			filename="test_code/cpp/main.cpp";
			break;
		case 2:
			filename="test_code/pascal/main.pp";
			break;
		case 3:
			filename="test_code/java/Main.java";
			break;
		case 4:
			filename="test_code/csharp/main.cs";
			break;
		case 6:
			filename="test_code/python2/main.py";
			break;
		case 7:
			filename="test_code/python3/main.py";
			break;
		case 8:
			filename="test_code/ruby/main.rb";
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
