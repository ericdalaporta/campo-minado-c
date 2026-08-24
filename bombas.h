#ifndef BOMBAS_H
#define BOMBAS_H

int quantidadeBombasValida(int linhas, int colunas, int quantidade);

void posicionarBombas(char **matriz, int linhas, int colunas, int quantidade);

int contarBombasAoRedor(char **matriz, int linhas, int colunas, int linha, int coluna);

#endif