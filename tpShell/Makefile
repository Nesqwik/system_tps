CC = gcc
CFLAGS =-Wall -Werror 
EXEC = exec
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC)) ligne_commande.o

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean : 
	rm -rf *.o
	rm -rf $(EXEC)

