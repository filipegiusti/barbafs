OBJS = $(patsubst %.c,%.o,$(wildcard *.c)) $(UTIL)

$(SRCS_BIN)hformat$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(UTIL): %.o : ../../include/util.h
