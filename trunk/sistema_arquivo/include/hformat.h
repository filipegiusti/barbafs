#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "util.h"

#define BOOT1 0x33 /**< Define o conteúdo do penúltimo setor de boot. */
#define BOOT2 0xCC /**< Define o conteúdo do último setor de boot. */
#define BOOT_PATH "boot.bin" /**< Define a localização do arquivo que contém as informações do boot. */
#define HPSYS_PATH "hpsys" /**< Define a localização do HPSYS. */
#define SIZE_SEC 512 /**< Define o tamanho de segmento a ser utilizado no sistema de arquivos */
#define MIN_DISK_SIZE ( 512 * SIZE_SEC ) /**< Define o tamanho mínimo em bytes que um disco a ser formatado deve ter */
#define MAX_DISK_SIZE ( 4096 * SIZE_SEC ) /**< Define o tamanho máximo em bytes que um disco a ser formatado poderá ter */

struct stat info_disk; /**< Estrutura que armazena as informações de estado do arquivo que representa o disco */
char DISK_NAME[255]; /**< Variável que irá conter o nome do disco a ser utilizado */
FILE *disk; /**< Variável utilizada para referenciar o disco que estará sendo utilizado */

int save_boot(short int tam_hpsys);
short int save_so();
int save_bitmap(short int tam_hpsys);
int save_root(short int tam_hpsys);
int format_disk();
