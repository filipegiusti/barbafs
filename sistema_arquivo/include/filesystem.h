/**
 * @file filesystem.h
 * @brief Chamadas do sistema de arquivos.
 * @author Elvio Viscosa, Filipe Giusti, Jerônimo Madruga, Leonardo Lobo, Mauro Kade.
 * @version 1.0
 * @date    25/01/2007
 */

#define MAX_SIZE_NOME 11 /**< Tamanho m�ximo pra nomes de arquivo ou diret�rio. */

/**
 * @enum modo_abertura_arquivo
 * @brief Modos de abertura possiveis para um arquivo.
 */
enum modo_abertura_arquivo {
	 READ,
	 WRITE,
	 READ_WRITE
};

/**
 * Identificador de um arquivo aberto.
 */
typedef unsigned int arquivo;

/**
 * Identificador de um diretorio aberto.
 */
typedef unsigned int diretorio;

/**
 * @enum tipo_arquivo
 * @brief Indicador do tipo de arquivo.
 */
enum tipo_arquivo {
	bin, /**< Arquivo do tipo binário. */
	txt, /**< Arquivo do tipo texto. */
	exe, /**< Arquivo do tipo executável do Host. */
	hpx, /**< Arquivo do tipo executável da máquina virtual */
	obj, /**< Arquivo do tipo objeto. */
	dir /**< Arquivo representa um diretório. */
};

int bfs_create(char *caminho);
int bfs_delete(char *caminho);
arquivo bfs_open(char *caminho, enum modo_abertura_arquivo modo);
int bfs_close(arquivo id);
int bfs_read(arquivo id, char *buffer, int nbytes);
int bfs_write(arquivo id, char *buffer, int nbytes);
//TODO: int bfs_location_seek(arquivo id, int deslocamento, );
int bfs_get_nome(arquivo id, char *buffer_nome);
char bfs_get_prot(arquivo id);
enum tipo_arquivo bfs_get_tipo(arquivo id);
int bfs_set_nome(arquivo id, char *nome);
int bfs_set_prot(arquivo id, char prot);
int bfs_set_tipo(arquivo id, enum tipo_arquivo);
int bfs_create_dir(char *caminho);
int bfs_delete_dir(char *caminho);
int bfs_set_cwd(char *caminho);
char *bfs_get_cwd();
diretorio bfs_open_dir(char *caminho);
int bfs_close_dir(diretorio dir);
int bfs_read_dir(diretorio dir, char *buffer_nome);
int bfs_rewind_dir(diretorio dir);
