/**
 * @file shell_func.c
 * @brief Funções do shell.
 * @author Elvio Vicosa, Filipe Giusti, JerÃ´nimo Madruga, Leonardo Lobo, Mauro Kade.
 * @version 0.1 alpha
 * @date    01/02/2007
 */

#include <stdio.h>
#include "filesystem.h"


void func_dir(int argc, char *argv[]) {
	
	if (argc > 1) {
		printf("Excesso de parametros para o comando dir\n");
		return;
	}
	
	//caminho = *bfs_get_cwd(); // pega o caminho atual. isso se for necessario, TODO: deve-se usar conceito de diretorio atual.
	//bfs_read_dir();		//TODO: le o diretorio atual, pega o inicio da lista de arquivos e lista elas na tela.
}

void func_del(int argc, char *argv[]) {
	
	if (argc < 2) {
		printf("Poucos parametros para o comando del\n");
		return;
	}
	if (argc > 2) {
		printf("Excesso de parametros para o comando del\n");
		return;
	}
	
	//TODO: verificar se 0(zero) é retorno OK
	if (bfs_delete(argv[2]) != 0) {
		printf("Erro");
	}
}

void func_rename(int argc, char *argv[]) {
	arquivo arq;
	
	if (argc < 2) {
		printf("Poucos parametros para o comando rename\n");
		return;
	}
	if (argc > 3) {
		printf("Excesso de parametros para o comando rename\n");
		return;
	}
	
	arq = bfs_open(argv[2], READ_WRITE);
	
	//TODO: verificar se 0(zero) é retorno OK
	if (bfs_set_nome(arq, argv[3]) != 0) {
		printf("Erro");
	}
	
	if (bfs_close(arq) != 0) {
		printf("Erro");
	}
}

void func_protect(int argc, char *argv[]) {
	arquivo arq;
	
	if (argc < 2) {
		printf("Poucos parametros para o comando del\n");
		return;
	}
	if (argc > 2) {
		printf("Excesso de parametros para o comando del\n");
		return;
	}
	
	arq = bfs_open(argv[2], READ_WRITE);
	
	//TODO: verificar se 0(zero) é retorno OK
	//TODO: verificar segundo parâmetro de bfs_aset_prot
	/*if (bfs_set_prot(arq, 1) != 0) {
		printf("Erro");
	}*/
}

void func_copy(int argc, char *argv[]) {
	arquivo arq1, arq2;
	
	if (argc < 2) {
		printf("Poucos parametros para o comando del\n");
		return;
	}
	if (argc > 3) {
		printf("Excesso de parametros para o comando del\n");
		return;
	}
	
	//TODO: verificar se 0(zero) é retorno OK
	if (bfs_create(argv[3]) != 0) {
		printf("Erro");
	}
	
	arq1 = bfs_open(argv[2], READ);
	arq2 = bfs_open(argv[3], WRITE);
//TODO ver os nbytes q se deve ler / escrever	
/*	if (bfs_read(arq1, buffer, int nbytes) != 0){
		printf("Erro");
	}
	if (bfs_write(arq2, buffer, int nbytes) != 0){
		printf("Erro");
	}*/
	
	if (bfs_close(arq1)) {
		printf("Erro");
	}
	if (bfs_close(arq2)) {
		printf("Erro");
	}
}

//TODO
void func_list(int argc, char *argv[]) {
}

//TODO
void func_shutdown(int argc, char *argv[]) {

}

//TODO
void func_import(int argc, char *argv[]) {

}

//TODO
void func_export(int argc, char *argv[]) {

}

//TODO
void func_format(int argc, char *argv[]) {

}

//TODO
void func_run(int argc, char *argv[]) {

}

//TODO
void func_exec(int argc, char *argv[]) {

}

//TODO
void func_asm(int argc, char *argv[]) {

}

//TODO
void func_link(int argc, char *argv[]) {

}






