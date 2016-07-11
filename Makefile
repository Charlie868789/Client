#Client Makefile
#CC=arm-none-linux-gnueabi-gcc 
CC=gcc
LIBS=-lsqlite3
obj=armxx_main.o armxx_config_file.o
ClientV1.0: $(obj)
	@$(CC) $(obj) -o ClientV1.0 $(LIBS)
armxx_main.o: armxx_main.c
	@$(CC) -c armxx_main.c
armxx_config_file.o:armxx_config_file.c
	@$(CC) -c armxx_config_file.c
.PHONY:clean
clean:
	rm -rf armxx_main.o armxx_config_file.o ClientV1.0

