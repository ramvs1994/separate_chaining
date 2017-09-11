#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>


#define TEXT_SIZE 1024
#define IP "127.0.0.1"
#define PORT 4460

void main()
{
	int fd;
	struct sockaddr_in c;
	char buf[100];
	memset(buf,0,100) ;

	if((fd=socket(AF_INET,SOCK_DGRAM,0)) == 0)
	{
		printf("Error in Socket!! \n\n");
		exit(-1);
	}

	c.sin_family=AF_INET;
	c.sin_addr.s_addr = inet_addr(IP);
	c.sin_port = htons(PORT);

	printf("\nEnter text:\n");
	scanf("%[^\n]s",buf);

	if ((sendto(fd, buf, sizeof(buf), 0, (struct sockaddr *)&c, sizeof(c) ))>0)
	   printf("Data Written Successfully \n");
	recvfrom(fd, buf, sizeof(buf), 0, NULL, 0) ;
	printf("server msg is %s\n",buf) ;
	close(fd);
}
