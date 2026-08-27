#include <stdio.h>
#include <stdlib.h>

#include "bombas.h"
#include "jogo.h"
#include "matriz.h"

static void protegerPrimeiraJogada(Jogo *jogo, int linha, int coluna)
{
    if (!jogo->primeiraJogada || jogo->tabuleiro[linha][coluna] != '*') {
        return;
    }

    for (int novaLinha = 0; novaLinha < jogo->linhas; novaLinha++) {
        for (int novaColuna = 0; novaColuna < jogo->colunas; novaColuna++) {
            if (jogo->tabuleiro[novaLinha][novaColuna] != '*' &&
                (novaLinha != linha || novaColuna != coluna)) {
                jogo->tabuleiro[novaLinha][novaColuna] = '*';
                jogo->tabuleiro[linha][coluna] = '0';
                calcularNumeros(jogo->tabuleiro, jogo->linhas, jogo->colunas);
                return;
            }
        }
    }
}

static int coordenadaValida(const Jogo *jogo, int linha, int coluna)
{
    return linha >= 0 && linha < jogo->linhas && coluna >= 0 && coluna < jogo->colunas;
}

static void revelarVizinhas(Jogo *jogo, int linha, int coluna)
{
    // Quando abre uma casa vazia, espalha a abertura para os vizinhos.
    for (int deltaLinha = -1; deltaLinha <= 1; deltaLinha++) {
        for (int deltaColuna = -1; deltaColuna <= 1; deltaColuna++) {
            revelarCelula(jogo, linha + deltaLinha, coluna + deltaColuna);
        }
    }
}

static char simboloVisivel(char valor, int revelarTudo)
{
    if (revelarTudo) {
        return valor;
    }
    if (valor == '#') {
        return '.';
    }
    if (valor == 'F') {
        return 'F';
    }
    if (valor == '0') {
        return ' ';
    }
    return valor;
}

static void imprimirSeparador(int colunas)
{
    printf("   +");
    for (int coluna = 0; coluna < colunas; coluna++) {
        printf("---+");
    }
    printf("\n");
}

Jogo *criarJogo(int linhas, int colunas, int bombas)
{
    Jogo *jogo = malloc(sizeof(Jogo));
    if (jogo == NULL) {
        return NULL;
    }

    jogo->linhas = linhas;
    jogo->colunas = colunas;
    jogo->bombas = bombas;
    jogo->reveladas = 0;
    jogo->marcadas = 0;
    jogo->terminou = 0;
    jogo->venceu = 0;
    jogo->primeiraJogada = 1;
    jogo->tabuleiro = criarMatriz(linhas, colunas);
    jogo->visao = criarMatriz(linhas, colunas);
    preencherMatriz(jogo->visao, linhas, colunas, '#');
    posicionarBombas(jogo->tabuleiro, linhas, colunas, bombas);
    calcularNumeros(jogo->tabuleiro, linhas, colunas);
    jogo->inicio = time(NULL);
    return jogo;
}

void destruirJogo(Jogo *jogo)
{
    if (jogo != NULL) {
        liberarMatriz(jogo->tabuleiro, jogo->linhas);
        liberarMatriz(jogo->visao, jogo->linhas);
        free(jogo);
    }
}

void mostrarJogo(const Jogo *jogo, int revelarTudo)
{
    // O tabuleiro usa uma grade simples para ficar mais legível no terminal.
    printf("\n     ");
    for (int coluna = 0; coluna < jogo->colunas; coluna++) {
        printf(" %2d ", coluna + 1);
    }
    printf("\n");

    imprimirSeparador(jogo->colunas);

    for (int linha = 0; linha < jogo->linhas; linha++) {
        printf("%2d |", linha + 1);
        for (int coluna = 0; coluna < jogo->colunas; coluna++) {
            char valor = revelarTudo ? jogo->tabuleiro[linha][coluna] : jogo->visao[linha][coluna];
            // Cada célula tem largura fixa para o cabeçalho não desalinha.
            printf(" %c |", simboloVisivel(valor, revelarTudo));
        }
        printf("\n");
        imprimirSeparador(jogo->colunas);
    }
}

int revelarCelula(Jogo *jogo, int linha, int coluna)
{
    if (jogo->terminou || !coordenadaValida(jogo, linha, coluna) || jogo->visao[linha][coluna] != '#') {
        return 0;
    }

    protegerPrimeiraJogada(jogo, linha, coluna);
    jogo->primeiraJogada = 0;

    if (jogo->tabuleiro[linha][coluna] == '*') {
        jogo->visao[linha][coluna] = 'X';
        jogo->terminou = 1;
        jogo->venceu = 0;
        return -1;
    }

    jogo->visao[linha][coluna] = jogo->tabuleiro[linha][coluna];
    jogo->reveladas++;

    if (jogo->tabuleiro[linha][coluna] == '0') {
        revelarVizinhas(jogo, linha, coluna);
    }

    if (jogo->reveladas == jogo->linhas * jogo->colunas - jogo->bombas) {
        jogo->terminou = 1;
        jogo->venceu = 1;
        return 2;
    }
    return 1;
}

int alternarMarcacao(Jogo *jogo, int linha, int coluna)
{
    if (jogo->terminou || !coordenadaValida(jogo, linha, coluna)) {
        return 0;
    }
    if (jogo->visao[linha][coluna] == '#') {
        if (jogo->marcadas == jogo->bombas) {
            return 0;
        }
        jogo->visao[linha][coluna] = 'F';
        jogo->marcadas++;
        return 1;
    }
    if (jogo->visao[linha][coluna] == 'F') {
        jogo->visao[linha][coluna] = '#';
        jogo->marcadas--;
        return 1;
    }
    return 0;
}

int jogoVenceu(const Jogo *jogo)
{
    return jogo->venceu;
}

double tempoDecorrido(const Jogo *jogo)
{
    return difftime(time(NULL), jogo->inicio);
}