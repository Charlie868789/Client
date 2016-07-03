#Client Makefile
#CC=arm-none-linux-gnueabi-gcc 
CC=gcc
obj=armxx_main.o 
ClientV1.0: $(obj)
	@$(CC) $(obj) -o ClientV1.0
armxx_main.o: armxx_main.c
	@$(CC) -c armxx_main.c
.PHONY:clean
clean:
	rm -rf armxx_main.o ClientV1.0

