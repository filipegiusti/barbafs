/**
 * @file filesystem_internal.h
 * @brief Funções auxiliares e estruturas de dados internas do sistema de arquivos.
 * @author Elvio Vicosa, Filipe Giusti, Jerônimo Madruga, Leonardo Lobo, Mauro Kade.
 */

#include "filesystem.h"

/**
 * Uma posição dentro do disco o qual começa do setor 0.
 */
typedef short int endereco_disco;

/**
 * @brief Descritor de um arquivo/diretório.
 */
struct descritor_arquivo {
	char nome[MAX_SIZE_NOME+1]; /**< Indica o nome do arquivo descrito. */
	char tipo; /**< Indica o tipo de arquivo em questão. */
	char protecao; /**< Atributo que indica o controle sobre eliminação ou gravação. */
	endereco_disco mapa_pag; /**< Mapa de páginas do arquivo em questão. */
};

/**
 * @brief Mapa de páginas de um arquivo que não é do tipo diretório, esta situado na área de dados do disco.
 */
struct mapa_paginas_arquivo {
	char tam[2]; /**< Indica o tamanho total do arquivo. */
	endereco_disco end_disco[255]; /**< Endereço da área de dados do arquivo. */
};

/**
 * @brief Mapa de arquivos de um diretório.
 */
struct mapa_paginas_diretorio {
	char quantidade[2]; /**< Indica  a quantidade de arquivos existentes em arquivos[] */
	endereco_disco self; /**< Aponta para o endereço atual do arquivo em questão. */
	endereco_disco pai; /**< Aponta para o endereço do pai do arquivo em questão. */
	endereco_disco arquivos[253]; /**< Endereço dos arquivos contidos no diretório. */
};

/**
 * @brief Descritor para arquivos abertos.
 */
struct arquivo_aberto {
	   arquivo id; /**< Identificador para o arquivo aberto. */
	   enum modo_abertura_arquivo modo; /**< Modo de abertura do arquivo.*/
	   char *caminho; /**< Caminho at� o arquivo. */
	   int location; /**< Indica qual o pr�ximo byte que ser� lido. */
	   struct descritor_arquivo *descritor; /**< C�pia na mem�ria do descrito do arquivo. */
	   struct mapa_paginas_arquivo *mapa_pag; /**< C�pia na mem�ria do mapa de p�ginas do arquivo. */
	   char alterado; /**< Indica se os dados ou informa��es do arquivo foram alterados. */
};

endereco_disco verifica_caminho(char *caminho);
