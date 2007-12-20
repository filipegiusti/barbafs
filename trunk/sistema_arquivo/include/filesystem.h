/**
 * Estruturas de dados do sistema de arquivos. Contém as 4 struct's e um typedef que são usados pelo sistema de arquivos.
 */

/**
 * Uma posição dentro do disco o qual começa do setor 0.
 */
typedef char endereco_disco[2];

/**
 * Mapa de páginas de um arquivo que não é do tipo diretório, esta situado na área de dados do disco.
 */
struct mapa_paginas {
	char tam[2]; /**< Indica o tamanho total do arquivo. */
	endereco_disco end_disco[255]; /**< Endereço da área de dados do arquivo. */
};

enum tipo_arquivo {
	bin,
	txt,
	exe,
	hpx,
	obj,
	dir
};

struct descritor_arquivos {
	char nome[12];
	enum tipo_arquivo tipo;
	char protecao;
	endereco_disco mapa_pag;
};

struct mapa_arquivos {
	char quantidade[2];
	endereco_disco self;
	endereco_disco pai;
	endereco_disco arquivos[253];
};
