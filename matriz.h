#ifndef MATRIZ_H
#define MATRIZ_H

char **criarMatriz(int linhas, int colunas);

void liberarMatriz(char **matriz, int linhas);

void mostrarMatriz(char **matriz, int linhas, int colunas);

void preencherMatriz(char **matriz, int linhas, int colunas, char valor);

#endif