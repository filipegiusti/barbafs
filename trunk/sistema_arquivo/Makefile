CC = gcc
CFLAGS = -Wall -g
INCLUDE = -Iinclude/
BASE_FATORIAL = src/fatorial/fatorial
BASE_HFORMAT = src/hformat/hformat
BASE_TESTE = testes/teste
SRC_FATORIAL = $(BASE_FATORIAL).c
OBJ_FATORIAL = $(BASE_FATORIAL).o

SRC_HFORMAT = $(BASE_HFORMAT).c
OBJ_HFORMAT = $(BASE_HFORMAT).o

SRC_MAIN = src/main.c
OBJ_MAIN = main.bin

OBJS = $(OBJ_FATORIAL) 

SRC_TESTE = $(BASE_TESTE)_fatorial.c 
OBJS_TESTE = $(BASE_TESTE).o 

all: $(OBJS) hformat boot hreset 
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(SRC_MAIN) -o bin/$(OBJ_MAIN)


fatorial: src/fatorial/fatorial.o
	make -C src/fatorial

hformat:
	make -C src/hformat

boot:
	make -C src/boot

hreset:
	make -C src/hreset
	
	
teste: $(OBJS) 
	$(CC) $(CFLAGS) -Iinclude/ $(OBJS) $(SRC_TESTE) -lcheck -o teste 
	./teste

clean:
	rm -f *.o
	rm -f bin/*
	rm -f src/fatorial/*.o 
	rm -f src/hreset/*.o 
	rm -f src/boot/*.o 
	rm -f src/hformat/*.o 
	rm -f src/hpsys/*.o 
	rm -f teste
