OBJS = $(patsubst %.c,%.o,$(wildcard *.c)) $(FILESYSTEM)

$(SRCS_BIN)shell$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

shell_cmd.o shell_func.o: %.o : %.h

$(FILESYSTEM): %.o : %_internal.h
