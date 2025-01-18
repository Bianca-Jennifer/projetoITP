#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include "mat.h"

// Função para criar a matriz
int** criar_matriz(int largura_total, int altura_total, char* codigodebarras, int espacamento_lateral, int quantidade_pixel) {
    // Aloca memória para a matriz
   int** matriz = (int**) calloc(altura_total, sizeof(int*));

    // Aloca memória para cada linha da matriz e inicializa com 0
    for (int i = 0; i < altura_total; i++) {
        matriz[i] = (int*) calloc(largura_total, sizeof(int)); 
    }

    //Altura da barra
    int linha_inicio = espacamento_lateral;
    int linha_fim = altura_total - espacamento_lateral;  

    // Preenche os valores do código de barras na matriz
    int pos = espacamento_lateral; 
    for (int i = 0; codigodebarras[i] != '\0'; i++) {
        int valor = codigodebarras[i] - '0'; 
        for (int j = 0; j < quantidade_pixel; j++) {
            for (int linha = linha_inicio; linha < linha_fim; linha++) {
                matriz[linha][pos + j] = valor;
            }
        }
        pos += quantidade_pixel;
    }

    return matriz;
}

// Função para liberar a matriz
void liberar_matriz(int** matriz, int altura_total) {
    for (int i = 0; i < altura_total; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

// Função para salvar arquivo .pbm
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