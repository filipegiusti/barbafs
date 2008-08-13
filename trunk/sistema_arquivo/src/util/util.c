#include <stdio.h>
#include <stdlib.h>
#include "../../include/util.h"

#ifdef DEBUG
	void debug(char *msg) {
		printf("[+] debug - %s\n", msg);
	}
#else
	void debug(char *msg){}
#endif
	
/*
 * se should_exit == 1 mostra erro e termina programa (erro fatal)
 */
void print_error(char *erro, char *descricao, int should_exit) {
	printf("HFORMAT 0.5-120808 alpha\n");	
	printf("------------------------\n");
	printf("ERRO.....: %s\n", erro);
	printf("DESCRICAO: %s\n\n", descricao);
	(should_exit) ? exit(EXIT_FAILURE) : printf("\t"); 
}
