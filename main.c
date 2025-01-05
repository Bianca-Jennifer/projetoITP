#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include "verificador.h"
#include "conversor.h"

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

// Função para salvar a matriz no formato PBM
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

// Função para liberar a memória alocada para a matriz
void liberar_matriz(int** matriz, int altura_total) {
    for (int i = 0; i < altura_total; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

int main(int argc, char *argv[]) {

    int identificador = 0, espacamento_lateral = 4, quantidade_pixel = 3, altura = 50;
    char nome[30] = "codigo_de_barra.pbm";
    int cond;
    char marcadorif[4] = {'1', '0', '1', '\0'};
    char marcadorcentral[6] = {'0', '1', '0', '1', '0', '\0'};

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
                memset(nome, '\0', strlen(nome));
                snprintf(nome, sizeof(nome), "%s", argv[5]);
                if (strlen(nome) >=4 && nome[strlen(nome)-1] != 'm' || nome[strlen(nome)-2] != 'b' || nome[strlen(nome)-3] != 'p' || nome[strlen(nome)-4] != '.') {
                    strcat(nome, ".pbm");
                }

            }

            //separador de digitos iniciais e digitos finais
            char esquerda[5], direita[5];
            char lcode[29], rcode[29];
                strncpy(esquerda, argv[1], 4);
                strncpy(direita, argv[1] + 4, 4);

                esquerda[4] = '\0'; 
                direita[4] = '\0';
            
            //converte os digitos iniciais em lcode e os finais em rcode
            conversor(esquerda, direita, lcode, rcode);

            //junta marcadores digitos convertidos
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

            printf("Informações: código = %d, espaçamento lateral = %d, quantidade de pixels = %d, altura = %d, nome do arquivo = %s\n", identificador, espacamento_lateral, quantidade_pixel, altura, nome);
            printf("%s\n", esquerda);
            printf("%s\n", direita);
            printf("%s\n", lcode);
            printf("%s\n", rcode);
            printf("%s\n", codigodebarras);
            printf("hello world");


        }
    }


    return 0;
}
