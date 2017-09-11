#ifndef __HEADER1_H
#include"header.h"
#endif


unsigned hash_func(struct packet_info *p)
{
	uint32_t s_ip = p->source_ip ;
	uint32_t d_ip = p->dest_ip ;
	uint16_t s_port = p->source_port ;
	uint16_t d_port = p->dest_port ;
	uint8_t protocol = p->protocol ;
	uint32_t val;
	val=s_ip^d_ip^( (s_port & 0xffff) | ((d_port & 0xffff) << 16) ) ;
	if(protocol == TCP) 
	return val ;
	else if(protocol == UDP)
	return (~val) ;
}
