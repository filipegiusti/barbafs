OBJS = $(patsubst %.c,%.o,$(wildcard *.c))

$(SRCS_BIN)hreset$(BIN): $(OBJS)
	$(CC) $(C_FLAGS) $^ -o $@
