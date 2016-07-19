/*
* Function: This is a main function,which is used to call other function to commnunicate with
*           sensor node and Server.
* Author  : Charlie Chen
* Time    : 2016/June/9
* Version : v1.0
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<errno.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include"sqlite3.h"
#include"mysqlite.h"
#include"event.h"
#include"config.h"
#include"debug.h"

#define PORT_NUMBER 8080
extern struct ModuleInfo ModInfo;
extern void print_gps_info(struct GPS_Data);
// location
struct GPS_Data GpsData;
// other information
struct Sensor_Data SensorData; 
int 
main(int argc, char *argv[])
{
	int sockfd=0;
	int flag=0;
	int portnumber=0;
	struct hostent *host;
	struct sockaddr_in serveraddr;
	sqlite3 *db;
	//FILE *fd;
	char sql[128]={0};
	//authority right
	GpsData.Gps_time = (char *)malloc(20);
	GpsData.Gps_sv = (char *)malloc(2);
	GpsData.Gps_latitude = (char *)malloc(12);
	GpsData.Gps_longitude = (char *)malloc(12);
	GpsData.Gps_speed = (char *)malloc(5);
	GpsData.Gps_date = (char *)malloc(8);
#if 0
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
	host = gethostbyname(ModInfo.ModServerIp);
	if(host  == NULL){
		fprintf(stderr,"gethostname error\n");
		exit(0);
	}
	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1){
		fprintf(stderr,"Socket error: %s\n",strerror(errno));
	}
	//memset((char *)&server_add, 0,sizeof(server_addr));
	portnumber = PORT_NUMBER;
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(portnumber);
	inet_aton(ModInfo.ModServerIp, &serveraddr.sin_addr);
	if(connect(sockfd,(struct sockaddr *)(&serveraddr),sizeof(struct sockaddr))==-1){
                fprintf(stderr,"Connect Error:%s\a\n",strerror(errno));  
                exit(1);
        }
#endif
	//To connect database ,sqlite
	memset(sql,'\0',128);
	// the first argv can be from user input
	CALL_SQLITE(open("./data/database.db",&db));
	//SQL LANGUAGE
	strcpy(sql,"create table id(id INTEGER PRIMARY KEY, data TEXT)");
	CALL_SQLITE(exec)
	sqlite3_exec(db,sql,NULL,NULL,NULL);
	//checking the network status
	//endless loop
	while(1){
		//check the location, then save to data base.
		//flag = GetGpsData(GpsData);
#ifdef DEBUG_CLIENT
		//print_gps_info(GpsData);
#endif

		//Modbus protcol, capture data from sensor node. Modbus Protocl
		flag = GetSensorData(SensorData);

		// capture the GPS data from UART and other sensor data save to database.
		/*
		* store the data to database, including location, temperture etc. 
		*/
	}
        //communicate with Server

        //offline
}
