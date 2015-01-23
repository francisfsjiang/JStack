#include<stdio.h>
#include<fcntl.h>
int main()
{
	int a,b;
	int fd=open("/dev/null",O_RDWR);
	write(fd,"hehe",sizeof("hehe"));
	while(scanf("%d %d", &a, &b)!=EOF){
		printf("%d\n",a+b);
	}
	return 0;
}
