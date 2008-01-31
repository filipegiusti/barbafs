#include <stdio.h>
#include <stdlib.h>
#include <check.h>

/*void setup (void) {
	printf("Inicializa testes...\n");
}

void teardown (void) {
	printf("Finaliza testes...\n");
}*/

START_TEST (existing_file) {
/*	fail_unless (fat(5) == 120,
		"Fatorial de 5 errado.");
	fail_unless (fat(11) == 39916800, 
		"Fatorial de 11 errado.");*/
}
END_TEST

START_TEST (non_existing_file) {
/*	fail_unless (fat(1) == 1,
               "Base da recursão falhou. Fat(1)");*/
}
END_TEST

START_TEST (invalid_path) {
/*	fail_unless (fat(1) == 1,
               "Base da recursão falhou. Fat(1)");*/
}
END_TEST

START_TEST (without_space) {
/*	fail_unless (fat(0) == 0,
		"Falhou pra 0.");
	fail_unless (fat(-1) == 0,
		"Falhou pra negativo.");*/
}
END_TEST

Suite *filesystem_suite(void) {
	Suite *s = suite_create("Filesystem");
	/* bfs_create */
	TCase *tc_bfs_create = tcase_create("bfs_create()");
	//tcase_add_checked_fixture(tc_core, setup, teardown);
	tcase_add_test(tc_bfs_create, existing_file);
	tcase_add_test(tc_bfs_create, non_existing_file);
	tcase_add_test(tc_bfs_create, invalid_path);
	tcase_add_test(tc_bfs_create, without_space);
	suite_add_tcase(s, tc_bfs_create);
	return s;
}
