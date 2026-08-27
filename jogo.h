#ifndef JOGO_H
#define JOGO_H

#include <time.h>

typedef struct {
    int linhas;
    int colunas;
    int bombas;
    int reveladas;
    int marcadas;
    int terminou;
    int venceu;
    int primeiraJogada;
    char **tabuleiro;
    char **visao;
    time_t inicio;
} Jogo;

Jogo *criarJogo(int linhas, int colunas, int bombas);
void destruirJogo(Jogo *jogo);
void mostrarJogo(const Jogo *jogo, int revelarTudo);
int revelarCelula(Jogo *jogo, int linha, int coluna);
int alternarMarcacao(Jogo *jogo, int linha, int coluna);
int jogoVenceu(const Jogo *jogo);
double tempoDecorrido(const Jogo *jogo);

#endif