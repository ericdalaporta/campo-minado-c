#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bombas.h"
#include "jogador.h"
#include "util.h"

int main()
{
    int opcao;

    srand((unsigned int) time(NULL));

    do {
        printf("\n=== CAMPO MINADO ===\n");
        printf("1 - Jogar\n");
        printf("2 - Computador jogar\n");
        printf("0 - Sair\n");
        opcao = lerInteiro("Escolha: ");

        if (opcao == 1 || opcao == 2) {
            int linhas = lerInteiro("Numero de linhas: ");
            int colunas = lerInteiro("Numero de colunas: ");
            int bombas = lerInteiro("Quantidade de bombas: ");

            while (!quantidadeBombasValida(linhas, colunas, bombas)) {
                printf("Configuracao invalida. Use dimensoes positivas e menos bombas que celulas.\n");
                bombas = lerInteiro("Quantidade de bombas: ");
            }

            if (opcao == 1) {
                jogarPartida(linhas, colunas, bombas);
            } else {
                computadorJogar(linhas, colunas, bombas);
            }
        } else if (opcao != 0) {
            printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    printf("Ate a proxima partida!\n");
    return 0;
}
