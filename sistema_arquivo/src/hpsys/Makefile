OBJS = $(patsubst %.c,%.o,$(wildcard *.c))

$(SRCS_BIN)hpsys$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
