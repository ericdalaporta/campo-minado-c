// gcc main.c matriz.c bombas.c jogador.c -o campo-minado.exe
// .\campo-minado.exe

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matriz.h"
#include "bombas.h"
#include "jogador.h"

static void mostrarMenu(void)
{
    printf("\n======================================\n");
    printf("           CAMPO MINADO\n");
    printf("======================================\n");
    printf("1 - Jogar\n");
    printf("2 - Sair\n");
    printf("======================================\n");
}

static void lerInteiro(const char *mensagem, int *valor)
{
    printf("%s", mensagem);
    scanf("%d", valor);
}

int main()
{
    srand((unsigned)time(NULL));

    int opcao;
    int linhas;
    int colunas;
    int quantidadeBombas;

    mostrarMenu();
    lerInteiro("Escolha uma opcao: ", &opcao);

    if (opcao == 2)
    {
        printf("Saindo do jogo...\n");
        return 0;
    }

    if (opcao != 1)
    {
        printf("Opcao invalida. Reinicie e escolha 1 ou 2.\n");
        return 1;
    }

    printf("\nVamos configurar a partida.\n");
    lerInteiro("Digite o numero de linhas: ", &linhas);
    lerInteiro("Digite o numero de colunas: ", &colunas);
    lerInteiro("Digite a quantidade de bombas: ", &quantidadeBombas);

    while (!quantidadeBombasValida(linhas, colunas, quantidadeBombas))
    {
        printf("Quantidade de bombas invalida. Digite um valor entre 1 e %d.\n", linhas * colunas);
        lerInteiro("Digite a quantidade de bombas: ", &quantidadeBombas);
    }

    char **matriz = criarMatriz(linhas, colunas);
    char **matrizVisivel = criarMatriz(linhas, colunas);

    posicionarBombas(matriz, linhas, colunas, quantidadeBombas);

    int acertouBomba = 0;
    time_t inicioPartida = time(NULL);

    while (!acertouBomba)
    {
        printf("\nTabuleiro atual:\n");
        mostrarMatriz(matrizVisivel, linhas, colunas);

        acertouBomba = jogar(matriz, matrizVisivel, linhas, colunas);
    }

    time_t fimPartida = time(NULL);
    double tempoPartida = difftime(fimPartida, inicioPartida);

    printf("\nTabuleiro final:\n");
    mostrarMatriz(matrizVisivel, linhas, colunas);
    printf("Tempo da partida: %.0f segundos\n", tempoPartida);

    liberarMatriz(matriz, linhas);
    liberarMatriz(matrizVisivel, linhas);

    return 0;
}