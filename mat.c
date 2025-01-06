#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include "mat.h"

int** criar_matriz(int largura_total, int altura_total, char* codigodebarras, int espacamento_lateral, int quantidade_pixel) {
    // Aloca memória para a matriz
   int** matriz = (int**) calloc(altura_total, sizeof(int*));

    // Aloca memória para cada linha da matriz e inicializa com 0
    for (int i = 0; i < altura_total; i++) {
        matriz[i] = (int*) calloc(largura_total, sizeof(int));  // Cada linha é um vetor de inteiros
    }

    //Altura da barra
    int linha_inicio = espacamento_lateral;
    int linha_fim = altura_total - espacamento_lateral;  

    // Preenche os valores do código de barras na matriz
    int pos = espacamento_lateral; // Começa após o espaçamento lateral
    for (int i = 0; codigodebarras[i] != '\0'; i++) {
        int valor = codigodebarras[i] - '0'; // Converte '1' ou '0' para inteiro
        for (int j = 0; j < quantidade_pixel; j++) {
            for (int linha = linha_inicio; linha < linha_fim; linha++) {
                matriz[linha][pos + j] = valor;
            }
        }
        pos += quantidade_pixel; // Avança para a próxima área
    }

    return matriz;
}