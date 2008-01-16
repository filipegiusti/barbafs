SOURCE = boot.asm
OBJ = boot.o
BIN = ../../bin/boot.bin

all: $(SOURCE)
	nasm -f elf $(SOURCE)
	ld -s -o $(BIN) $(OBJ)

