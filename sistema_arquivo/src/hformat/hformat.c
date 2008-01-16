/**
 * @file hformat.c
 * @brief Executável responsável formatação do disco a ser utilizado
 * @author Elvio Viscosa, Filipe Giusti, Mauro Kade.
 *  @version 1.0
 *  @date    16/01/2007
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
//#include "hformat.h"
#include "util.h"

#define BOOT1 0x77 /**< Define o conteúdo do primeiro setor de boot. */
#define BOOT2 0x33 /**< Define o conteúdo do segundo setor de boot. */
#define BOOT_PATH "boot.bin" /**< Define a localização do arquivo que contém as informações do boot. */
//#define DISK_NAME "disco"
#define HPSYS_PATH "hpsys" /**< Define a localização do HPSYS */
#define SIZE_SEC 512 /**< Define o tamanho de segmento a ser utilizado no S.O. */
#define MIN_DISK_SIZE (256) /**< Define o tamanho minímo que um disco onde o S.O. será gravado deve ter */
#define MAX_DISK_SIZE ( 1024 * 1024 * 2) /**< Define o tamanho máximo que um disco onde o S.O. será gravado poderá ter */

char DISK_NAME[255];
int DISK_SIZE;
FILE *disk;

/**
 * Função responsável por salvar os dois setores de boot no disco.
 * @return 1 Caso tenha sido bem sucedido a carga do boot.
*/
int save_boot() {
	FILE *boot_file;
	char boot_content[SIZE_SEC*2];
	struct stat info_boot;

	/* verifica se é possível abriro arquivo de boot */
	if ( (boot_file = fopen(BOOT_PATH, "rb")) == NULL ) {
		debug("Erro na abertura de boot");
	} else {
		fseek(disk, 0, SEEK_SET);
		stat(BOOT_PATH, &info_boot);
		if (info_boot.st_size > 2*SIZE_SEC) {
			print_error("0x005", "Tamanho do boot maior que 2 setores", 1);
		}
		fread(boot_content, sizeof(char), info_boot.st_size, boot_file);
		fwrite(boot_content, sizeof(char), info_boot.st_size, disk);
		fclose(boot_file);
		debug("BOOT salvo");
	}
	return 1;
}

/**
 * Função responsável por salvar o sistema operacional no disco.
 */
int save_so() {
	FILE *hpsys;
	char *buffer;
	char info_hpsys_str[100];
	struct stat info_hpsys;

	/* abertura do hpsys */
	hpsys = fopen(HPSYS_PATH, "rb");
	if (!hpsys) {
		debug("Erro na leitura binaria do HPSYS");
		exit(EXIT_FAILURE);
	}

	/* pega informacoes do hpsys e mostra no debug */
	stat(HPSYS_PATH, &info_hpsys);
	sprintf(info_hpsys_str, "HPSYS - tamanho: %d bytes", (int)info_hpsys.st_size);
	debug(info_hpsys_str);
	/* fim parte debug hpsys */

	/* deslocando para o 3º setor */
	fseek(disk, 2*SIZE_SEC, SEEK_SET);

	/* copiando hpsys para o 3º setor */
	buffer = (char *) malloc( info_hpsys.st_size );
	fread(buffer, sizeof(char), info_hpsys.st_size, hpsys);
	fwrite(buffer, sizeof(char), info_hpsys.st_size, disk);
	debug("HPSYS salvo no disco");
	fclose(hpsys);
	return 1;
}

/**
 * Função responsável por salvar o mapa de bits no disco.
 * @return 1 Caso tenha sido bem sucedido a carga do mapa de bits para o disco.
 */
int save_bitmap() {
	return 1;
}

/**
 * Função responsável por salvar o diretório raiz no disco.
 * @return 1 Caso tenha sido bem sucedido a criação da diretório raiz.
 */
int save_root() {
	return 1;
}

/**
 * Função que realiza a abertura do disco a ser salvo.
 * @return 1 Caso tenha sido bem sucedido a abertura do disco.
 * @return 0 Caso tenha ocorrido um erro na abertura do arquivo.
 */
int open_disk() {
	return (disk = fopen(DISK_NAME, "wb")) ? 1 : 0; 
}

/**
 * Função que formata o disco a ser utilizado.
 * @return 1 Caso a formatação tenha sido bem sucedida.
  */
int format_disk() {
	int i;
	char nulo=0;
	char msg[100];

	if (!open_disk()) {
		debug("erro na abertura do arquivo de disco");
		exit(EXIT_FAILURE);
	}
	sprintf(msg, "Tamanho do disco encontrado = %d bytes", (int)DISK_SIZE);
	debug(msg);

	for (i=0; i < DISK_SIZE; i++) {
		fwrite(&nulo, sizeof(char), 1, disk);	
	}

	debug("Disco Formatado");
	save_boot();
	save_so();
	//save_bitmap();
	//save_root();
	//fclose(disk);
	return 1;
}

/**
 * Função principal do hformat.c, responsável por chamar as subrotinas e verificar se os parametros foram passados corretamente.
 * @return 1 Se a operação de formatação do disco foi bem sucedida.
 */
int main(int argc, char *argv[]) {
	struct stat info_disk;
	char desc[100];
	FILE *fp;
	
	debug("Iniciando HFORMAT");

	if (argc != 2)
		print_error("0x0001", "Numero de parametros incorretos", 1);

	if (!(fp = fopen(argv[1], "r")))
		print_error("0x0002", "Arquivo de disco nao encontrado", 1);
	fclose(fp);

	if (!stat(argv[1], &info_disk) && info_disk.st_size / 1024 >= MIN_DISK_SIZE && info_disk.st_size / 1024 <= MAX_DISK_SIZE)
		goto valid_disk_size;
	else {
		sprintf(desc, "Tamanho do disco encontrado (%2.2f Kb) invalido. O tamanho deve ser entre %d e %d Kb", (float)info_disk.st_size/1024, MIN_DISK_SIZE, MAX_DISK_SIZE);
		print_error("0x0003", desc, 1);
	}

valid_disk_size:
	DISK_SIZE = info_disk.st_size;
	strcpy(DISK_NAME, argv[1]);
	format_disk();
	fclose(disk);
	return 1;
}
