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