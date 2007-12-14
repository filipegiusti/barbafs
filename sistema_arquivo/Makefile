CC = gcc
CFLAGS = -Wall
OBJS = src/fatorial.o src/hformat.o
SRCS = src/fatorial.c src/hformat.c
OBJS_TESTE = testes/teste_hformat.o
SRCS_TESTE = testes/teste_hformat.c

fatorial: $(OBJS) src/main.o
	$(CC) $(CFLAGS) src/main.o $(OBJS) -o $@

hformat: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

src/main.o:

$(OBJS):

$(OBJS_TESTE):

teste: $(OBJS_TESTE) $(OBJS)
	$(CC) $(OBJS_TESTE) $(OBJS) -lcheck -o $@
	echo ============================================================
	./teste

clean: 
	rm -f $(OBJS) $(OBJS_TESTE) teste fatorial hformat src/main.o
