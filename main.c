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
            printf("O identificador cont�m valores n�o num�ricos.\n");
            return 1;
            break;
        }
    }


    if (tamanho != 8) {
        printf("O identificador n�o cont�m 8 d�gitos.\n");
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
        printf("O d�gito verificador � inv�lido.\n");
        return 1;
    }

    return 0;
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
                strncpy(esquerda, argv[1], 4);
                strncpy(direita, argv[1] + 4, 4);

                esquerda[4] = '\0'; 
                direita[4] = '\0';

            printf("Informa��es: c�digo = %d, espa�amento lateral = %d, quantidade de pixels = %d, altura = %d, nome do arquivo = %s\n", identificador, espacamento_lateral, quantidade_pixel, altura, nome);
            printf("%s\n", esquerda);
            printf("%s\n", direita);
        }
    }


    return 0;
}
