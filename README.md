# Campo Minado em C

O jogo usa duas matrizes alocadas dinamicamente: o tabuleiro real e a visao do jogador.
A primeira jogada e protegida contra bombas.

## Arquivos

- `main.c`: menu e configuracao da partida.
- `matriz.c/.h`: alocacao e operacoes basicas das matrizes.
- `bombas.c/.h`: bombas e contagem de vizinhos.
- `jogo.c/.h`: estado, regras, revelacao e tempo.
- `jogador.c/.h`: comandos do jogador.
- `computador.c`: deducao de bombas, casas seguras e escolha por menor risco.
- `util.c/.h`: leitura de inteiros.

## Compilacao direta

Linux:

```bash
gcc main.c matriz.c bombas.c jogo.c jogador.c computador.c util.c -o campo-minado
./campo-minado
```

Windows PowerShell:

```powershell
gcc main.c matriz.c bombas.c jogo.c jogador.c computador.c util.c -o campo-minado.exe
.\campo-minado.exe
```

Durante uma partida manual, digite apenas a linha e a coluna de cada jogada.
Use linha negativa para marcar ou desmarcar uma bandeira na mesma posicao.
