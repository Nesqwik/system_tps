CC = gcc
CFLAGS =-Wall -Werror
EXEC = hello
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean : 
	rm -rf *.o
	rm -rf $(EXEC)

	
