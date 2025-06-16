#include <stdio.h>
#include <stdlib.h>

#define TAM 8

// Definições para facilitar leitura do código
#define VAZIO '.'

// Funções para checar a cor da peça
int ehBranca(char p) { return p >= 'A' && p <= 'Z'; }
int ehPreta(char p)  { return p >= 'a' && p <= 'z'; }
int ehVazia(char p)  { return p == VAZIO; }

char tabuleiro[TAM][TAM];

// Inicializa o tabuleiro com as peças padrão
void inicializarTabuleiro() {
    // Peças pretas
    tabuleiro[0][0] = 't'; tabuleiro[0][1] = 'c'; tabuleiro[0][2] = 'b'; tabuleiro[0][3] = 'd';
    tabuleiro[0][4] = 'r'; tabuleiro[0][5] = 'b'; tabuleiro[0][6] = 'c'; tabuleiro[0][7] = 't';
    for (int i = 0; i < TAM; i++)
        tabuleiro[1][i] = 'p';

    // Peças brancas
    tabuleiro[7][0] = 'T'; tabuleiro[7][1] = 'C'; tabuleiro[7][2] = 'B'; tabuleiro[7][3] = 'D';
    tabuleiro[7][4] = 'R'; tabuleiro[7][5] = 'B'; tabuleiro[7][6] = 'C'; tabuleiro[7][7] = 'T';
    for (int i = 0; i < TAM; i++)
        tabuleiro[6][i] = 'P';

    // Espaços vazios
    for (int i = 2; i < 6; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = VAZIO;
}

// Mostra o tabuleiro no terminal
void exibirTabuleiro() {
    printf("\n  A B C D E F G H\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", 8 - i);
        for (int j = 0; j < TAM; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Converte letra da coluna para índice
int colunaParaIndice(char c) {
    if (c >= 'A' && c <= 'H') return c - 'A';
    if (c >= 'a' && c <= 'h') return c - 'a';
    return -1;
}

// Faz a movimentação da peça
void moverPeca(int lOrig, int cOrig, int lDest, int cDest) {
    tabuleiro[lDest][cDest] = tabuleiro[lOrig][cOrig];
    tabuleiro[lOrig][cOrig] = VAZIO;
}

// Limpa o buffer do teclado para evitar falha no scanf
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Limpa a tela (compatível com Windows e Unix)
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Função principal
int main() {
    inicializarTabuleiro();
    int turno = 0; // 0 = brancas, 1 = pretas

    while (1) {
        limparTela();
        exibirTabuleiro();
        printf("\nTurno das %s\n", turno == 0 ? "brancas" : "pretas");
        printf("Digite 0 para sair.\n");

        char colOrig, colDest;
        int linOrig, linDest;

        // Entrada da origem
        printf("Digite a coordenada de origem (ex: e2): ");
        int n = scanf(" %c%d", &colOrig, &linOrig);
        if (n != 2) {
            printf("Entrada inválida! Tente novamente.\n");
            limparBuffer();
            continue;
        }
        if (colOrig == '0') break;

        // Entrada do destino
        printf("Digite a coordenada de destino (ex: e4): ");
        n = scanf(" %c%d", &colDest, &linDest);
        if (n != 2) {
            printf("Entrada inválida! Tente novamente.\n");
            limparBuffer();
            continue;
        }
        if (colDest == '0') break;

        // Converter para índices de matriz
        int cOrig = colunaParaIndice(colOrig);
        int lOrig = 8 - linOrig;
        int cDest = colunaParaIndice(colDest);
        int lDest = 8 - linDest;

        // Validação de índices
        if (cOrig < 0 || cOrig >= TAM || cDest < 0 || cDest >= TAM ||
            lOrig < 0 || lOrig >= TAM || lDest < 0 || lDest >= TAM) {
            printf("Coordenadas inválidas! Tente novamente.\n");
            limparBuffer();
            continue;
        }

        char peca = tabuleiro[lOrig][cOrig];
        char destino = tabuleiro[lDest][cDest];

        // Verifica se existe peça na origem
        if (ehVazia(peca)) {
            printf("Não há peça na origem!\n");
            limparBuffer();
            continue;
        }

        // Verifica se o jogador está tentando mover a peça do adversário
        if ((turno == 0 && !ehBranca(peca)) ||
            (turno == 1 && !ehPreta(peca))) {
            printf("Essa peça não é sua!\n");
            limparBuffer();
            continue;
        }

        // Não permite capturar peça da própria cor
        if ((turno == 0 && ehBranca(destino)) ||
            (turno == 1 && ehPreta(destino))) {
            printf("Você não pode capturar sua própria peça!\n");
            limparBuffer();
            continue;
        }

        // Aqui seria o local para adicionar validação de movimento da peça

        moverPeca(lOrig, cOrig, lDest, cDest);
        turno = 1 - turno; // Alterna turno
    }

    printf("Jogo encerrado. Obrigado por jogar!\n");
    return 0;
}
