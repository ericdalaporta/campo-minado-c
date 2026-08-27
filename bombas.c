#include <stdlib.h>
#include "bombas.h"

int quantidadeBombasValida(int linhas, int colunas, int quantidade){
    return linhas > 0 && colunas > 0 && quantidade > 0 && quantidade < linhas * colunas;
}

void posicionarBombas(char **matriz, int linhas, int colunas, int quantidade)
{
    int linha;
    int coluna;
    int bombasColocadas = 0;

    while (bombasColocadas < quantidade)
    {
        linha = rand() % linhas;
        coluna = rand() % colunas;

        if (matriz[linha][coluna] != '*')
        {
            matriz[linha][coluna] = '*';
            bombasColocadas++;
        }
    }
}

void calcularNumeros(char **matriz, int linhas, int colunas)
{
    for (int linha = 0; linha < linhas; linha++) {
        for (int coluna = 0; coluna < colunas; coluna++) {
            if (matriz[linha][coluna] == '*') {
                continue;
            }

            int bombasVizinhas = 0;
            for (int deltaLinha = -1; deltaLinha <= 1; deltaLinha++) {
                for (int deltaColuna = -1; deltaColuna <= 1; deltaColuna++) {
                    int vizinhaLinha = linha + deltaLinha;
                    int vizinhaColuna = coluna + deltaColuna;

                    if (vizinhaLinha >= 0 && vizinhaLinha < linhas &&
                        vizinhaColuna >= 0 && vizinhaColuna < colunas &&
                        matriz[vizinhaLinha][vizinhaColuna] == '*') {
                        bombasVizinhas++;
                    }
                }
            }
            matriz[linha][coluna] = (char) ('0' + bombasVizinhas);
        }
    }
}