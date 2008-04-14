CC = gcc
CFLAGS = -Wall -g -Iinclude
SRC_DIR = src/
TESTES_DIR = testes/
BIN_DIR = bin/
TESTE_OBJS = $(patsubst %.c,%.o,$(wildcard $(TESTES_DIR)*.c)) fatorial.o filesystem.o util.o
MAKE_SUBDIRS = $(SRC_DIR)boot $(SRC_DIR)hformat $(SRC_DIR)hpsys $(SRC_DIR)hreset $(SRC_DIR)shell
SRC_SUBDIRS = $(wildcard $(SRC_DIR)*)
BIN = .bin
# Variaveis para serem usados pelas Makefiles dos srcs
SRCS_BIN = ../../bin/
UTIL = ../util/util.o
FILESYSTEM = ../filesystem/filesystem.o

export
.PHONY: $(SRC_SUBDIRS) clean teste all debug normal
vpath %.o $(SRC_SUBDIRS)
vpath %.c $(SRC_SUBDIRS)

all: $(MAKE_SUBDIRS)

$(MAKE_SUBDIRS):
	@$(MAKE) -s -C $@ CFLAGS='-Wall -g -I../../include' 

teste: $(BIN_DIR)teste$(BIN)
	

$(BIN_DIR)teste$(BIN): $(TESTE_OBJS)
	make
	$(CC) $(CFLAGS) $^ -lcheck -o $@

debug:
	$(CC) $(CFLAGS) -DDEBUG -c $(SRC_DIR)util/util.c -o $(SRC_DIR)util/util.o
	make

normal:
	$(CC) $(CFLAGS) -c $(SRC_DIR)util/util.c -o $(SRC_DIR)util/util.o
	make

clean:
	rm -f bin/*.bin
	rm -f src/*/*.o
	rm -f src/*/*.lst
	rm -f testes/*.o
