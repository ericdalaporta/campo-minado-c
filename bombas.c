#include <stdlib.h>
#include "bombas.h"

int quantidadeBombasValida(int linhas, int colunas, int quantidade){
    return quantidade > 0 && quantidade <= linhas * colunas;
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
   

int contarBombasAoRedor(char **matriz, int linhas, int colunas, int linha, int coluna)
{
    int quantidadeBombas = 0;

    for (int i = linha - 1; i <= linha + 1; i++) // percorre todas as casas vizinhas da posicao informada
    {
        for (int j = coluna - 1; j <= coluna + 1; j++)
        {
            if (i < 0 || i >= linhas || j < 0 || j >= colunas) // garantir que não vai ler posições fora da matriz
            {
                continue;
            }

            if (i == linha && j == coluna) // não contar a própria
            {
                continue;
            }

            if (matriz[i][j] == '*')
            {
                quantidadeBombas++;
            }
        }
    }

    return quantidadeBombas;
}

