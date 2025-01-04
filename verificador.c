#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include "verificador.h"

int verificar(char identificador[]) {
    int tamanho = strlen(identificador);
    int soma = 0;
    int numero_que_falta;


    for (int i = 0; identificador[i] != '\0'; i++) {
        if (!isdigit(identificador[i])) {
            printf("O identificador contém valores não numéricos.\n");
            return 1;
            break;
        }
    }


    if (tamanho != 8) {
        printf("O identificador não contém 8 dígitos.\n");
        return 1;
    }

    for (int i = 0; i < 7; i++) {
        int numero = identificador[i] - '0';
        if (i % 2 == 0) {
            soma += (3 * numero);
        } else {
            soma += (1 * numero);
        }
    }


    numero_que_falta = soma % 10;

    if (numero_que_falta != identificador[7] - '0') {
        printf("O dígito verificador é inválido.\n");
        return 1;
    }

    return 0;
}