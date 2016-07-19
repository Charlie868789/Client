#ifndef COMMOND_H_
#define COMMOND_H_
typedef struct
{       
        unsigned char Sync;
        unsigned char SrcAddr;
        unsigned char DesAddr;
        unsigned char Command;
        unsigned char Data[10];
        unsigned char CrcByte1;
        unsigned char CrcByte2;
}Packet;

Packet  WRPack;
Packet  RDPack;

#endif
