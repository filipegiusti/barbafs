/**
 * @file filesystem.h
 * @brief Estruturas de dados do sistema de arquivos. Contém as 4 struct's e um typedef que são usados pelo sistema de arquivos.
 * @author Elvio Viscosa, Filipe Giusti, Jerônimo Madruga, Leonardo Lobo, Mauro Kade.
 *  @version 1.0
 *  @date    16/01/2007
 */

/**
 * Uma posição dentro do disco o qual começa do setor 0.
 */
typedef char endereco_disco[2];

/**
 * @struct mapa_paginas
 * @brief Mapa de páginas de um arquivo que não é do tipo diretório, esta situado na área de dados do disco.
 */
struct mapa_paginas {
	char tam[2]; /**< Indica o tamanho total do arquivo. */
	endereco_disco end_disco[255]; /**< Endereço da área de dados do arquivo. */
};

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

/**
 * @struct descritor_arquivos
 * @brief Estrutura que representa o descritor de um arquivo.
 */
struct descritor_arquivos {
	char nome[12]; /**< Indica o nome do arquivo descrito. */
	enum tipo_arquivo tipo; /**< Indica o tipo de arquivo em questão. */
	char protecao; /**< Atributo que indica o controle sobre eliminação ou gravação. */
	endereco_disco mapa_pag; /**< Mapa de páginas do arquivo em questão. */
};

/**
 * @struct mapa_arquivos
 * @brief Mapa de arquivos de um diretório.
 */
struct mapa_arquivos {
	char quantidade[2]; /**< Indica  a quantidade de arquivos  existentes em arquivos[] */
	endereco_disco self; /**< Aponta para o endereço atual do arquivo em questão. */
	endereco_disco pai; /**< Aponta para o endereço do pai do arquivo em questão. */
	endereco_disco arquivos[253]; /**< Endereço dos arquivos contidos no diretório. */
};