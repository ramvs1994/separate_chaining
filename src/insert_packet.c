
#include"header.h"
#include<string.h>

void insert_packet(void *p) 
{
	struct packet_info *r = (struct packet_info *)p ;
	unsigned index= (r->key)%101 ;
	printf("index = %hu\n", index) ;
	if(arr[index] == NULL)
	{	
				
		arr[index] = (struct table *)malloc(sizeof(struct table));
		if(arr[index] == NULL)
		{
			printf("malloc returned NULL\n");
			exit(0);
		}
		memset(arr[index],0,sizeof(struct table)) ;
		arr[index]->key = r->key ;
		strcpy(arr[index]->time, r->time ) ;
		
		arr[index]->details=(struct packet_info *)malloc(sizeof(struct packet_info)) ;
		arr[index]->details->source_ip=r->source_ip ;	
		arr[index]->details->dest_ip = r->dest_ip ;
		arr[index]->details->source_port=r->source_port ;
		arr[index]->details->dest_port = r->dest_port;
		arr[index]->details->protocol = r->protocol;
		arr[index]->next =NULL ;
		printf("insert success\n");
		return ;
	}
	
	else
	{
		struct table *tp = arr[index] ;
		while(tp != NULL)
		{
			if(tp->key == r->key)
			{
				strcpy(tp->time , r->time) ;
				printf("insert success\n");
				return ;
			}
			tp = tp->next ;

		}
		//tp=tp->next ;
		tp=(struct table *)malloc(sizeof(struct table)) ;
		memset(tp,0,sizeof(struct table)) ;
 		tp->key = r->key;
		strcpy(tp->time,r->time);
	

		tp->details =(struct packet_info *)malloc(sizeof(struct packet_info)) ;

		tp->details->source_ip = r->source_ip ;
		tp->details->dest_ip = r->dest_ip ;
		tp->details->source_port=r->source_port ;
		tp->details->dest_port = r->dest_port;
		tp->details->protocol = r->protocol;
		tp->next = NULL ;
		printf("insert success\n");


		return ;
	}
	
}
