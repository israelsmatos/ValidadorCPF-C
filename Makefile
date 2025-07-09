CC=$(shell which gcc)
TARGET=cpf
FLAGS=-o

all:
	$(CC) $(FLAGS) $(TARGET) cpf.c lib.c

clean:
	rm -rf $(TARGET) *.o
