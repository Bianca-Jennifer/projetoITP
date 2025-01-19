#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include "conversor.h"

void conversor(const char *esquerda, const char *direita, char *lcode, char *rcode) {
    // Mapeamento dos dígitos para suas representações
    const char *tablcode[10] = {
        "0001101", // 0
        "0011001", // 1
        "0010011", // 2
        "0111101", // 3
        "0100011", // 4
        "0110001", // 5
        "0101111", // 6
        "0111011", // 7
        "0110111", // 8
        "0001011"  // 9
    };
        const char *tabrcode[10] = {
        "1110010", // 0
        "1100110", // 1
        "1101100", // 2
        "1000010", // 3
        "1011100", // 4
        "1001110", // 5
        "1010000", // 6
        "1000100", // 7
        "1001000", // 8
        "1110100"  // 9
    };

    lcode[0] = '\0'; // Inicializa a string de resultado vazia
    rcode[0] = '\0';

    // Para cada caractere no número
    for (int i = 0; esquerda[i] != '\0'; i++) {
        int digito = esquerda[i] - '0'; // Converte o caractere para um número
        int digito2 = direita[i] - '0';
        if (digito >= 0 && digito <= 9) {
            strcat(lcode, tablcode[digito]); // Adiciona a string correspondente
            strcat(rcode, tabrcode[digito2]);
        } else {
            printf("Caractere inválido: %c\n", esquerda[i]);
            printf("Caractere inválido: %c\n", direita[i]);
            return;
        }
    }
    lcode[28] = '\0';
    rcode[28] = '\0';
}