#include<stdio.h>	
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<stdlib.h>
#include<time.h>
#include<errno.h>


#define TEXT "SERVER"
#define CLEAR ccc()
#define SIZE 1024
#define PORT 4460
#define TCP 06
#define UDP 17


void main(void)
{
	struct sockaddr_in s,c;
	unsigned short tcp;
	unsigned short udp;
	unsigned short cfd;
	unsigned short client_socket[30] , max_clients = 30 ;
	unsigned short sd, max_sd;
	unsigned short activity, i;
	unsigned char buf[SIZE], *temp=TEXT, *htime;
	unsigned char c_name[INET_ADDRSTRLEN];
	unsigned char s_name[INET_ADDRSTRLEN];
	time_t cldtime;
	fd_set fds;
	socklen_t len= sizeof(c);

	if((tcp=socket(AF_INET,SOCK_STREAM,0))==0)
	{
		printf("Error in create TCP Socket\n\n");
		exit(EXIT_FAILURE);
	}

	if((udp=socket(AF_INET,SOCK_DGRAM,0))==0)
	{
		printf("Error in create UDP Socket\n\n");
		exit(EXIT_FAILURE);
	}	

	s.sin_family=AF_INET;
	s.sin_addr.s_addr=INADDR_ANY;
	s.sin_port=htons(PORT);

	if((bind(tcp,(struct sockaddr *)&s, sizeof(s)))<0)
	{
		printf("Error in TCP Bind\n\n");
		exit(EXIT_FAILURE);
	}

	if((bind(udp,(struct sockaddr *)&s, sizeof(s)))<0)
	{
		printf("Error in UDP Bind\n\n");
		exit(EXIT_FAILURE);
	}

	if((listen(tcp,5))<0)
	{
		printf("\nError in Server Listen\n\n");
		exit(EXIT_FAILURE);
	}

	//printf("\nWaiting for connections..!!\n");		

	while(1)
	{
		printf("___SERVER WAITING___\n") ;
		FD_ZERO(&fds);
		FD_SET(tcp,&fds);
		FD_SET(udp,&fds);		

		//add child sockets to set
       		for ( i = 0 ; i < max_clients ; i++) 
        	{

			sd = client_socket[i];
			if(sd > 0)
			FD_SET( sd , &fds);
			if(sd > max_sd)
			max_sd = sd;
		}

		activity = select( max_sd + 1 , &fds , NULL , NULL , NULL);
		if ((activity < 0) && (errno!=EINTR))  
		{  
			printf("select error");  
		}
		
		if(FD_ISSET(tcp,&fds))
		{
			if((cfd=accept(tcp,(struct sockaddr *)&c, &len))<0)
			{
				printf("ERROR in Accept!!\n\n");
				exit(-1);
			}
			
						

			read(cfd, buf, SIZE);
			inet_ntop(AF_INET,&c.sin_addr.s_addr, c_name,sizeof(c_name));
			printf("client msg %s\n",buf);
			
			time(&cldtime);
			htime=ctime(&cldtime);
			write(cfd,htime,sizeof(htime)) ;

			
			
		}

		else if(FD_ISSET(udp,&fds))
		{
			if((recvfrom(udp, buf, sizeof(buf), 0, (struct sockaddr *)&c, (socklen_t *)&len))<0)
				printf("\n\nError reading data!!");
			printf("client request %s\n",buf) ;

			inet_ntop(AF_INET,&c.sin_addr.s_addr, c_name,sizeof(c_name));

			time(&cldtime);
			htime=ctime(&cldtime);
			sendto(udp, htime, sizeof(htime), 0, (struct sockaddr *)&c, (socklen_t)len);

			
		}

close(cfd);		
	}	
close(tcp);
close(udp);

}	

