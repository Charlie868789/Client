#Client Makefile
#CC=arm-none-linux-gnueabi-gcc 
CC=gcc
LIBS=-lsqlite3
obj=armxx_main.o armxx_config_file.o armxx_gps.o
ClientV1.0: $(obj)
	@$(CC) $(obj) -o ClientV1.0 $(LIBS)
armxx_main.o: armxx_main.c
	@$(CC) -c armxx_main.c
armxx_config_file.o:armxx_config_file.c
	@$(CC) -c armxx_config_file.c
armxx_gps.o:armxx_gps.c
	@$(CC) -c armxx_gps.c
.PHONY:clean
clean:
	rm -rf armxx_main.o armxx_config_file.o armxx_gps.o ClientV1.0 

