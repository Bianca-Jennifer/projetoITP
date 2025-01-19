#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include "arquivovalido.h"

/*As funções "verificar_espacamento","verificar_largura_por_pixel",
"verificar linhas iguais" e "verificar_marcadores" são usadas dentro da função "verificar_codigo_valido".
*/
int verificar_arquivo_valido (char nome[30]) {
    const char *nome_arquivo = nome;
    FILE *file = fopen(nome_arquivo, "r");

    if (file == NULL) {
        printf("O arquivo é inválido!\n");
        return 1;
    } else {
        //----------------------primeira linha----------

        //verifica se tem a primeira linha
        char linha[256];
        if (fgets(linha, sizeof(linha), file) == NULL) {
            printf("O arquivo é inválido!\n");
            fclose(file);
            return 1;
        }
        
        //verifica se os primeiro elementos são P e 1 e se tem mais algum elementos depois deles
        // 
        int cont = 0;

        if (linha[0] == 'P' && linha[1] == '1') {
                cont = 2;
                while (linha[cont] != '\0') {
                    if (linha[cont] != ' ' && linha[cont] != '\n') {
                        printf("O arquivo é inválido!");
                        fclose(file);
                        return 1;
                    }
                    cont++;
                }

        } else {
            printf("O arquivo é inválido!\n");
            fclose(file);
            return 1;
        }

        //-------------------------segunda linha---------------
        char linha2[256];
        int valor1, valor2;
        char apos_valor[256];

       
        //verifica se tem a segunda linha
        if (fgets(linha2, sizeof(linha2), file) == NULL) {
            printf("O arquivo é inválido!\n");
            fclose(file);
            return 1;
        }

        //verifica se os primeiro elementos são os valores e se tem mais algum elementos depois deles
        size_t len = strlen(linha2);
        if (len > 0 && linha2[len - 1] == '\n') {
            linha2[len - 1] = '\0';
        }

        if (!isdigit(linha2[0])) {
            printf("O arquivo é inválido!\n");
            fclose(file);
            return 1;
        }

        if (sscanf(linha2, "%d %d %s", &valor1, &valor2, apos_valor) != 2) {
            printf("O arquivo é inválido!\n");
            fclose(file);
            return 1;
        } 
        

        //----------------------desenho-------------
        //verifica se há 1 ou 0,se a quantidade de elementos é igual à multiplicação dos dois valores
        //verifica se depois dos elementos do desenho é o fim 
        int tamanho_total = valor1 * valor2;
        int pixels_somados = 0;
        int elemento;
        

        while (fscanf(file, "%d", &elemento) == 1) {
            if (elemento != 0 && elemento != 1) {
                printf("O arquivo é inválido!\n");
                fclose(file);
                return 1;
            }
            pixels_somados++;
        }

        if (tamanho_total != pixels_somados) {
            printf("O arquivo é inválido!\n");
            fclose(file);
            return 1;
        }

        int final;

        final = fgetc(file);

        if (final != EOF) {
            printf("O arquivo é inválido!\n");
            fclose(file);
            return 1;
        }
    

    } 

    fclose(file);
    return 0;
}         