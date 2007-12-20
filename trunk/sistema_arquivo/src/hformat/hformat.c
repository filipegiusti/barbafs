#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
//#include "hformat.h"
#include "util.h"

#define BOOT1 0x77
#define BOOT2 0x33
#define DISK_SIZE 4096
#define DISK_NAME "disco"
#define HPSYS_PATH "hpsys.bin"
#define SIZE_SEC 512

FILE *disk;
int save_boot() {
	return 1;
}


int save_so() {
	FILE *hpsys;
	int i;
	char buffer[SIZE_SEC];
	char info_hpsys_str[100];
	struct stat info_hpsys;

	/* abertura do hpsys */
	hpsys = fopen(HPSYS_PATH, "rb");
	if (!hpsys) {
		debug("Erro na leitura binaria de hpsys.bin");
		exit(EXIT_FAILURE);
	}

	/* pega informacoes do hpsys e mostra no debug */
	stat(HPSYS_PATH, &info_hpsys);
	sprintf(info_hpsys_str, "hpsys - tamanho: %d bytes", (int)info_hpsys.st_size);
	debug(info_hpsys_str);
	/* fim parte debug hpsys */

	/* deslocando para o 3 setor */
	fseek(disk, 2*SIZE_SEC, SEEK_SET);

	/* copiando hpsys para o 3 setor */
	for (i=0; i < 1; i++) {
		fread(buffer, sizeof(char), SIZE_SEC, hpsys);
		fwrite(buffer, sizeof(char), SIZE_SEC, disk);
	} 

	fclose(hpsys);
	return 1;
}


int save_bitmap() {
	return 1;
}

int save_root() {
	return 1;
}


int create_disk() {
	return (disk = fopen(DISK_NAME, "wb")) ? 1 : 0; 
}


int format_disk() {
	int i;
	char nulo=0;

	if (!create_disk()) {
		debug("erro na abertura do arquivo de disco");
		exit(EXIT_FAILURE);
	}

	for (i=0; i < DISK_SIZE; i++) {
		fwrite(&nulo, sizeof(char), 1, disk);	
	}

	save_boot();
	save_so();
	save_bitmap();
	save_root();

	fclose(disk);
	return 1;
}

int main(int argc, char *argv[]) {
	debug("Iniciando HFORMAT");
	format_disk();
	return 0;
}
