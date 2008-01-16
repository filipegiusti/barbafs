#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
//#include "hformat.h"
#include "util.h"

#define BOOT1 0x77
#define BOOT2 0x33
#define BOOT_PATH "boot.bin"
//#define DISK_NAME "disco"
#define HPSYS_PATH "hpsys"
#define SIZE_SEC 512
#define MIN_DISK_SIZE (256)
#define MAX_DISK_SIZE ( 1024 * 1024 * 2)

char DISK_NAME[255];
int DISK_SIZE;
FILE *disk;

int save_boot() {
	FILE *boot_file;
	char boot_content[SIZE_SEC*2];
	struct stat info_boot;

	if ( (boot_file = fopen(BOOT_PATH, "rb")) == NULL ) {
		debug("Erro na abertura de boot");
	} else {
		fseek(disk, 0, SEEK_SET);
		stat(BOOT_PATH, &info_boot);
		fread(boot_content, sizeof(char), info_boot.st_size, boot_file);
		fwrite(boot_content, sizeof(char), info_boot.st_size, disk);
		fclose(boot_file);
		debug("BOOT salvo");
	}
	return 1;
}


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

	/* deslocando para o 3 setor */
	fseek(disk, 2*SIZE_SEC, SEEK_SET);

	/* copiando hpsys para o 3 setor */
	buffer = (char *) malloc( info_hpsys.st_size );
	fread(buffer, sizeof(char), info_hpsys.st_size, hpsys);
	fwrite(buffer, sizeof(char), info_hpsys.st_size, disk);
	debug("HPSYS salvo no disco");
	fclose(hpsys);
	return 1;
}


int save_bitmap() {
	return 1;
}

int save_root() {
	return 1;
}


int open_disk() {
	return (disk = fopen(DISK_NAME, "wb")) ? 1 : 0; 
}


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


/*
 * se should_exit == 1 mostra erro e termina programa (erro fatal)
 */

void print_error(char *erro, char *descricao, int should_exit) {
	printf("HFORMAT 0.4-160108 alpha\n");	
	printf("------------------------\n");
	printf("ERRO.....: %s\n", erro);
	printf("DESCRICAO: %s\n\n", descricao);
	(should_exit) ? exit(EXIT_FAILURE) : printf("\t"); 
}


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
