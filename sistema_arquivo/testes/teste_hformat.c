#include <stdio.h>
#include <stdlib.h>
#include <check.h>

FILE *ptr_arquivo;

void construtor(void) {
	ptr_arquivo = fopen("teste.txt","w+");
}

void destrutor(void) {
	fclose(ptr_arquivo);
	remove("teste.txt");
	remove("abc");
}

/*START_TEST (teste_abre_arquivo_perguntando) {
	fail_unless (abre_arquivo("teste.txt", 0) == ,
		"Fatorial de 5 errado.");
	fail_unless (fat(11) == 39916800, 
		"Fatorial de 11 errado.");
}
END_TEST*/

START_TEST (teste_abre_arquivo_forcado) {
/*	fail_unless (abre_arquivo("teste.txt", 1) != 0 ,
               "Não conseguiu escrever no arquivo existente forçando.");*/
}
END_TEST

START_TEST (teste_abre_arquivo_inexistente) {
/*	fail_unless (abre_arquivo("abc", 1) != 0 ,
               "Não conseguiu escrever no arquivo inexistente forçando.");*/
}
END_TEST

Suite *hformat_suite (void) {
	Suite *s = suite_create("HFormat");
	/* Core test case */
	TCase *ct_abre_arquivo = tcase_create("abre_arquivo");
	tcase_add_checked_fixture(ct_abre_arquivo, construtor, destrutor);
//	tcase_add_test(ct_abre_arquivo, teste_abre_arquivo_perguntando);
	tcase_add_test(ct_abre_arquivo, teste_abre_arquivo_forcado);
	tcase_add_test(ct_abre_arquivo, teste_abre_arquivo_inexistente);
	suite_add_tcase(s, ct_abre_arquivo);
	return s;
}
