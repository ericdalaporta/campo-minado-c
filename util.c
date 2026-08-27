#include <stdio.h>
#include <stdlib.h>

#include "util.h"

int lerInteiro(const char *mensagem)
{
    char entrada[100];
    char *fim;
    long valor;

    while (1) {
        printf("%s", mensagem);
        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            return 0;
        }
        valor = strtol(entrada, &fim, 10);
        if (fim != entrada) {
            return (int) valor;
        }
        printf("Digite um numero valido.\n");
    }
}