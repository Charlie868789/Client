/*
* Function: This function is used to capture GPS data and analysis it
* Author  : Charlie Chen
* Time    : 2016/July/11
*/
#include"config.h"
#include<stdio.h>
#include<stdlib.h>
#include"debug.h"
#include<string.h>
#include<termios.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

#define UART_PORT_NO 4
const int BUFF_SIZE = 512;
int SectionID=0, i = 0;
int open_port(int num);
int set_com_config(int fd, int baud_rate,int data_bits,char parity,int stop_bits);
int read_gps_data(int fd,struct GPS_Data);
void print_info(struct GPS_Data);
void GPS_resolve_GPRMC(char data,struct GPS_Data);
const char * dev[]={"/dev/ttySAC0","/dev/ttySAC1","/dev/ttySAC2","/dev/ttySAC3","/dev/ttySAC4"};


void print_info(struct GPS_Data Gps_Data)
{
    printf("Now the receive time is %s\n",Gps_Data.Gps_time);
    printf("The star is %c 3\n",Gps_Data.Gps_sv);
    printf("The earth latitude is :%s\n",Gps_Data.Gps_latitude);
    printf("The earth longitude is :%s\n",Gps_Data.Gps_longitude);
    printf("The train speed is:%s km/h\n",Gps_Data.Gps_speed);
    printf("The date is:%s\n",Gps_Data.Gps_date);
}
void GPS_resolve_GPRMC(char data, struct GPS_Data GPS_Data)
{
	//$GPRMC,092427.604,V,4002.1531,N,11618.3097,E,0.000,0.00,280812,,E,N*08
	if(data==',')
	{
		++SectionID;
		i=0;
	}
    	else
    	{
        	switch(SectionID)
			{
			    case 1://02:48:13
				    GPS_Data.Gps_time[i++]=data;
				    if(i==2 || i==5)
				    {
				        GPS_Data.Gps_time[i++]=':';
				    }
				    GPS_Data.Gps_time[8]='\0';
				    break;
			    case 2:
				    if(data=='A')
					GPS_Data.Gps_sv='>';
				    else
					GPS_Data.Gps_sv='<';
				    break;
			    case 3://3158.4608
				    GPS_Data.Gps_latitude[++i]=data;
				    GPS_Data.Gps_latitude[12]='\0';
				    break;
			    case 4:
				    if(data=='N')
				    	GPS_Data.Gps_latitude[0]='N';
				    else if(data=='S')
				    	GPS_Data.Gps_latitude[0]='S';
				    break;
			    case 5://11848.3737,E
				    GPS_Data.Gps_longitude[++i]=data;
				    GPS_Data.Gps_longitude[12]='\0';
				    break;
			    case 6:
				    if(data=='E')
				    	GPS_Data.Gps_longitude[0]='E';
				    else if(data=='W')
				    	GPS_Data.Gps_longitude[0]='W';
				    break;
			    case 7://10.05
				    GPS_Data.Gps_speed[i++]=data;
				    GPS_Data.Gps_speed[4]='\0';
				    break;
			    case 9://15-07-06 -> 06-07-15
				    GPS_Data.Gps_date[i++]=data;
				    if(i==2 || i==5)
				    {
				        GPS_Data.Gps_date[i++]='-';
				    }
				    GPS_Data.Gps_date[8]='\0';
				    break;
        	}
    	}

}

int read_gps_data(int fd, struct GPS_Data GpsData)
{
	char buffer[BUFF_SIZE],dest[1024];
	char array[10]="$GPRMC";
	int res,i=0,j=0,k=0;
	int data=1,len=0;
	memset(dest,0,sizeof(dest));
	do{
		memset(buffer,0 ,sizeof(buffer));
		if(res = read(fd,buffer,1) > 0)
		{

			strcat(dest,buffer);
		    	if(buffer[0]=='\n')
		    	{
		        	i=0;
				if(strncmp(dest,array,6)==0)
				{
				       printf("%s",dest);
				       len=strlen(dest);
				       for(k=0;k<len;k++)
				       {
				            GPS_resolve_GPRMC(dest[k],GpsData);
				       }
				       SectionID=0;
				       print_info(GpsData);
		        	}
		        	bzero(dest,sizeof(dest));
		    	}

		}
	}while(1);
	close(fd);
}

int set_com_config(int fd, int baud_rate,int data_bits,char parity,int stop_bits)
{
	struct termios new_cfg,old_cfg;
	int speed;
	if(tcgetattr(fd,&old_cfg)!=0)
	{
		fprintf(stderr,"tcgetattr\n");
		return -1;
	}
	tcflush(fd,TCIOFLUSH);
	new_cfg = old_cfg;
	cfmakeraw(&new_cfg);
	new_cfg.c_cflag &=~CSIZE;

	switch(baud_rate)
    	{
        	case 2400:
            		speed = B2400;
            		break;
        	case 4800:
            		speed = B4800;
            		break;
        	case 9600:
            		speed = B9600;
            		break;
        	case 19200:
            		speed = B19200;
            		break;
        	case 38400:
            		speed = B38400;
            		break;
        	case 115200:
            		speed = B115200;
            		break;
		default:
			speed = B9600;
			break;
	}
	cfsetispeed(&new_cfg,speed);
	cfsetospeed(&new_cfg,speed);
	switch(data_bits)
	{
		case 7:
		    new_cfg.c_cflag|=CS7;
		    break;

		case 8:
		    new_cfg.c_cflag|=CS8;
		    break;
	}

	switch(stop_bits)
	{
		case 1:
		    new_cfg.c_cflag &=~CSTOPB;
		    break;
		case 2:
		    new_cfg.c_cflag |=CSTOPB;
		    break;
	}

	switch(parity)
	{
		case 'o':
		case 'O':
		    new_cfg.c_cflag|=(PARODD|PARENB);
		    new_cfg.c_iflag|=(INPCK |ISTRIP);
		    break;
		case 'e':
		case 'E':
		    new_cfg.c_cflag |=PARENB;
		    new_cfg.c_cflag &=~PARODD;
		    new_cfg.c_iflag |=(INPCK | ISTRIP);
		    break;
		case 's':
		case 'S':
		    new_cfg.c_cflag &=~PARENB;
		    new_cfg.c_cflag &=~CSTOPB;
		    break;
		case 'n':
		case 'N':
		    new_cfg.c_cflag &=~PARENB;
		    new_cfg.c_iflag &=~INPCK;
		    break;
	}

        new_cfg.c_cc[VTIME] =10;
    	new_cfg.c_cc[VMIN] =5;
     	tcflush(fd,TCIFLUSH);

	if((tcsetattr(fd,TCSANOW,&new_cfg))!=0)
	{
        	fprintf(stderr,"tcsetattr error\n");
        	return -1;
	}
}
int open_port(int com_port)
{
	int uart_fd = 0;
	if(com_port<0){
		printf("serial port number is error\n");
		return -1;
	}
	if((uart_fd = open(dev[com_port-1],O_RDWR|O_NOCTTY|O_NDELAY))<0)
	{
		fprintf(stderr,"cannot open the serial port\n");
		return -1;
	}
	if(fcntl(uart_fd,F_SETFL,0) < 0)
	{
		fprintf(stderr,"fcntl F_SETFL error\n");
		return -1;
	}
	return uart_fd;
}
int GetGpsData(struct GPS_Data gpsdata)
{
	int fd=0;
	struct GPS_Data GpsData = gpsdata;
	//open serial port device
	fd = open_port(UART_PORT_NO);
	if(fd < 0){
		printf("cann't open the serail number, please check it\n");
	}
#ifdef DEBUG_CLIENT
	printf("open serial port successfully\n");
#endif
	//set serail port
	if((set_com_config(fd,9600,8,'N',1)) < 0)
	{
		fprintf(stderr,"configure the serial port error\n");
		return -1;
	}
#ifdef DEBUG_CLIENT
	printf("set serial port successful\n");
#endif
	//read gps data
	read_gps_data(fd,GpsData);
	return 1;
}


