#Client Makefile
#CC=arm-none-linux-gnueabi-gcc 
CC=gcc
obj=armxx_main.o armxx_config_file.o
ClientV1.0: $(obj)
	@$(CC) $(obj) -o ClientV1.0
armxx_main.o: armxx_main.c
	@$(CC) -c armxx_main.c
armxx_config_file.o:armxx_config_file.c
	@$(CC) -c armxx_config_file.c
.PHONY:clean
clean:
	rm -rf armxx_main.o armxx_config_file.o ClientV1.0

