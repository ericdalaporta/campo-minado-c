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

    // Mensagem curta para explicar o controle sem entulhar a tela.
    printf("\nDigite apenas a linha e a coluna. Use linha negativa para marcar ou desmarcar uma bandeira.\n\n");

    while (!jogo->terminou) {
        int resultado;
        int modoBandeira = 0;

        mostrarJogo(jogo, 0);
        printf("\n");
        linha = lerInteiro("Linha: ");
        coluna = lerInteiro("Coluna: ");

        if (linha < 0) {
            // Convenção simples para não precisar de um menu extra de ação.
            modoBandeira = 1;
            linha = -linha;
        }

        linha--;
        coluna--;

        if (modoBandeira) {
            if (alternarMarcacao(jogo, linha, coluna)) {
                printf("\nBandeira atualizada.\n\n");
            } else {
                printf("\nNao foi possivel marcar essa posicao.\n\n");
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

    // Aqui o tabuleiro final aparece logo depois da ultima jogada.
    mostrarJogo(jogo, 0);
    printf("\n%s", jogoVenceu(jogo) ? "Voce venceu!" : "Fim de jogo.");
    printf(" Tempo: %.0f segundos.\n\n", tempoDecorrido(jogo));
    destruirJogo(jogo);
}