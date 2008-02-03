BOOT = boot

$(SRCS_BIN)$(BOOT)$(BIN): $(BOOT).o
	ld -s -o $@ $^

$(BOOT).o: $(BOOT).asm
	nasm -f elf $^ -l $*.lst

