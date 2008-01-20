#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell_cmd.h"

// funcoes teste 
void func_assar_batata(int argc, char *argv[]) {
	int i;
	printf("Listando comandos de argv da funcao: assar_batata\n");
	for (i=0; i < argc; i++) {
		printf("argv[%d] = %s\n", i, argv[i]);
	}
	printf("\n");
}

void func_fazer_cafe() {
	printf("executando funcao de fazer cafe\n");
}
// fim das funcoes que serao usadas para teste



int main(int argc, char *argv[]) {
	
	// declarando comandos que serao usados
	append_command_list(&command_list, build_command("assar_batata", &func_assar_batata));
	append_command_list(&command_list, build_command("fazer_cafe", &func_fazer_cafe));

	// valores teste 
	int _argc = 2;
	char *_argv[] = {"./nome_comando", "tipo_batata"};
	// fim valores teste
	

	// fazendo chamada aos comandos
	int command_found;
	command_found = call_command("assar_batata", _argc, _argv);
	if (!command_found)
		printf("O comando nao foi encontrado...\n");

	command_found = call_command("fazer_cafe", _argc, _argv);
	if (!command_found)
		printf("O comando nao foi encontrado...\n");

	// caso que comando nao eh encontrado
	command_found = call_command("comando_que_nao_existe", _argc, _argv);
	if (!command_found)
		printf("O comando nao foi encontrado...\n");



	return 0;
}
