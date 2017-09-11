#include"header.h"


void lookup_packet(void *ptr)
{
	struct packet_info *packet = (struct packet_info *)ptr;
	unsigned key= packet->key;
	unsigned index = key %101 ;
	if(arr[index] == NULL)
	{
		printf("No record stored with this key\n") ;
		return ;
	}
	
	//struct sockaddr_in sa;
	char str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, (struct in_addr *)&(arr[index]->details->source_ip), str, INET_ADDRSTRLEN);

	struct table *temp = arr[index] ;
	while(temp !=NULL)
	{
		
		if(temp->key == key)
		{
			unsigned short prtcl ;
			printf("___PACKET DETAILS___\n") ;
			inet_ntop(AF_INET, (struct in_addr *)&(temp->details->source_ip), str, INET_ADDRSTRLEN);
			printf("1.source IP is %s\n",str);
			inet_ntop(AF_INET, (struct in_addr *)&(temp->details->dest_ip), str, INET_ADDRSTRLEN);
			printf("2.destination IP is %s\n",str);
			printf("3.time stamp is %s\n",temp->time);
			prtcl = temp->details->protocol ; 
			
		        switch (prtcl) 					//Checking for the Protocol 
   	 		{
        			case 1:  
           	 			printf("4.ICMP Protocol\n");
            				break ;
         
        			case 2:  
            				printf("4.IGMP Protocol\n");
            				break ;
         
        			case 6: 
					printf("4.source port %hu\n",temp->details->source_port) ;
					printf("5.destination port %hu\n",temp->details->dest_port) ;
               				printf("6.TCP protocol\n");
            				break ;
         
        			case 17: 
					printf("4.source port %hu\n",temp->details->source_port) ;
					printf("5.destination port %hu\n",temp->details->dest_port) ;
               				printf("6.UDP protocol\n");
             	        		break ;
         
       				default: 
					printf("4.protocol number %hu\n",prtcl);    //Some Other Protocol like ARP , RARP etc.
            				break ;
    			}
		
			return ;
		}
		
		temp=temp->next ;
	}
	printf("sorry No record stored with this key\n") ;

		
	return ;
}
