#include <stdio.h>
#include "../includes/fatorial.h"

int main () {
        int num;
        printf("Digite o fatorial a ser calculado: ");
        scanf("%d", &num);
        printf("O fatorial de %d = %d\n", num, fat(num));
        return 0;
}

