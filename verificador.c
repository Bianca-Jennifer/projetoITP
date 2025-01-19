#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include "verificador.h"

// Função para verificar o identificador
int verificar(char identificador[]) {
    int tamanho = strlen(identificador);
    int cond;

    // Verifica se o identificador contém apenas números
    for (int i = 0; identificador[i] != '\0'; i++) {
        if (!isdigit(identificador[i])) {
            printf("O identificador contém valores não numéricos.\n");
            return 1;
        }
    }

    // Verifica se o identificador tem exatamente 8 dígitos
    if (tamanho != 8) {
        printf("O identificador não contém 8 dígitos.\n");
        return 1;
    }

    // Chama a função verificarFinal para validar o código
    cond = verificarFinal(identificador); // Alteração: passa todo o identificador
    if (cond == 1) {
        printf("O dígito verificador é inválido.\n");
        return 1;
    }
    return 0;
}

int verificarFinal(char codigoDeBarras[]) {
    int soma_impar = 0, soma_par = 0, soma_total, digito_verificador;
    int tamanho = strlen(codigoDeBarras);

    // Calcula a soma das posições ímpares e pares
    for (int i = 0; i < tamanho - 1; i++) { // Exclui o último dígito (verificador)
        int numero = codigoDeBarras[i] - '0';
        if (i % 2 == 0) { // Posições ímpares (índice 0, 2, 4, 6)
            soma_impar += numero;
        } else { // Posições pares (índice 1, 3, 5)
            soma_par += numero;
        }
    }

    // Soma total seguindo o padrão EAN-8
    soma_total = soma_par + (soma_impar * 3);

    // Calcula o múltiplo de 10 mais próximo maior ou igual à soma_total
    int proximo_multiplo_10 = ((soma_total + 9) / 10) * 10;

    // Obtém o dígito verificador
    digito_verificador = proximo_multiplo_10 - soma_total;


    // Compara o dígito verificador calculado com o fornecido no código
    if (digito_verificador != (codigoDeBarras[7] - '0')) {
        //"O dígito verificador é inválido
        return 1;
    }

    return 0;
}