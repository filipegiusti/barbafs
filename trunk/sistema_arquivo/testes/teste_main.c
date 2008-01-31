#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "teste_filesystem.c"
#include "teste_hformat.c"
#include "teste_fatorial.c"

int main (void) {
	int number_failed;
	Suite *fatorial = fatorial_suite();
	Suite *filesystem = filesystem_suite();
	Suite *hformat = hformat_suite();
	//Suite *filesystem = filesystem_suite();
	SRunner *sr = srunner_create(filesystem);
	srunner_add_suite(sr, hformat);
	srunner_add_suite(sr, fatorial);
	srunner_run_all (sr, CK_NORMAL);
	number_failed = srunner_ntests_failed (sr);
	srunner_free (sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

