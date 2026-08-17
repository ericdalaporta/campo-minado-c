// gcc main.c matriz.c bombas.c jogador.c -o campo-minado.exe
// .\campo-minado.exe

#include <stdio.h>
#include "matriz.h"
#include "bombas.h"
#include "jogador.h"

int main()
{
    int linhas;
    int colunas;
    int quantidadeBombas;

    printf("--- CAMPO MINADO --- \n");

    printf("Digite o número de linhas: ");
    scanf("%d", &linhas);

    printf("Digite o número de colunas: ");
    scanf("%d", &colunas);

    printf("Digite a quantidade de bombas: ");
    scanf("%d", &quantidadeBombas);

    while (!quantidadeBombasValida(linhas, colunas, quantidadeBombas)){
        printf ("Quantidade de bombas inválida \n");

        printf("Digite a quantidade de bombas: ");
        scanf("%d", &quantidadeBombas);
    }

    char **matriz = criarMatriz(linhas, colunas);

    char **matrizVisivel = criarMatriz(linhas, colunas);

    posicionarBombas(matriz, linhas, colunas, quantidadeBombas);

    // mostra apenas o que o jogador pode ver
    mostrarMatriz(matrizVisivel, linhas, colunas);

    jogar(matriz, matrizVisivel, linhas, colunas);

    // mostra novamente depois da jogada
    mostrarMatriz(matrizVisivel, linhas, colunas);

    liberarMatriz(matriz, linhas);

    return 0;
}