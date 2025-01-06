#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include "verificador.h"
#include "conversor.h"
#include "mat.h"
#include "libmat.h"
#include "pbm.h"

int main(int argc, char *argv[]) {

    setlocale(LC_ALL, "pt_BR.UTF-8");

    int identificador = 0, espacamento_lateral = 4, quantidade_pixel = 3, altura = 50;
    char nome[30] = "codigo_de_barra.pbm";
    int cond;
    char marcadorif[4] = {'1', '0', '1', '\0'};
    char marcadorcentral[6] = {'0', '1', '0', '1', '0', '\0'};

// Verifica a validade do identificador
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

            // Verifica se o usuário digitou ".pbm" ao nome do arquivo. caso não, o ".pbm" é adicionado
            if (argc > 5) {
                memset(nome, '\0', strlen(nome));
                snprintf(nome, sizeof(nome), "%s", argv[5]);
                if (strlen(nome) >=4 && nome[strlen(nome)-1] != 'm' || nome[strlen(nome)-2] != 'b' || nome[strlen(nome)-3] != 'p' || nome[strlen(nome)-4] != '.') {
                    strcat(nome, ".pbm");
                }

            }

            // Separador de digitos iniciais e digitos finais
            char esquerda[5], direita[5];
            char lcode[29], rcode[29];
                strncpy(esquerda, argv[1], 4);
                strncpy(direita, argv[1] + 4, 4);

                esquerda[4] = '\0'; 
                direita[4] = '\0';
            
            // Converte os digitos iniciais em lcode e os finais em rcode
            conversor(esquerda, direita, lcode, rcode);

            // Concatena marcadores e digitos convertidos
            char codigodebarras[68] = "";

                strcat(codigodebarras, marcadorif);
                strcat(codigodebarras, lcode);
                strcat(codigodebarras, marcadorcentral);
                strcat(codigodebarras, rcode);
                strcat(codigodebarras, marcadorif);

            // Calcula a largura e a altura total da imagem
            int largura_total = 2 * espacamento_lateral + strlen(codigodebarras) * quantidade_pixel;
            int altura_total = altura + (2 * espacamento_lateral);

            // Cria a matriz
            int** matriz = criar_matriz(largura_total, altura_total, codigodebarras, espacamento_lateral, quantidade_pixel);

            // Salva a matriz no formato PBM
            salvar_pbm(nome, matriz, largura_total, altura_total);

            // Libera a memória da matriz
            liberar_matriz(matriz, altura_total);

            // Imprime os parâmetros do código de barras
            printf("Informações: código = %d, espaçamento lateral = %d, quantidade de pixels = %d, altura = %d, nome do arquivo = %s\n", identificador, espacamento_lateral, quantidade_pixel, altura, nome);

        }
    }


    return 0;
}
