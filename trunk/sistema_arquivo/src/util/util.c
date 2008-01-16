#include <stdio.h>
#include "../../include/util.h"

#ifdef DEBUG
	void debug(char *msg) {
		printf("[+] debug - %s\n", msg);
	}
#else
	void debug(char *msg){}
#endif
