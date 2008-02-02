/**
 * @file shell_func.h
 * @brief Fun��es do shell.
 * @author Elvio Viscosa, Filipe Giusti, Jeronimo Madruga, Leonardo Lobo, Mauro Kade.
 * @version 0.1 alpha
 * @date    01/02/2008
 */


void func_dir ( int argc,  char *argv[ ] );

void func_del ( int argc,  char *argv[ ] );

void func_rename ( int argc,  char * argv[ ] );

void func_copy ( int argc,  char * argv[ ] );

void func_list ( int argc,  char * argv[ ] );

void func_protect ( int argc,  char * argv[ ] );

void func_import ( int argc,  char * argv[ ] );

void func_export ( int argc,  char * argv[ ] );

void func_asm ( int argc,  char * argv[ ] );

void func_link ( int argc,  char * argv[ ] );

void func_format ( int argc,  char * argv[ ] );

void func_shutdown ( int argc,  char * argv[ ] );

void func_run ( int argc,  char * argv[ ] );

void func_exec ( int argc,  char * argv[ ] );

void func_search_str ( int argc, char *argv[ ] );     // Se der tempo, fa�o o c�digo desta funcao ( procura uma ocorrencia de uma string dentro de um arquivo )

void hshell_help (  );    // fun��o que exibe um shell de comandos
