#include <stdio.h>

#include "jogador.h"
#include "jogo.h"
#include "util.h"

void jogarPartida(int linhas, int colunas, int bombas)
{
    Jogo *jogo = criarJogo(linhas, colunas, bombas);
    int linha;
    int coluna;

    if (jogo == NULL) {
        printf("Nao foi possivel criar o jogo.\n");
        return;
    }

    printf("\nEscolha 1 para abrir uma casa, 2 para marcar e 3 para desmarcar uma bandeira.\n\n");

    while (!jogo->terminou) {
        int resultado;
        int acao;

        mostrarJogo(jogo, 0);
        printf("\n");
        acao = lerInteiro("Acao (1 abrir, 2 marcar, 3 desmarcar): ");
        linha = lerInteiro("Linha: ");
        coluna = lerInteiro("Coluna: ");

        if (acao != 1 && acao != 2 && acao != 3) {
            printf("\nAcao invalida. Use 1, 2 ou 3.\n\n");
            continue;
        }

        linha--;
        coluna--;

        if (acao == 2) {
            if (alternarMarcacao(jogo, linha, coluna)) {
                printf("\nBandeira atualizada.\n\n");
            } else {
                printf("\nNao foi possivel marcar essa posicao.\n\n");
            }
        } else if (acao == 3) {
            if (desmarcarMarcacao(jogo, linha, coluna)) {
                printf("\nBandeira removida.\n\n");
            } else {
                printf("\nNao ha bandeira nessa posicao.\n\n");
            }
        } else {
            resultado = revelarCelula(jogo, linha, coluna);
            if (resultado == -1) {
                // Acertou uma bomba: o jogo termina na mesma hora.
                printf("\nVoce encontrou uma bomba!\n\n");
            } else if (resultado == 0) {
                printf("\nPosicao invalida ou ja revelada.\n\n");
            } else {
                char valor = jogo->visao[linha][coluna];
                printf("\nBombas ao redor: %c\n", valor);
                if (valor == '0') {
                    printf("Area limpa.\n");
                }
                printf("\n");
            }
        }
    }

    // aqui o tabuleiro final aparece logo depois da ultima jogada.
    mostrarJogo(jogo, 0);
    printf("\n%s", jogoVenceu(jogo) ? "Voce venceu!" : "Fim de jogo.");
    printf(" Tempo: %.0f segundos.\n\n", tempoDecorrido(jogo));
    destruirJogo(jogo);
}