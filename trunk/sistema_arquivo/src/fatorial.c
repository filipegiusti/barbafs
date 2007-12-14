#include <stdio.h>

int fat(int num) {
	if(num == 1)
		return 1;
	else
		return num * fat(num-1);
}
