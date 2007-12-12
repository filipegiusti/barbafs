exec: fatorial.o main.o
	gcc -Wall fatorial.o main.o -o fatorial

fatorial.o: 

main.o:

teste_fatorial.o: fatorial.o
	gcc -Wall testes/teste_fatorial.c -c -o teste_fatorial.o

teste: teste_fatorial.o
	gcc -Wall teste_fatorial.o -o testes/teste
	./testes/teste

clean: 
	rm fatorial.o fatorial
