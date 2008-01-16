CC = gcc
CFLAGS = -Wall -g -c
OBJS = util.o 
SRCS = util.c 
INCLUDE = -I../../include/

all: 
	$(CC) $(CFLAGS) $(INCLUDE) $(SRCS) -o $(OBJS)

debug:
	$(CC) $(CFLAGS) -DDEBUG $(INCLUDE) $(SRCS) -o $(OBJS)

