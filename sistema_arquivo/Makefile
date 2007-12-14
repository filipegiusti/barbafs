CC = gcc
CFLAGS = -Wall
OBJS = src/fatorial.o
SRCS = src/fatorial.c
OBJS_TESTE = testes/teste_fatorial.o
SRCS_TESTE = testes/teste_fatorial.c

fatorial: $(OBJS) src/main.o
	$(CC) $(CFLAGS) src/main.o $(OBJS) -o $@

src/main.o:

$(OBJS):

$(OBJS_TESTE):

teste: $(OBJS_TESTE) $(OBJS)
	$(CC) $(OBJS_TESTE) $(OBJS) -lcheck -o $@
	echo ============================================================\n
	./teste

clean: 
	rm -f $(OBJS) $(OBJS_TESTE) teste fatorial
