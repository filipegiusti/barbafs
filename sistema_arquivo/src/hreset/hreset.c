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

int main(int argc, char *argv[]) {
	if (argc == 1){
		printf("Nenhum argumento passado.\n");
		printf("Favor digitar o nome do disco a ser inicializado\n");
		return 1;
	}
	if (argc > 2){
		printf("Muitos argumentos.\n");
		printf("Favor digitar o nome do disco a ser inicializado\n");
		return 1;
	}
	pid_t pid;
	pid = fork();
	// TODO: Validar os parametros passados pelo usuário
	// TODO: Criar help caso parametros sejam passados errados
	// TODO: Verificar se boot está válido
	// TODO: Criar arquivo com os 1024 bytes do boot
	// DONE.
	FILE *fp;
	char validar[1024];
	
	if ( (fp = fopen(argv[1], "r")) == NULL ){
		printf("Disco inexistente.\n");
        	return 1;
	}
	
	if ( !(fread(&validar, 1, 1024, fp)) ){
		printf("Erro na leitura do disco.");
	}
	
	if ( (validar[1022] != 0x33) || (validar[1023] != 0xCC) ){
		printf("Boot inválido");
	}
	
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
