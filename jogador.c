#include <stdio.h>
#include "jogador.h"

void jogar(char **matriz, char **matrizVisivel, int linhas, int colunas) {

    int linha;
    int coluna;

    printf("Digite a linha: ");
    scanf("%d", &linha);

    printf("Digite a coluna: ");
    scanf("%d", &coluna);

    while(linha < 0 || linha >= linhas || coluna < 0 || coluna >= colunas) {
        
        printf("Posição inválida, preste atenção!\n");
        
        printf("Digite a linha: ");
        scanf("%d", &linha);

        printf("Digite a coluna: ");
        scanf("%d", &coluna);
    }

    if (matriz[linha][coluna] == '*') {
        printf("BROOO VOCÊ ACERTOU UMA BOMBA! \n");
    }
    else {
        matrizVisivel[linha][coluna] = matriz[linha][coluna];
        printf("BOA!\n");
    }
}