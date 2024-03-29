/**
 * @file hreset.c
 * @brief Executável responsável pela indicação do disco virtual e identificação do disco a ser utilizado.
 * @author Filipe Giusti, Mauro Kade
 *  @version 1.1
 *  @date    17/01/2007
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Imprime o texto de help e aborta a execução.
 * 
 * Imprime o seguinte texto:
 * Uso: hreset DISCO\n
 * Inicializa um disco anteriormente formatado, se o disco não existir é informado a não existência do mesmo.
 * 
 */
void hreset_help() {
	printf("Uso: hreset DISCO\n");
	printf("Inicializa um disco anteriormente formatado, se o disco não existir é informado a não existência do mesmo.\n\n");
	exit(EXIT_FAILURE);
}


int main(int argc, char *argv[]) {
	pid_t pid;
	FILE *fp;
	unsigned char validar[1024];

	if (argc == 1){
		hreset_help();
		return 1;
	}
	if (argc > 2){
		hreset_help();
		return 1;
	}
	
	if ( (fp = fopen(argv[1], "r")) == NULL ){
		printf("Disco inexistente.\n\n");
		hreset_help();
        	return 1;
	}
	
	if ( !(fread(validar, 1, 1024, fp)) ){
		printf("Erro na leitura do disco.\n\n");
		return 1;
	}

	if ( ((validar[1022]) != 0x33) || (validar[1023] != 0xCC) ){
		printf("Boot inválido\n");
		return 1;
	}
	pid = fork();
	/* Inicio da Execução do código do filho */
	if (pid == 0) {
		char *parametros[] = {"boot.bin", argv[1] , (char *)0 };
		if (execv("boot.bin", parametros) == -1) {
			// TODO: Verificar a causa do erro do execv
			// As causas de erros são várias, mas o codigo é -1 para todas
			printf("Erro no execv.\n");
		}
	}
	/* Erro no fork() */
	else if (pid == -1) {
		// TODO: Melhorar o erro
		// Não tem o q melhorar
		printf("Erro na execução do fork.\n");
	}
	/* Início da execução do código do pai */
	else {
		int filho_status;
		if ( waitpid(pid, &filho_status, 0) == -1 ) {
			// TODO: Verificar causa do erro no waitpid
			// OK
			printf("Processo filho não existe.\n");
		}
		/* Filho finalizou OK */
		if (WIFEXITED(filho_status)) {
			execv("temp.exe", NULL);
			
		}
		else {
			// TODO: Melhorar o erro
			printf("Problema na finalização do filho.\n");
		}
	}
	return 0;
}
