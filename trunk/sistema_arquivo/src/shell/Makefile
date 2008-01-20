CC = gcc
C_FLAGS = -Wall -lutil  -g
INCLUDE = -I../../include/
OBJ = ../util/util.o
SOURCE = shell.c shell_cmd.c 
BIN = ../../bin/shell.bin

all: $(OBJ)
	$(CC) $(C_FLAGS) $(INCLUDE) $(LIB) $(SOURCE) $(OBJ) -o $(BIN)

run:
	./../../bin/shell.bin

