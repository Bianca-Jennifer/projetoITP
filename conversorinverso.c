#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include "conversorinverso.h"

char *conversorInverso(char esquerda[29], char direita[29]){
    char esquerdaConvertida[5];
    char direitaConvertida[5];

    // Mapeamento do LCODE e RCODE para os dígitos
    const char *mapaE[10] = {
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

    const char *mapaD[10] = {
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

    for (int i = 0; i < 4; i++) {
        char temp[8];
        for (int j = 0; j < 7; j++) {
            temp[j] = esquerda[i * 7 + j];
        }
        temp[7] = '\0';

        // Procura o padrão no array
        int encontrado = 0;
        for (int k = 0; k < 10; k++) {
            if (strcmp(temp, mapaE[k]) == 0) {
                esquerdaConvertida[i] = '0' + k;
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("Erro: Padrão %s não encontrado\n", temp);
            esquerdaConvertida[i] = '?';
            return NULL;
        }
    }
    esquerdaConvertida[4] = '\0';

    for (int i = 0; i < 4; i++) {
        char temp[8];
        for (int j = 0; j < 7; j++) {
            temp[j] = direita[i * 7 + j];
        }
        temp[7] = '\0';

        // Procura o padrão no array
        int encontrado = 0;
        for (int k = 0; k < 10; k++) {
            if (strcmp(temp, mapaD[k]) == 0) {
                direitaConvertida[i] = '0' + k;
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("Erro: Padrão %s não encontrado\n", temp);
            direitaConvertida[i] = '?';
            return NULL;
        }
    }
    direitaConvertida[4] = '\0';

    char *codigoDeBarras = (char*) calloc(9, sizeof(char));

    for(int i = 0, contador = 0; i < 8; i++){
        if(i <= 3){
            codigoDeBarras[i] = esquerdaConvertida[i];
        }
        else{
            codigoDeBarras[i] = direitaConvertida[contador];
            contador++;
        }
    }

    return codigoDeBarras;
}