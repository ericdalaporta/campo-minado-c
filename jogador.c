#include <stdio.h>
#include "jogador.h"
#include "bombas.h"

int jogar(char **matriz, char **matrizVisivel, int linhas, int colunas) {

    int linha;
    int coluna;

    printf("Digite a linha (1 a %d): ", linhas);
    scanf("%d", &linha);

    printf("Digite a coluna (1 a %d): ", colunas);
    scanf("%d", &coluna);

    while(linha < 1 || linha > linhas || coluna < 1 || coluna > colunas) {
        
        printf("Posicao invalida, use valores de 1 ate %d e 1 ate %d.\n", linhas, colunas);
        
        printf("Digite a linha (1 a %d): ", linhas);
        scanf("%d", &linha);

        printf("Digite a coluna (1 a %d): ", colunas);
        scanf("%d", &coluna);
    }

    linha--;
    coluna--;

    if (matriz[linha][coluna] == '*') {
        matrizVisivel[linha][coluna] = 'X';
        printf("Voce acertou uma bomba!\n");
        return 1;
    }
    else {
        int bombasAoRedor = contarBombasAoRedor(matriz, linhas, colunas, linha, coluna);

        matrizVisivel[linha][coluna] = (char)('0' + bombasAoRedor);
        printf("Boa jogada!\n");
        return 0;
    }
}