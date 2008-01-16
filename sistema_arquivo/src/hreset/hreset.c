#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int agrc, char *argv[]) {
	pid_t pid;
	pid = fork();
	if (pid == 0) {
		char *parametros[] = {"teste", "arquivoTAL\0\0\0\0\0\0\0\0" , (char *)0 };
		printf("Sou o filho\n");
		if (execv("boot.bin", parametros) == -1) {
			printf("Erro no execv.\n");
		}
	}
	else if (pid == -1) {
		printf("Deu erro.\n");
	}
	else {
		int filho_status;
		if ( waitpid(pid, &filho_status, 0) == -1 ) {
			printf("Deu erro no waitpid.\n");
		}
		if (WIFEXITED(filho_status)) {
			printf("Filho finalizou LEGAL\n");
			
		}
		else {
			printf("Problema na finalização do filho.\n");
		}
		printf("Sou o pai\n");
	}
	return 0;
}
