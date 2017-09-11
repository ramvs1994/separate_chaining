#include"header.h"
#include<stdlib.h>

void delete(void *arg)
{
	struct packet_info *pack=(struct packet_info *)arg ;
	unsigned int key = pack->key;
	unsigned index = key %101 ;
	if(arr[index] == NULL)
	{
		printf("No record with this key\n") ;
		return ;
	}
	if( arr[index]->key == key)
	{
		struct table *copy = arr[index] ;
		arr[index]= arr[index]->next ;
		free(copy) ;
		printf("delete success\n") ;
		return ;
	}
	else
	{
		struct table *temp = arr[index] ;
		while(temp !=NULL)
		{
		
			if(temp->key == key)
			{
			   struct table *copy =temp ;
			   temp=temp->next ;
			   free(copy) ;
			   printf("delete success\n");
			   return ;
			}
		  	temp=temp->next ;
		}
		printf("no packet was stored with this key\n") ;
		
	}
	return ;
}
