#include<stdio.h>
#include<netinet/in.h>		// contains sturcuture sockaddr_in
#include<sys/socket.h>		// contains socket()
#include<stdlib.h>    //malloc
#include<string.h>    //memset
#include<netinet/ip_icmp.h>   //Provides declarations for icmp header
#include<netinet/udp.h>   //Provides declarations for udp header
#include<netinet/tcp.h>   //Provides declarations for tcp header
#include<netinet/ip.h>    //Provides declarations for ip header
#include<arpa/inet.h>
//#include<ip.h>		// contain structure struct iphdr
#include<stdint.h>
#include<errno.h>
#include<time.h>
#include<string.h>
#include<netinet/if_ether.h>  
#include<netinet/ip.h>
#include<net/ethernet.h>
#include<signal.h>
#include<unistd.h>

#include"header.h"

#define packet_size 65536
#define TCP 6
#define UDP 17

int rawsock_fd ;

void get_tuple_para(unsigned char *, int, char *) ;


struct packet_info *tuple_para ;

int loop=1 ;
unsigned _key;


struct packet_info *store;

void func(int sig)
{
		
			
		int choice ; 
		char src_ip[20],des_ip[20];
		unsigned short src_port, dst_port, procl;
		struct sockaddr_in addr;

		printf("___MENU___\n");
		printf("1.lookup\n");
		printf("2.delete\n");
		printf("3.insert\n");
		printf("4.exit\n");
		printf("enter ur choice\n");
		scanf("%d",&choice) ;
		if(choice == 4 )
			exit(0) ;
		printf("enter source ip \n");
		scanf(" %[^\n]",src_ip) ;
		printf("destination ip\n");
		scanf(" %[^\n]",des_ip);
		printf("enter source port\n");
		scanf("%hu",&src_port) ;
		printf("enter destination port\n") ;
		scanf("%hu",&dst_port);
 		printf("enter 6 for TCP packet, 17 for UDP packet\n") ;
		scanf("%hu",&procl);
		store =(struct packet_info *)malloc(sizeof(struct packet_info)) ;

		if(store == NULL) {
			printf("mallco returned NULL\n");
			exit(1);
		}
		inet_pton(AF_INET, src_ip, &(addr.sin_addr));
		store->source_ip= addr.sin_addr.s_addr ;  
		inet_pton(AF_INET, des_ip, &(addr.sin_addr));
		store->dest_ip= addr.sin_addr.s_addr ;   
		store->source_port= src_port ;
		store->dest_port= dst_port ;
		store->protocol= procl ;
		_key=hash_func(store) ;
		store->key = _key ;
				
				switch(choice) {

				case 1: 
					printf("choosen lookup packet\n") ;
					lookup_packet((void *)store) ;
					sleep(3);
					break ;
				case 2:
					printf("choosen delete packet\n") ;
					delete((void *)store) ;
					sleep(3);
					break ;
				case 3:
					insert_packet((void *)store) ;
					break ;
				case 4: 
					exit(0);
		
				default: 
					printf(" Wrong choice !\n");	
					break ;

	
				}
		
		return ;
}


int main()
{
		struct sockaddr saddr ;	
		time_t cldtime ;
		char *t;
	
		unsigned int data_size , saddr_size;
		unsigned char buf[packet_size];
	
		if((rawsock_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) <0 ) {
	
			fprintf(stderr, "socket() failed: %s\n", strerror(errno));
        		exit(1);
		}	
		
		while(loop) {
			signal(SIGINT,func) ;
		 	saddr_size = sizeof(saddr) ;		
			data_size = recvfrom(rawsock_fd,buf,packet_size,0,&saddr,&saddr_size) ;

			if(data_size < 0)	{
				printf("error in receiving packets\n") ;
				exit(1) ;
			}

			time(&cldtime);
			t= ctime(&cldtime) ;
			
			get_tuple_para(buf,data_size,t);
			_key = hash_func((struct packet_info *)tuple_para );
			tuple_para->key = _key ;
			printf("generated key is %u\n",_key) ;
			insert_packet((void*)tuple_para) ;

			lookup_packet((void *)tuple_para);
						
			free(tuple_para);

		
		}// close of while
	
		return 0;
	
} // close of main

void get_tuple_para(unsigned char *buffer ,int datasize,char *tm)
{
		unsigned short iphdrlen;
		struct ethhdr *eth = (struct ethhdr *)buffer;
		struct iphdr *iph = (struct iphdr *)(buffer+sizeof(struct ethhdr));
		iphdrlen = iph->ihl*4;
	
		tuple_para = (struct packet_info *)malloc(sizeof(struct packet_info)) ;

		strcpy(tuple_para->time,tm);

		if(iph->protocol == TCP) {

			struct tcphdr *tcph=(struct tcphdr*)(buffer + iphdrlen + sizeof(struct ethhdr));
			tuple_para->source_port = ntohs(tcph->source) ;
			tuple_para->dest_port = ntohs(tcph->dest) ;	

		} else if(iph->protocol == UDP) {

			struct udphdr *udph = (struct udphdr*)(buffer + iphdrlen  + sizeof(struct ethhdr));
			tuple_para->source_port = ntohs(udph->source) ;
			tuple_para->dest_port = ntohs(udph->dest) ;	

		} else  { 		/* other protocols like ADR , ICMP IGMP which are not used for actual data transfer */
		
		tuple_para->source_port = -1;		
		tuple_para->dest_port = -1 ;	
		}
	
	
		tuple_para->source_ip = iph->saddr ;
		tuple_para->dest_ip = iph->daddr ;
		tuple_para->protocol = iph->protocol ;

		return ;
}








































