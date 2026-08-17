#include <stdio.h>
#include <stdlib.h>

#include "matriz.h"

char **criarMatriz(int linhas, int colunas){

    // Aloca memória para os ponteiros das linhas
    char **matriz = malloc(linhas * sizeof(char*));

    if (matriz == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    // Aloca cada linha da matriz.
    for (int i = 0; i < linhas; i++){
        matriz[i] = malloc(colunas * sizeof(char));

        // se alguma linha der erro, libera as linhas já alocadas e encerra
        if (matriz[i] == NULL){
            printf("Erro ao alocar memória.\n");

            for (int j = 0; j < i; j++)
            {
                free(matriz[j]);
            }

            free(matriz);
            exit(1);

        }
        for (int j = 0; j < colunas; j++){
            matriz[i][j] = ' '; // inicializa a matriz com espaços em branco
        }
    }
    return matriz;
}

//essa função libera a memória alocada pra matriz depois de usá-la normalmente
void liberarMatriz(char **matriz, int linhas){
    for (int i = 0; i < linhas; i++){
        free(matriz[i]);
    }
    free(matriz);
}

void mostrarMatriz(char **matriz, int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            printf("[%c]", matriz[i][j]);
        }

        printf("\n");
    }
}