#include <stdio.h>
#include <limits.h>

#include "jogador.h"
#include "jogo.h"

static int vizinhaValida(const Jogo *jogo, int linha, int coluna)
{
    return linha >= 0 && linha < jogo->linhas && coluna >= 0 && coluna < jogo->colunas;
}

static int analisarTabuleiro(Jogo *jogo)
{
    for (int linha = 0; linha < jogo->linhas; linha++) {
        for (int coluna = 0; coluna < jogo->colunas; coluna++) {
            char valor = jogo->visao[linha][coluna];
            if (valor < '1' || valor > '8') {
                continue;
            }

            int bombasMarcadas = 0;
            int desconhecidas = 0;
            for (int deltaLinha = -1; deltaLinha <= 1; deltaLinha++) {
                for (int deltaColuna = -1; deltaColuna <= 1; deltaColuna++) {
                    int vizinhaLinha = linha + deltaLinha;
                    int vizinhaColuna = coluna + deltaColuna;
                    if (!vizinhaValida(jogo, vizinhaLinha, vizinhaColuna)) {
                        continue;
                    }
                    if (jogo->visao[vizinhaLinha][vizinhaColuna] == 'F') {
                        bombasMarcadas++;
                    } else if (jogo->visao[vizinhaLinha][vizinhaColuna] == '#') {
                        desconhecidas++;
                    }
                }
            }

            if (desconhecidas == 0) {
                continue;
            }
            if (bombasMarcadas == valor - '0') {
                for (int deltaLinha = -1; deltaLinha <= 1; deltaLinha++) {
                    for (int deltaColuna = -1; deltaColuna <= 1; deltaColuna++) {
                        int vizinhaLinha = linha + deltaLinha;
                        int vizinhaColuna = coluna + deltaColuna;
                        if (vizinhaValida(jogo, vizinhaLinha, vizinhaColuna) &&
                            jogo->visao[vizinhaLinha][vizinhaColuna] == '#') {
                            revelarCelula(jogo, vizinhaLinha, vizinhaColuna);
                            return 1;
                        }
                    }
                }
            }
            if (bombasMarcadas + desconhecidas == valor - '0') {
                for (int deltaLinha = -1; deltaLinha <= 1; deltaLinha++) {
                    for (int deltaColuna = -1; deltaColuna <= 1; deltaColuna++) {
                        int vizinhaLinha = linha + deltaLinha;
                        int vizinhaColuna = coluna + deltaColuna;
                        if (vizinhaValida(jogo, vizinhaLinha, vizinhaColuna) &&
                            jogo->visao[vizinhaLinha][vizinhaColuna] == '#') {
                            if (alternarMarcacao(jogo, vizinhaLinha, vizinhaColuna)) {
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

static int escolherMenorRisco(Jogo *jogo, int *melhorLinha, int *melhorColuna)
{
    double menorRisco = (double) INT_MAX;
    int encontrou = 0;

    for (int linha = 0; linha < jogo->linhas; linha++) {
        for (int coluna = 0; coluna < jogo->colunas; coluna++) {
            if (jogo->visao[linha][coluna] != '#') {
                continue;
            }
            double risco = 0;
            int pistas = 0;
            for (int deltaLinha = -1; deltaLinha <= 1; deltaLinha++) {
                for (int deltaColuna = -1; deltaColuna <= 1; deltaColuna++) {
                    int vizinhaLinha = linha + deltaLinha;
                    int vizinhaColuna = coluna + deltaColuna;
                    if (!vizinhaValida(jogo, vizinhaLinha, vizinhaColuna)) {
                        continue;
                    }
                    char valor = jogo->visao[vizinhaLinha][vizinhaColuna];
                    if (valor >= '1' && valor <= '8') {
                        int desconhecidas = 0;
                        int marcadas = 0;
                        for (int dLinha = -1; dLinha <= 1; dLinha++) {
                            for (int dColuna = -1; dColuna <= 1; dColuna++) {
                                int l = vizinhaLinha + dLinha;
                                int c = vizinhaColuna + dColuna;
                                if (vizinhaValida(jogo, l, c)) {
                                    desconhecidas += jogo->visao[l][c] == '#';
                                    marcadas += jogo->visao[l][c] == 'F';
                                }
                            }
                        }
                        if (desconhecidas > 0) {
                            risco += (double) ((valor - '0') - marcadas) / desconhecidas;
                            pistas++;
                        }
                    }
                }
            }
            if (pistas == 0) {
                risco = 1000;
            } else {
                risco /= pistas;
            }
            if (risco < menorRisco) {
                menorRisco = risco;
                *melhorLinha = linha;
                *melhorColuna = coluna;
                encontrou = 1;
            }
        }
    }
    return encontrou;
}

void computadorJogar(int linhas, int colunas, int bombas)
{
    Jogo *jogo = criarJogo(linhas, colunas, bombas);
    int linha;
    int coluna;

    if (jogo == NULL) {
        printf("Nao foi possivel criar o jogo.\n");
        return;
    }
    revelarCelula(jogo, 0, 0);
    while (!jogo->terminou) {
        if (!analisarTabuleiro(jogo) && escolherMenorRisco(jogo, &linha, &coluna)) {
            revelarCelula(jogo, linha, coluna);
        }
    }
    mostrarJogo(jogo, 0);
    printf(jogoVenceu(jogo) ? "O computador venceu!" : "O computador encontrou uma bomba.");
    printf(" Tempo: %.0f segundos.\n", tempoDecorrido(jogo));
    destruirJogo(jogo);
}