#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>


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
}


int main(int argc, char *argv[]) {

    int identificador = 0, espacamento_lateral = 0, quantidade_pixel = 0, altura = 0;
    char nome[20] = "";
    int cond;

    setlocale(0, "Portuguese");


    if (argc > 1) {
        cond = verificar(argv[1]);

        if (cond == 0) {

            identificador = atoi(argv[1]);

            if (argc > 2) {
                espacamento_lateral = atoi(argv[2]);

            }

            if (argc > 3) {
                quantidade_pixel = atoi(argv[3]);

            }

            if (argc > 4) {
                altura= atoi(argv[4]);

            }

            if (argc > 5) {
                snprintf(nome, sizeof(nome), "%s", argv[5]);

            }
            char esquerda[5], direita[5];
            char lcode[29], rcode[29];
                strncpy(esquerda, argv[1], 4);
                strncpy(direita, argv[1] + 4, 4);

                esquerda[4] = '\0'; 
                direita[4] = '\0';
            
            conversor(esquerda, direita, lcode, rcode);

            printf("Informações: código = %d, espaçamento lateral = %d, quantidade de pixels = %d, altura = %d, nome do arquivo = %s\n", identificador, espacamento_lateral, quantidade_pixel, altura, nome);
            printf("%s\n", esquerda);
            printf("%s\n", direita);
            printf("%s\n", lcode);
            printf("%s\n", rcode);
        }
    }


    return 0;
}
