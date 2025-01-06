#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include "pbm.h"

void salvar_pbm(const char* nome_arquivo, int** matriz, int largura_total, int altura_total) {
    FILE* arquivo = fopen(nome_arquivo, "w");
    if (!arquivo) {
        perror("Erro ao criar o arquivo PBM");
        exit(EXIT_FAILURE);
    }

    // Escreve o cabeçalho PBM
    fprintf(arquivo, "P1\n");
    fprintf(arquivo, "%d %d\n", largura_total, altura_total);

    // Escreve os valores da matriz
    for (int i = 0; i < altura_total; i++) {
        for (int j = 0; j < largura_total; j++) {
            fprintf(arquivo, "%d ", matriz[i][j]);
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
}