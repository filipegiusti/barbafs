/**
 * @file filesystem.c
 * @brief Implementa��o do sistema de arquivos.
 * @author Elvio Vicosa, Filipe Giusti, Jerônimo Madruga, Leonardo Lobo, Mauro Kade.
 * @version 1.0
 * @date    25/01/2007
 */

#include <stdio.h>
#include "filesystem_internal.h"

int bfs_create(char *caminho) {
	endereco_disco diretorio;
	diretorio = verifica_caminho(caminho);
	if (diretorio == 0) {
		return 1;//TODO: ERRO
	}
	//TODO: Verificar a validade do caminho
	//TODO: Criar descritor
	//TODO: Criar mapa de paginas
	//TODO: Alocar uma pagina
	//TODO: Tabela de c�digos de retorno
	return 0;
}

arquivo bfs_open(char *caminho, enum modo_abertura_arquivo modo){
	printf("bfs_open dummy\n");
	return 0;
}

int bfs_delete(char *caminho) {
	printf("bfs_delete dummy\n");
	return 0;
}

int bfs_close(arquivo id) {
	printf("bfs_close dummy\n");
	return 0;
}

int bfs_read(arquivo id, char *buffer, int nbytes) {
	printf("bfs_read dummy\n");
	return 0;
}

int bfs_write(arquivo id, char *buffer, int nbytes) {
	printf("bfs_write dummy\n");
	return 0;
}

int bfs_get_nome(arquivo arq, char *buffer_caminho) {
	printf("bfs_get_nome dummy\n");
	return 0;
}

char bfs_get_prot(arquivo arq) {
	printf("bfs_get_prot dummy\n");
	return 0;
}

enum tipo_arquivo bfs_get_tipo(arquivo arq) {
	printf("bfs_get_tipo dummy\n");
	return 0;
}

int bfs_set_nome(arquivo id, char *nome) {
	printf("bfs_ dummy\n");
	return 0;
}

int bfs_set_prot(arquivo id, char prot) {
	printf("bfs_set_prot dummy\n");
	return 0;
}

int bfs_set_tipo(arquivo id, enum tipo_arquivo novo_tipo) {
	printf("bfs_set_tipo dummy\n");
	return 0;
}

int bfs_create_dir(char *caminho) {
	printf("bfs_create_dir dummy\n");
	return 0;
}

int bfs_delete_dir(char *caminho) {
	printf("bfs_delete_dir dummy\n");
	return 0;
}

int bfs_set_cwd(char *caminho) {
	printf("bfs_set_cwd dummy\n");
	return 0;
}

char *bfs_get_cwd() {
	printf("bfs_get_cwd dummy\n");
	return 0;
}

diretorio bfs_open_dir(char *caminho) {
	printf("bfs_open_dir dummy\n");
	return 0;
}

int bfs_close_dir(diretorio dir) {
	printf("bfs_close_dir dummy\n");
	return 0;
}

int bfs_read_dir(diretorio dir, char *buffer_caminho) {
	printf("bfs_read_dir dummy\n");
	return 0;
}

int bfs_rewind_dir(diretorio dir) {
	printf("bfs_rewind_dir dummy\n");
	return 0;
}

// ======== Fun��es auxiliares

/**
 * @fn endereco_disco verifica_caminho(char *caminho)
 * @brief Verifica se o caminho passado j� existe no sistema de arquivos.
 * @param caminho O caminho a ser verificado.
 * @return O endere�o no disco do descritor do �ltimo arquivo/diret�rio do caminho verificado.
 */
endereco_disco verifica_caminho(char *caminho) {
	printf("verifica_caminho dummy\n");
	return 0;
}
