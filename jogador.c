#include <stdio.h>

#include "jogador.h"
#include "jogo.h"

void jogarPartida(int linhas, int colunas, int bombas)
{
    Jogo *jogo = criarJogo(linhas, colunas, bombas);
    char comando;
    int linha;
    int coluna;

    if (jogo == NULL) {
        printf("Nao foi possivel criar o jogo.\n");
        return;
    }

    printf("Comandos: r linha coluna (revelar), m linha coluna (marcar), s (sair)\n");
    while (!jogo->terminou) {
        mostrarJogo(jogo, 0);
        printf("Acao: ");
        if (scanf(" %c", &comando) != 1) {
            break;
        }
        if (comando == 's') {
            break;
        }
        if (scanf("%d %d", &linha, &coluna) != 2) {
            printf("Use: r 2 3 ou m 2 3.\n");
            while (getchar() != '\n') { }
            continue;
        }
        linha--;
        coluna--;
        if (comando == 'r') {
            int resultado = revelarCelula(jogo, linha, coluna);
            if (resultado == -1) {
                printf("Voce encontrou uma bomba!\n");
            } else if (resultado == 0) {
                printf("Posicao invalida ou ja revelada.\n");
            }
        } else if (comando == 'm') {
            if (!alternarMarcacao(jogo, linha, coluna)) {
                printf("Nao foi possivel marcar essa posicao.\n");
            }
        }
    }

    if (jogo->terminou) {
        mostrarJogo(jogo, 0);
        printf(jogoVenceu(jogo) ? "Voce venceu!" : "Fim de jogo.");
        printf(" Tempo: %.0f segundos.\n", tempoDecorrido(jogo));
    }
    destruirJogo(jogo);
}