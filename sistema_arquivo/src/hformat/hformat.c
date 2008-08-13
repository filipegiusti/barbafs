/**
 * @file hformat.c
 * @brief Formata um disco com o barbafs.
 * @author Elvio Viçosa, Filipe Giusti, Jerônimo Madruga, Mauro Kade.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include "util.h"
#include "filesystem.h"

#define BOOT1 0x33							/**< Valor do penúltimo setor de boot. */
#define BOOT2 0xCC							/**< Valor do último setor de boot. */
#define BOOT_PATH "boot.bin"				/**< Caminho do arquivo que contém o boot. */
#define HPSYS_PATH "hpsys.bin"				/**< Caminho do HPSYS. */
#define SIZE_SEC 512						/**< Tamanho de segmento em bytes a ser utilizado no sistema de arquivos. */
#define MIN_DISK_SIZE ( 512 * SIZE_SEC )	/**< Tamanho mínimo em bytes que um disco a ser formatado deve ter. */
#define MAX_DISK_SIZE ( 4096 * SIZE_SEC )	/**< Tamanho máximo em bytes que um disco a ser formatado poderá ter. */

char DISK_NAME[255];	/**< Nome do disco. */
FILE *disk;				/**< Arquivo onde está o disco. */
int DISK_SIZE;			/**< Tamanho que o disco terá em bytes, caso precise criar um disco. */
int FORMAT_TYPE;		/**< Opção de formatação. */

//define marcadores
static char HFORMAT[2000] = "gambi_ini0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000gambi_fim";

/**
 * Tipos de formatação possíveis.
 */
enum {
	USING_DISK,			/**< disco ja existe, apenas formata.*/
	CREATING_DISK,		/**< disco nao existe, cria com valor minimo e formata.*/
	CREATING_SIZEDDISK	/**< disco nao existe, tamanho definido pelo argv. Cria e formata.*/
}; 

/**
 * @brief Salva os dois setores de boot no disco.
 * @param tam_hpsys Tamanho em setores do hpsys que foi gravado.
 * @return 0 Caso tenha sido bem sucedida a carga do boot, caso algum erro ocorra encerra o programa com uma mensagem de erro.
 * @todo Adicionar tratamento de erros.
 */
int save_boot(short int tam_hpsys) {
	FILE *boot_file;											/* Arquivo contendo o boot. */
	char boot_content[SIZE_SEC*2];								/* Buffer da transferência do boot de seu arquivo original para o seu destino em disco. */
	struct stat info_boot;										/* Estado do arquivo do setor de boot. */
	short int end_bitmap = (tam_hpsys+2)*SIZE_SEC;
	char marcadores_boot;

	debug("save_boot()");
	/* verifica se é possível abrir o arquivo de boot */
	if ( (boot_file = fopen(BOOT_PATH, "r")) == NULL ) {
		char error_msg[100]; /* Irá conter a mensagem de erro */
		sprintf(error_msg, "Não foi possivel abrir o arquivo %s", BOOT_PATH);
		print_error("0x666", error_msg, 1);
	}
	fseek(disk, 0, SEEK_SET);
	stat(BOOT_PATH, &info_boot);
	/* verifica se o tamanho do boot a ser caregado corresponde ao tamanho de dois setores */
	/*if (info_boot.st_size > 2*SIZE_SEC) {
		print_error("0x005", "Tamanho do boot maior que 2 setores", 1);
	}*/ 														// TODO: Comentando até achar uma solução melhor pro boot.bin
	fread(boot_content, sizeof(char), SIZE_SEC*2, boot_file);	//TODO: Tratar erro
	fwrite(boot_content, sizeof(char), SIZE_SEC*2, disk);		//TODO: Tratar erro
	fclose(boot_file);

	/* Grava o código do boot e o tamanho do hpsys */
	fseek(disk, (2*SIZE_SEC)-2*sizeof(short int)-2*sizeof(char), SEEK_SET);
	fwrite(&end_bitmap, sizeof(short int), 1, disk);			/* Endereço de início do bitmap de setores livres */ //TODO: Tratar erro
	fwrite(&tam_hpsys, sizeof(short int), 1, disk);				/* Número de setores do SO */ //TODO: Tratar erro
	
	// Grava os marcadores do final do boot
	marcadores_boot = BOOT1;
	fwrite(&marcadores_boot, sizeof(char), 1, disk);			//TODO: Tratar erro
	marcadores_boot = BOOT2;
	fwrite(&marcadores_boot, sizeof(char), 1, disk);			//TODO: Tratar erro
	
	debug("BOOT salvo");
	return 0;
}

/**
 * @brief Salva o sistema operacional no disco.
 * @return Retorna o tamanho do SO gravado no disco em setores, caso algum erro ocorra encerra o programa com uma mensagem de erro.
 * 
 * @todo Adicionar alguns tratamentos de erro.
 */
short int save_so() {
	FILE *hpsys;				/* Arquivo do HPSYS. */
	char *buffer;				/* Buffer do arquivo do HPSYS para o seu destino no disco */
	char info_hpsys_str[100];	/* Mensagem de debug que contém o tamanho do HPSYS */
	struct stat info_hpsys;		/* Estado do arquivo do HPSYS. */
	int tam_so_gravado;			/* Em bytes */
	
	/* abertura do hpsys */
	hpsys = fopen(HPSYS_PATH, "rb");
	if (!hpsys) {
		char error_msg[100];											/* Mensagem de erro */
		sprintf(error_msg, "Não foi possivel abrir o arquivo %s", HPSYS_PATH);
		print_error("0x668", error_msg, 1);
	}

	/* pega informacoes do hpsys e mostra no debug */
	stat(HPSYS_PATH, &info_hpsys);
	sprintf(info_hpsys_str, "HPSYS - tamanho: %d bytes", (int)info_hpsys.st_size);
	debug(info_hpsys_str);
	/* fim parte debug hpsys */

	/* deslocando para o 3º setor */
	fseek(disk, 2*SIZE_SEC, SEEK_SET);

	/* copiando hpsys para o 3º setor */
	buffer = (char *) malloc( info_hpsys.st_size );						// TODO: Tratar erro
	fread(buffer, sizeof(char), info_hpsys.st_size, hpsys);				// TODO: Tratar erro
	tam_so_gravado = fwrite(buffer, sizeof(char), info_hpsys.st_size, disk); // TODO: Tratar erro
	debug("HPSYS salvo no disco");
	fclose(hpsys);
	return ( (tam_so_gravado%SIZE_SEC) ? tam_so_gravado/SIZE_SEC + 1 : tam_so_gravado/SIZE_SEC );
}

/**
 * @brief Salva o mapa de bits no disco.
 * @param tam_hpsys Tamanho em setores do hpsys que foi gravado.
 * @return 0 Caso tenha sido bem sucedido a carga do mapa de bits para o disco.
 */
int save_bitmap(short int tam_hpsys) {
	int i, j = 0;
	char bitmap[SIZE_SEC];
	int setores_ocupados_inicialmente = 2 + tam_hpsys + 1 + 2 + 1; /* Boot + hpsys + bitmap + descritores do arquivos + mapa de paginas do root*/
	debug("Salvando bitmap");
	
	for(i = 0 ; i < setores_ocupados_inicialmente ; i++) {
		if ( !(i%8) ) {
			j = 1;
		}
		bitmap[i/8] += j;
		j <<= 1;
	}
	//printf("hpsys: %d\nbitmap: %s\n", tam_hpsys, bitmap);
	fseek(disk, (2+tam_hpsys)*SIZE_SEC, SEEK_SET);			/* boot + hpsys */
	fwrite(bitmap, sizeof(char), SIZE_SEC, disk);
	debug("bitmap salvo");
	return 0;
}

/**
 * @brief Salvar o diretório raiz no disco.
 * @param tam_hpsys Tamanho em setores do hpsys que foi gravado.
 * @return 0 Caso tenha sido bem sucedido a criação da diretório raiz.
 */
int save_root(short int tam_hpsys) {
	short int end_descritores = (2+tam_hpsys+1)*SIZE_SEC;	/* boot + tam_hpsys + bitmap de blocos livres */
	char nome_root[MAX_SIZE_NOME+1] = "";
	char tipo_root = DIR;
	char prot = 0;
	short int end_mapa_paginas = end_descritores+(2*SIZE_SEC); 
	
	char num_arq_diretorio = 0;
	debug("Salvando root");
	
	// Salva descritor do diretório root
	fseek(disk, end_descritores, SEEK_SET);
	fwrite(nome_root, sizeof(char), MAX_SIZE_NOME+1, disk);
	fwrite(&tipo_root, sizeof(char), 1, disk);
	fwrite(&prot, sizeof(char), 1, disk);
	fwrite(&end_mapa_paginas, sizeof(short int), 1, disk);
	
	// Salva mapa de páginas do root
	fseek(disk, end_mapa_paginas, SEEK_SET);
	fwrite(&num_arq_diretorio, sizeof(char), 1, disk);
	fwrite(&end_descritores, sizeof(short int), 1, disk);	// Referencia self
	fwrite(&end_descritores, sizeof(short int), 1, disk);	// Referencia ao pai
	
	debug("root salvo");
	return 0;
}

/**
 * @brief Formata o disco a ser utilizado.
 * @return 0 Caso a formatação tenha sido bem sucedida.
 */
int format_disk() {
	int i;				/* Variável utilizada como contador para percorrer os setores do disco */
	char nulo=0;		/* Variável utilizada como conteúdo para os setores do disco a serem preenchidos */
	short int tam_so;	/* Tamanho em setores */
	char msg[100];

	if (FORMAT_TYPE == CREATING_DISK)
		debug("Criando disco");
	else if (FORMAT_TYPE == USING_DISK)
		debug("Usando disco");
	else if (FORMAT_TYPE == CREATING_SIZEDDISK)
		debug("Criando disco com -s");

	if ( (disk = fopen(DISK_NAME, "wb")) == NULL ) {
		sprintf(msg, "Erro na abertura do disco. Abortando");
		print_error("0x0044", msg, 1);
		exit(EXIT_FAILURE);
	}
	
	/* Caso o disco tenha sido aberto com sucesso, preenche cada um dos seus setores com o valor 0. */
	for (i=0; i < DISK_SIZE; i++) {
		fwrite(&nulo, sizeof(char), 1, disk);
	}
	debug("Disco Zerado");
	
	tam_so = save_so();
	sprintf(msg, "Tamanho do so gravado = %d setores", tam_so);
	debug(msg);
	tam_so *= 1.5;
	save_boot(tam_so);
	save_bitmap(tam_so);
	save_root(tam_so);
	return 0;
}

/**
 * @brief Verifica se um arquivo existe.
 * @param file_path Path do arquivo a ser verificado.
 * @return 1 Arquivo existe.
 * @return 0 Arquivo não existe.
 */
int file_exist(char *file_path) {
	FILE *fp;
	if ( (fp = fopen(file_path, "r")) != NULL ) {
		return 1;
	}

	return 0;
}

/**
 * @brief Imprime o texto de help e aborta a execução.
 * 
 * Imprime o seguinte texto:
 * 
 * Uso: hformat [OPÇÕES] DISCO\n
 * Formata um disco com o sistema de arquivos bfs, e se o disco não existir, cria um com tamanho mínimo.
 * 
 * 		-s NUM	 Cria disco com NUM número de setores.\n
 * 		-h		 Mostra esta ajuda.
 */
void hformat_help() {
	printf("Uso: hformat [OPÇÕES] DISCO\n");
	printf("Formata um disco com o sistema de arquivos bfs, e se o disco não existir,\n");
	printf("cria um com tamanho mínimo.\n\n");
	printf("\t -s NUM \t Cria disco com NUM número de setores.\n");
	printf("\t -h \t\t Mostra esta ajuda.\n\n");
	exit(EXIT_FAILURE);
}

/**
 * @brief Filtra os argumentos passados.
 * 
 * Armazena os argumentos passados nas variáveis globais e se houver algum erro aborta o programa e imprime uma mensagem de como utilizá-lo.
 * 
 * @param argc Número de argumentos
 * @param argv Argumentos 
 */
void filter_argv(int argc, char **argv) {
	struct stat disco_info;
	int size_from_argv;
	char str_erro[100];

	if (argc == 2) {
		// Chamou o help
		if ( !strcmp(argv[1], "-h")) {
			hformat_help();
		}
		// Disco existe
		else if (file_exist(argv[1])) {
			stat(argv[1], &disco_info);
			if (disco_info.st_size >= MIN_DISK_SIZE && disco_info.st_size <= MAX_DISK_SIZE) {
				FORMAT_TYPE = USING_DISK;
				DISK_SIZE = disco_info.st_size;
				strcpy(DISK_NAME, argv[1]);
			} else {
				sprintf(str_erro, "O número ( %d ) de setores é inválido.", (int)disco_info.st_size);
				print_error("0x0007", str_erro, 1);
			}
		}
		// disco nao existe && sem determinar tamanho
		else {
			if (strlen(argv[1]) > 7) {							/** @todo O que que é isso????*/
				FORMAT_TYPE = CREATING_DISK;
				DISK_SIZE = MAX_DISK_SIZE; 
				strcpy(DISK_NAME, argv[1]);
			} else {
				print_error("0x0009", "Nome de arquivo inválido.", 1);
			}
		}
	}
	else if (argc == 4) {
		size_from_argv = atoi(argv[2])*SIZE_SEC;
		if ( !strcmp(argv[1], "-s") ) {
			if (size_from_argv >= MIN_DISK_SIZE && size_from_argv <= MAX_DISK_SIZE) {
				FORMAT_TYPE = CREATING_SIZEDDISK;
				DISK_SIZE = size_from_argv; 
				strcpy(DISK_NAME, argv[3]);
			} else {
				sprintf(str_erro, "O número ( %d ) de setores é inválido. Minimo: %d Maximo: %d", atoi(argv[2]), MIN_DISK_SIZE/SIZE_SEC, MAX_DISK_SIZE/SIZE_SEC);
				print_error("0x0007", str_erro, 1);
			}
		} else {
			print_error("0x0007", "Opcao desconhecida", 1);
		} 
	}
	// Argumentos estão errados.
	else {
		hformat_help();
	}
}

/**
 * @brief Chama as subrotinas e verifica se os parâmetros foram passados corretamente.
 * @param argc Número de parâmetros passados pela linha de comando.
 * @param argv Strings passadas pela linha de comando.
 * @return 0 Se a operação de formatação do disco foi bem sucedida.
 */
int main(int argc, char *argv[]) {
	filter_argv(argc, argv);

	format_disk();
	fclose(disk);
	return 0;
}
