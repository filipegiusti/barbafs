/**
 * @file hformat.c
 * @brief Executável responsável pela formatação do disco a ser utilizado.
 * @author Elvio Viçosa, Filipe Giusti, Jerônimo Madruga, Mauro Kade.
 * @version 1.0
 * @date    16/01/2007
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include "util.h"

#define BOOT1 0x33 /**< Define o conteúdo do penúltimo setor de boot. */
#define BOOT2 0xCC /**< Define o conteúdo do último setor de boot. */
#define BOOT_PATH "boot.bin" /**< Define a localização do arquivo que contém as informações do boot. */
#define HPSYS_PATH "hpsys.bin" /**< Define a localização do HPSYS. */
#define SIZE_SEC 512 /**< Define o tamanho de segmento a ser utilizado no sistema de arquivos */
#define MIN_DISK_SIZE ( 512 * SIZE_SEC ) /**< Define o tamanho mínimo em bytes que um disco a ser formatado deve ter */
#define MAX_DISK_SIZE ( 4096 * SIZE_SEC ) /**< Define o tamanho máximo em bytes que um disco a ser formatado poderá ter */

struct stat info_disk; /**< Estrutura que armazena as informações de estado do arquivo que representa o disco */
char DISK_NAME[255]; /**< Variável que irá conter o nome do disco a ser utilizado */
FILE *disk; /**< Variável utilizada para referenciar o disco que estará sendo utilizado */
int DISK_SIZE; /**< Tamanho que o disco terá, caso precise criar um disco */
int FORMAT_TYPE; /**< Opção de formatação */
enum {USING_DISK, CREATING_DISK, CREATING_SIZEDDISK}; /**<
 * define os tipos de format que poderao ser usados 
 * 1 - disco ja existe, apenas formata
 * 2 - disco nao existe, cria com valor minimo e formata
 * 3 - disco nao existe, tamanho definido pelo argv. Cria e formata
 * */

int save_boot(short int tam_hpsys);
short int save_so();
int save_bitmap(short int tam_hpsys);
int save_root(short int tam_hpsys);
int format_disk();

/**
 * @fn int save_boot(int tam_hpsys)
 * @brief Função responsável por salvar os dois setores de boot no disco.
 * @param tam_hpsys Tamanho em setores do hpsys que foi gravado.
 * @return 1 Caso tenha sido bem sucedida a carga do boot, caso algum erro ocorra encerra o programa com uma mensagem de erro.
 */
int save_boot(short int tam_hpsys) {
	FILE *boot_file; /* Variável que será utilizada para abrir o arquivo contendo o boot. */
	char boot_content[SIZE_SEC*2]; /* Variável que sera utilizada para transferência do boot de seu arquivo original para o seu destino em disco. */
	struct stat info_boot; /* Variável utilizada para armazenar o estado do arquivo do setor de boot. */
	short int end_bitmap = (tam_hpsys+2)*SIZE_SEC;

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
	}*/ // TODO: Comentando até achar uma solução melhor pro boot.bin
	fread(boot_content, sizeof(char), SIZE_SEC*2, boot_file); //TODO: Tratar erro
	fwrite(boot_content, sizeof(char), SIZE_SEC*2, disk); //TODO: Tratar erro
	fclose(boot_file);

	/* Grava o código do boot e o tamanho do hpsys */
	fseek(disk, (2*SIZE_SEC)-6-1, SEEK_SET); /* 6 é a soma de 2 short int mais 2 bytes pros marcadores e -1 pra acertar a referência */
	fwrite(&end_bitmap, sizeof(short int), 1, disk); /* Início bitmap de setores livres *///TODO: Tratar erro e ESTA ERRADO O VALOR
	end_bitmap -= 2*SIZE_SEC;
	fwrite(&end_bitmap, sizeof(short int), 1, disk); //TODO: Tratar erro

	debug("BOOT salvo");
	return 1;
}

/**
 * @fn int save_so()
 * @brief Função responsável por salvar o sistema operacional no disco.
 * @return Retorna o tamanho do SO em setores gravado no disco, caso algum erro ocorra encerra o programa com uma mensagem de erro.
 */
short int save_so() {
	FILE *hpsys; /* Variável que será utilizada para a abertura do arquivo do HPSYS. */
	char *buffer; /* Variável que será utilizada para transferência do arquivo do HPSYS para o seu destino no disco */
	char info_hpsys_str[100]; /* Variável que armazena a mensagem de debug que contém o tamanho do HPSYS */
	struct stat info_hpsys; /* Variável utilizada para armazenar o estado do arquivo do HPSYS. */
	int tam_so_gravado; /* Em bytes */
	
	/* abertura do hpsys */
	hpsys = fopen(HPSYS_PATH, "rb");
	if (!hpsys) {
		char error_msg[100]; /* Mensagem de erro */
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
	buffer = (char *) malloc( info_hpsys.st_size ); // TODO: Tratar erro
	fread(buffer, sizeof(char), info_hpsys.st_size, hpsys); // TODO: Tratar erro
	tam_so_gravado = fwrite(buffer, sizeof(char), info_hpsys.st_size, disk); // TODO: Tratar erro
	debug("HPSYS salvo no disco");
	fclose(hpsys);
	return ( (tam_so_gravado%SIZE_SEC) ? tam_so_gravado/SIZE_SEC + 1 : tam_so_gravado/SIZE_SEC );
}

/**
 * @fn int save_bitmap()
 * @brief Função responsável por salvar o mapa de bits no disco.
 * @param tam_hpsys Tamanho em setores do hpsys que foi gravado.
 * @return 1 Caso tenha sido bem sucedido a carga do mapa de bits para o disco.
 */
int save_bitmap(short int tam_hpsys) {
	int i, j = 0;
	char bitmap[SIZE_SEC];
	int setores_ocupados_inicialmente = 2 + tam_hpsys + 1 + 2; /* Boot + hpsys + bitmap + descritores do arquivos */
	for(i = 0 ; i < setores_ocupados_inicialmente ; i++) {
		if ( !(i%8) ) {
			j = 1;
		}
		bitmap[i/8] += j;
		j <<= 1;
	}
	//printf("hpsys: %d\nbitmap: %s\n", tam_hpsys, bitmap);
	fseek(disk, (setores_ocupados_inicialmente)*SIZE_SEC, SEEK_SET);
	fwrite(bitmap, sizeof(char), SIZE_SEC, disk);
	return 1;
}

/**
 * @fn int save_root()
 * @brief Função responsável por salvar o diretório raiz no disco.
 * @param tam_hpsys Tamanho em setores do hpsys que foi gravado.
 * @return 1 Caso tenha sido bem sucedido a criação da diretório raiz.
 */
int save_root(short int tam_hpsys) {
	return 1;
}

/**
 * @fn int format_disk()
 * @brief Função que formata o disco a ser utilizado.
 * @return 1 Caso a formatação tenha sido bem sucedida.
 */
int format_disk() {
	int i; /* Variável utilizada como contador para percorrer os setores do disco */
	char nulo=0; /* Variável utilizada como conteúdo para os setores do disco a serem preenchidos */
	short int tam_so; /* Tamanho em setores */
	char msg[100];

	if (FORMAT_TYPE == CREATING_DISK)
		debug("Criando disco");
	else if (FORMAT_TYPE == USING_DISK)
		debug("Usando disco");
	else if (FORMAT_TYPE == CREATING_SIZEDDISK)
		debug("Criando disco com -s");

	if ( (disk = fopen(DISK_NAME, "wb")) == NULL ) {
		debug("Erro na abertura do disco. Abortando");
		exit(EXIT_FAILURE);
	}
	
	/* Caso o disco tenha sido aberto com sucesso, preenche cada um dos seus setores com o valor 0. */
	for (i=0; i < DISK_SIZE; i++) {
		fwrite(&nulo, sizeof(char), 1, disk);
	}

	debug("Disco Formatado");
	tam_so = save_so();
	sprintf(msg, "Tamanho do so gravado = %d setores", tam_so);
	debug(msg);
	tam_so *= 1.5;
	save_boot(tam_so);
	save_bitmap(tam_so);
	//save_root();
	return 1;
}

/**
 * @fn int file_exist(char *file_path)
 * @brief Verifica se um arquivo existe.
 * @param file_path Path do arquivo a ser testado
 * @return 1 Arquivo existe
 * @return 0 Arquivo não existe
 */
int file_exist(char *file_path) {
	FILE *fp;
	if ( (fp = fopen(file_path, "r")) != NULL )
		return 1;

	return 0;
}


/**
 * @fn int file_exist(char *file_path)
 * @brief Imprime o texto de help
 * 
 * Pode-se usar
 * ./hformat disco (disco nao existe)
 * ./hformat disco (disco ja existe)
 * ./hformat -s 5000 disco (disco nao existe)
 *
 * */
void hformat_help() {
	printf("\nHFORMAT - Ajuda\n\n");
	printf("./hformat disco -- se disco nao existe, cria disco com tamanho minimo e formata\n");
	printf("./hformat disco -- se existe, formata disco\n");
	printf("./hformat -s tam disco -- cria disco com tamanho tam(em Kb) e formata. \n\n"); //TODO: alterar pra usuário entrar com o numero de setores
	printf("./hformat -h|--help -- Mostra esta ajuda. \n\n");
	exit(EXIT_FAILURE);
}

/**
 * @fn void filter_argv(int argc, char **argv)
 * @brief TODO: Coloca na conta do Elvio a documentação
 * @param argc TODO
 * @param argv TODO
 */
void filter_argv(int argc, char **argv) {
	struct stat disco_info;
	float size_from_argv;
	char str_erro[100];

	if (argc != 2 && argc != 4) {
		hformat_help();
	} 

	if (argc == 2) {
		if ( !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
			hformat_help();
		} 
		// disco existe
		else if (file_exist(argv[1])) {
			stat(argv[1], &disco_info);
			if (disco_info.st_size >= MIN_DISK_SIZE && disco_info.st_size <= MAX_DISK_SIZE) {
				FORMAT_TYPE = USING_DISK;
				DISK_SIZE = disco_info.st_size;
				strcpy(DISK_NAME, argv[1]);
			} else {
				sprintf(str_erro, "Tamanho especificado( %f Kb ) invalido", (float)disco_info.st_size);
				print_error("0x0007", str_erro, 1);
			}
		}
		// disco nao existe && sem determinar tamanho
		else {
			if (strlen(argv[1]) > 7) { // TODO: q q é isso????
				FORMAT_TYPE = CREATING_DISK;
				DISK_SIZE = MAX_DISK_SIZE; 
				strcpy(DISK_NAME, argv[1]);
			} else {
				print_error("0x0009", "Nome de arquivo invalido", 1);
			}
		}
	}
	else if (argc == 4) {
		size_from_argv = atof(argv[2]);
		size_from_argv /= 1024; // TODO: numero do nada??? tem q documentar quando tem valores fixos voando por ai
		if ( !strcmp(argv[1], "-s") ) {
			if (size_from_argv >= MIN_DISK_SIZE/1024 && size_from_argv <= MAX_DISK_SIZE/1024) {
				FORMAT_TYPE = CREATING_SIZEDDISK;
				DISK_SIZE = size_from_argv; 
				strcpy(DISK_NAME, argv[3]);
			} else {
				sprintf(str_erro, "Tamanho especificado( %f Kb ) invalido", size_from_argv);
				print_error("0x0007", str_erro, 1);
			}
		} else {
			print_error("0x0007", "Opcao desconhecida", 1);
		} 
	}
}

/**
 * @fn int main(int argc, char *argv[])
 * @brief Função principal do hformat.c, responsável por chamar as subrotinas e verificar se os parâmetros foram passados corretamente.
 * @param argc Indica o número de parâmetros passados pela linha de comando.
 * @param argv String que representa os parâmetros passados na linha de comando.
 * @return 0 Se a operação de formatação do disco foi bem sucedida.
 */
int main(int argc, char *argv[]) {
	debug("Iniciando HFORMAT");

	/* verifica o que foi passado para linha de comando */
	filter_argv(argc, argv);

	format_disk();
	fclose(disk);
	return 0;
}
