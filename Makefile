#Client Makefile
CC=arm-none-linux-gnueabi-gcc 
#CC=gcc
LIBS=-lsqlite3 -levent
CFLAGS= -Wall -I/home/charlie/C_coding/Client/ARM_Client/third-part/include
LDFLAGS=-L/home/charlie/C_coding/Client/ARM_Client/third-part/lib
obj=armxx_main.o armxx_config_file.o armxx_gps.o
Client: $(obj)
	@$(CC) $(obj) -o Client $(LDFLAGS) $(LIBS)
armxx_main.o: armxx_main.c
	@$(CC) $(CFLAGS) -c armxx_main.c
armxx_config_file.o:armxx_config_file.c
	@$(CC) -c armxx_config_file.c
armxx_gps.o:armxx_gps.c
	@$(CC) -c armxx_gps.c
.PHONY:clean
clean:
	rm -rf armxx_main.o armxx_config_file.o armxx_gps.o Client 

