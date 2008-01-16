/**
 * @file hformat.c
 * @brief Executável responsável pela formatação do disco a ser utilizado e carga doS.O. no mesmo.
 * @author Elvio Viscosa, Filipe Giusti, Jerônimo Madruga, Mauro Kade.
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
#define SIZE_SEC 512 /**< Define o tamanho de segmento a ser utilizado no sistema de arquivos */
#define MIN_DISK_SIZE (256) /**< Define o tamanho minímo que um disco a ser formatado deve ter */
#define MAX_DISK_SIZE ( 1024 * 1024 * 2) /**< Define o tamanho máximo que um disco a ser formatado poderá ter */

char DISK_NAME[255]; /**< Variável que irá conter o nome do disco a ser utilizado */
int DISK_SIZE; /**< Variável que indica o tamanho do disco a ser utilizado */
FILE *disk; /**< Variável utilizada para referenciar o disco que estará sendo utilizado */

/**
 * @fn int save_boot()
 * @brief Função responsável por salvar os dois setores de boot no disco.
 * @return 1 Caso tenha sido bem sucedido a carga do boot.
*/
int save_boot() {
	FILE *boot_file; /* Variavel que será utilizada para abrir o arquivo contendo o boot. */
	char boot_content[SIZE_SEC*2]; /* Variavel que sera utilizada para transferência do boot de seu arquivo original para o seu destino em disco. */
	struct stat info_boot; /* Variavel utilizada para armazenar o estado do arquivo do setor de boot. */

	/* verifica se é possível abriro arquivo de boot */
	if ( (boot_file = fopen(BOOT_PATH, "rb")) == NULL ) {
		debug("Erro na abertura de boot");
	} else {
		fseek(disk, 0, SEEK_SET);
		stat(BOOT_PATH, &info_boot);
		/* verifica se o tamanho do boot a ser caregado corresponde ao tamanho de dois setores */
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
 * @fn int save_so()
 * @brief Função responsável por salvar o sistema operacional no disco.
* @return 1 Caso tenha sido bem sucedido a carga do sistema operacional para o disco. 
 */
int save_so() {
	FILE *hpsys; /* Variavel que sera utilizada para a abertura do arquivo do HPSYS. */
	char *buffer; /* Variavel que sera utilizada para transferência do arquivo do HPSYS para o seu destino no disco */
	char info_hpsys_str[100]; /* variavel que armazena a mensagem que contém o tamanho do HPSYS */
	struct stat info_hpsys; /* Variavel utilizada para armazenar o estado do arquivo do HPSYS. */

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
 * @fn int save_bitmap()
 * @brief Função responsável por salvar o mapa de bits no disco.
 * @return 1 Caso tenha sido bem sucedido a carga do mapa de bits para o disco.
 */
int save_bitmap() {
	return 1;
}

/**
 * @fn int save_root()
 * @brief Função responsável por salvar o diretório raiz no disco.
 * @return 1 Caso tenha sido bem sucedido a criação da diretório raiz.
 */
int save_root() {
	return 1;
}

/**
 * @brief Função que realiza a abertura do disco a ser salvo.
 * @return 1 Caso tenha sido bem sucedido a abertura do disco.
 * @return 0 Caso tenha ocorrido um erro na abertura do arquivo.
 */
int open_disk() {
	return (disk = fopen(DISK_NAME, "wb")) ? 1 : 0; 
}

/**
 * @fn int format_disk()
 * @brief Função que formata o disco a ser utilizado.
 * @return 1 Caso a formatação tenha sido bem sucedida.
  */
int format_disk() {
	int i; /* Variável utilizada como contador para percorrer os setores do disco */
	char nulo=0; /* Variável utilizada como conteúdo para os setores do disco a serem preenchidos */
	char msg[100]; /* Variável que irá guardar amensagem que indica o tamanho do disco encontrado */

	/* Verifica se é possível abrir o disco */
	if (!open_disk()) {
		debug("erro na abertura do arquivo de disco");
		exit(EXIT_FAILURE);
	}
	sprintf(msg, "Tamanho do disco encontrado = %d bytes", (int)DISK_SIZE);
	debug(msg);

	/* Caso o disco tenha sido aberto com sucesso, preenche cada um dos seus setores com o valor 0. */
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
 * @fn int main(int argc, char *argv[])
 * @brief Função principal do hformat.c, responsável por chamar as subrotinas e verificar se os parametros foram passados corretamente.
 * @param argc indica o número de parametros repassados pela linha de comando.
 * @param argv string que representa os parametros repassados na linha de comando.
 * @return 1 Se a operação de formatação do disco foi bem sucedida.
 */
int main(int argc, char *argv[]) {
	struct stat info_disk;
	char desc[100];
	FILE *fp;
	
	debug("Iniciando HFORMAT");

	/* Verifica se o número de parametros repassados é 2 */
	if (argc != 2)
		print_error("0x0001", "Numero de parametros incorretos", 1);

	/* Verifica se o arquivo com o nome do disco repassado existe */
	if (!(fp = fopen(argv[1], "r")))
		print_error("0x0002", "Arquivo de disco nao encontrado", 1);
	fclose(fp);

	/* Verifica se o tamanho do disco é válido (os limites mínimos e máximos são definidos no ínicio do arquivo  */
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
