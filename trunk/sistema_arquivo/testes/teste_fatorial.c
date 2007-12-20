#include <stdio.h>
#include <stdlib.h>
#include "fatorial.h"
#include <check.h>

void setup (void) {
	printf("Inicializa testes...\n");
}

void teardown (void) {
	printf("Finaliza testes...\n");
}

START_TEST (test_some_fats) {
	fail_unless (fat(5) == 120,
		"Fatorial de 5 errado.");
	fail_unless (fat(11) == 39916800, 
		"Fatorial de 11 errado.");
}
END_TEST

START_TEST (test_recursion_base) {
	fail_unless (fat(1) == 1,
               "Base da recursão falhou. Fat(1)");
}
END_TEST

START_TEST (test_negative_numbers) {
	fail_unless (fat(0) == 0,
		"Falhou pra 0.");
	fail_unless (fat(-1) == 0,
		"Falhou pra negativo.");
}
END_TEST

Suite *fatorial_suite (void) {
	Suite *s = suite_create("Fatorial");
	/* Core test case */
	TCase *tc_core = tcase_create("Core");
	tcase_add_checked_fixture(tc_core, setup, teardown);
	tcase_add_test(tc_core, test_some_fats);
	suite_add_tcase(s, tc_core);
	/* Limits test case */
	TCase *tc_limits = tcase_create ("Limits");
	tcase_add_test (tc_limits, test_recursion_base);
	tcase_add_test (tc_limits, test_negative_numbers);
	suite_add_tcase (s, tc_limits);
	return s;
}

int main (void) {
	int number_failed;
	Suite *s = fatorial_suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all (sr, CK_NORMAL);
	number_failed = srunner_ntests_failed (sr);
	srunner_free (sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

