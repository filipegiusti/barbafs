/**
 * @file shell_func.c
 * @brief Fun��es do shell.
 * @author Elvio Vicosa, Filipe Giusti, Jerônimo Madruga, Leonardo Lobo, Mauro Kade.
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
	
	//TODO: verificar se 0(zero) � retorno OK
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
	
	//TODO: verificar se 0(zero) � retorno OK
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
	
	//TODO: verificar se 0(zero) � retorno OK
	//TODO: verificar segundo par�metro de bfs_aset_prot
	if (bfs_set_prot(arq, '1') != 0) {
		printf("Erro");
	}
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
	
	//TODO: verificar se 0(zero) � retorno OK
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


//TODO: exibe uma descri��o dos comandos do shell;
//TODO: se for passado apenas [help], sem nenhum outro par�metro, lista todos os comandos
//TODO: se for passado [help] + comando, exibe a sintaxe correta do comando especificado
void func_help(int argc, char *argv[]) {

     if (argc > 2) {
                printf("Quantidade invalida de parametros! \n");
                printf("No maximo 2 parametros! \n");
                return;         
     }
     
     if (argv[2] == " ") {
                printf("\nHELP DO SHELL DE COMANDOS. \n\n\n\n");
                printf("ASM       Carrega arquivos objeto para a memoria (.OBJ). \n\n");     
                printf("COPY      Copia um arquivo para outro local. \n\n");     
                printf("DEL       Exclui um arquivo. \n\n");
                printf("DIR       Exibe uma lista de arquivos e subpastas em uma pasta. \n\n");
                printf("EXEC      Executa arquivos com extensao (.EXE). \n\n");     
                printf("EXPORT    Copia um arquivo do HPSYS para o disco do Windows. \n\n");
                printf("FIND      Procura uma sequencia de texto em um arquivo. \n\n");
                printf("FORMAT    Formata um disco. \n\n");     
                printf("IMPORT    Copia um arquivo do Windows para o disco do HPSYS. \n\n");  
                printf("LINK      Carrega uma lista de arquivos objeto. \n\n");   
                printf("LIST      Exibe uma lista de arquivos e subpastas em uma pasta. \n\n");     
                printf("PROTECT   Altera o modo de protecao de um arquivo. \n\n");
                printf("REN       Altera o nome de um arquivo. \n\n");
                printf("RUN       Executa arquivos da maquina virtual (.HPX). \n\n");     
                printf("SHUTDOWN  Encerra o processamento e desliga a maquina virtual. \n\n");
     }
     
     if (argv[2] == "asm") {
                printf("ASM \n\nCarrega arquivos objeto para a memoria (.OBJ) \n\n");
                printf("A sintaxe do comando e: \n\n");
                printf("[asm]  <arquivo.fonte> \n");
     }
     
     if (argv[2] == "copy") {
                printf("COPY \n\nCopia um arquivo para outro local \n\n");
                printf("A sintaxe do comando e: \n\n");
                printf("[copy]  <arquivo_1.tipo>  <arquivo_2.tipo> \n");
     }
     
     if (argv[2] == "del") {
                printf("DEL \n\nExclui um arquivo \n\n");
                printf("A sintaxe do comando e: \n\n");
                printf("[del]  <arquivo.tipo> \n");
     }
     
     if (argv[2] == "dir") {
                printf("DIR \n\nExibe uma lista de arquivos e subpastas em uma pasta \n\n");
                printf("A sintaxe do comando e: \n\n");
                printf("[dir] \n");
     }
     
     if (argv[2] == "exec") {
                printf("EXEC \n\nExecuta arquivos com extensao (.EXE) \n\n");
                printf("A sintaxe do comando e: \n\n");
                printf("[exec]  <arquivo.EXE> \n");
     }
     
     if (argv[2] == "export") {
                printf("EXPORT \n\nCopia um arquivo do HPSYS para o disco do Windows \n\n");
                printf("A sintaxe do comando e: \n\n");
                printf("[export]  <arquivo.tipo> \n");
     }
     
     if (argv[2] == "format") {
                printf("FORMAT \n\nFormata um disco \n\n");
                printf("A sintaxe do comando e: \n\n");
                printf("[format]  <drive A ou B>  <nome arquivo> \n");
     } 
     
     if (argv[2] == "import") {
                printf("IMPORT \n\nCopia um arquivo do Windows para o disco do HPSYS \n\n");
                printf("A sintaxe do comando e: \n\n");
                printf("[import]  <arquivo.tipo> \n");
     }
     
     if (argv[2] == "link") {
                printf("LINK \n\nCarrega uma lista de arquivos objeto \n\n");
                printf("A sintaxe do comando e: \n\n");
                printf("[link]  <arquivo_1.OBJ>  <arquivo_2.OBJ>  ...  <arquivo_n.OBJ> \n");
     }
     
     if (argv[2] == "list") {
                printf("LIST \n\nExibe uma lista de arquivos e subpastas em uma pasta \n\n");
                printf("A sintaxe do comando e: \n\n");
                printf("[list]  <nome diretorio> \n");
     }

     if (argv[2] == "protect") {
                printf("PROTECT \n\nAltera o modo de protecao de um arquivo \n\n");
                printf("A sintaxe do comando e: \n\n");
                printf("[protect]  <arquivo.tipo> \n");
     }
     
     if (argv[2] == "ren") {
                printf("REN \n\nAltera o nome de um arquivo \n\n");
                printf("A sintaxe do comando e: \n\n");
                printf("[ren]  <arquivo.tipo> \n");
     }
     
     if (argv[2] == "run") {
                printf("RUN \n\nExecuta arquivos da maquina virtual (.HPX) \n\n");
                printf("A sintaxe do comando e: \n\n");
                printf("[run]  <arquivo.HPX> \n");
     }

     if (argv[2] == "shutdown") {
                printf("SHUTDOWN \n\nEncerra o processamento e desliga a maquina virtual \n\n");
                printf("A sintaxe do comando e: \n\n");
                printf("[shutdown] \n");
     }
     
     exit(0);
}


