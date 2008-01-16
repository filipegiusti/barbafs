/**
 * @file hreset.c
 * @brief Executável responsável pela indicação do disco virtual e identificação do disco a ser utilizado.
 * @author Filipe Giusti
 *  @version 1.0
 *  @date    16/01/2007
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int agrc, char *argv[]) {
	pid_t pid;
	pid = fork();
	// TODO: Validar os parametros passados pelo usuário
	// TODO: Criar help caso parametros sejam passados errados
	// TODO: Verificar se boot está válido
	// TODO: Criar arquivo com os primeiros 1024 bytes do boot

	/* Inicio da Execução do código do filho */
	if (pid == 0) {
		char *parametros[] = {"boot.bin", argv[1] , (char *)0 };
		// TODO: trocar funçaõ para execvp que recebe um descritor de arquivo
		if (execv("boot.bin", parametros) == -1) {
			// TODO: Verificar a causa do erro do execv
			printf("Erro no execv.\n");
		}
	}
	/* Erro no fork() */
	else if (pid == -1) {
		// TODO: Melhorar o erro
		printf("Deu erro.\n");
	}
	/* Início da execução do código do pai */
	else {
		int filho_status;
		if ( waitpid(pid, &filho_status, 0) == -1 ) {
			// TODO: Verificar causa do erro no waitpid
			printf("Deu erro no waitpid.\n");
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
