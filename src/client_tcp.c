#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>


#define TEXT_SIZE 1024

#define PORT 4460
#define IP "127.0.01"
 


void main()
{
	short fd;
	struct sockaddr_in c;
	char buf[100];
	memset(buf,0,100) ;

	if((fd=socket(AF_INET,SOCK_STREAM,0)) == 0)
	{
		printf("Error in Socket!! \n\n");
		exit(-1);
	}

	c.sin_family=AF_INET;
	c.sin_addr.s_addr = inet_addr(IP);
	c.sin_port = htons(PORT);

	if((connect(fd,(struct sockaddr *)&c, sizeof(c)))<0)
	{
		printf("Error in Connect!! \n\n");
		exit(-1);
	}
	
	printf("Enter text :\n");
	scanf("%[^\n]s",buf);

	if ((write(fd, buf,sizeof(buf) ))>0)
	   printf("Data Written Successfully \n");
	mem
	read(fd,buf,100);
	printf("msg from server %s\n",buf);	
	close(fd);
}
