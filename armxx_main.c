/*
* Function: This is a main function,which is used to call other function to commnunicate with
*           sensor node and Server.
* Author  : Charlie Chen
* Time    : 2016/June/9
* Version : v1.0
*/
#include<stdio.h>
#include<stdlib.h>
#include"libevent/include/event.h"
#include"config.h"
#define DEBUG_CLIENT  1
#define DEBUG_MAKEFILE 1

extern struct ModuleInfo ModInfo;

int 
main(int argc, int *argv[])
{
	int sockfd=0;
	int flag=0;
	//authority right
#if DEBUG_MAKEFILE 
	printf("To text the Makefile is correct\n");
#endif
	ModInfo.ModServerIp =( char *)malloc(20);
	flag = ReadModinfo(ModInfo);
	if(flag < 0){
		printf("/etc/Module.ini cannot find or other\n");
	}
#if DEBUG_CLIENT
	printf("The Server Ip address is : %s\n",ModInfo.ModServerIp);
#endif
	//checking the network status

        //communicate with Server

        //offline
}
