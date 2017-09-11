#ifndef __HEADER1_H
#define __HEADER1_H

#include<stdint.h>
#include<string.h>
#include<stdlib.h>
#include <arpa/inet.h>
#include<netinet/in.h>
#include<stdio.h>

#define TCP 6
#define UDP 17

struct packet_info {
	uint32_t key;
	uint32_t source_ip;
	uint32_t dest_ip;
	uint16_t source_port ;
	uint16_t dest_port;
	uint8_t protocol;
	char time[50];
	
};

struct table {
	struct table *next;
	struct packet_info *details;	
	//struct packet_info details;	
	char time[50];	
	unsigned key;
};

struct table *arr[100];



extern unsigned hash_func(struct packet_info *x);
extern void insert_packet(void *y) ;
extern void lookup_packet(void *z) ;
extern void delete(void *a) ;

#endif
