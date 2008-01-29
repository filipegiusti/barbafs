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

OBJS = $(OBJ_FATORIAL) 

SRC_TESTE = $(BASE_TESTE)_fatorial.c 
OBJS_TESTE = $(BASE_TESTE).o 

all: $(OBJS) hformat shell boot hreset hpsys

fatorial: src/fatorial/fatorial.o
	make -C src/fatorial

hformat:
	make -C src/hformat

shell:
	make -C src/shell

boot:
	make -C src/boot

hreset:
	make -C src/hreset

hpsys:
	make -C src/hpsys

	
	
teste: $(OBJS) 
	$(CC) $(CFLAGS) -Iinclude/ $(OBJS) $(SRC_TESTE) -lcheck -o teste 
	./teste

clean:
	rm -f *.o
	rm -f bin/*
	rm -f src/fatorial/*.o 
	rm -f src/hreset/*.o 
	rm -f src/boot/*.o
	rm -f src/boot/*.lst 
	rm -f src/hformat/*.o 
	rm -f src/hpsys/*.o 
	rm -f teste
