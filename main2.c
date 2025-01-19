#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include "verificador.h"
#include "codigovalido.h"
#include "conversorinverso.h"
#include "arquivovalido.h"

int main(int argc, char *argv[]){

    setlocale(LC_ALL, "pt_BR.UTF-8");

    char nome[30];
    int cond;

// Verifica se foi digitado o nome
    if (argc > 1) {
        snprintf(nome, sizeof(nome), "%s", argv[1]);
        if (strlen(nome) >=4 && nome[strlen(nome)-1] != 'm' || nome[strlen(nome)-2] != 'b' || nome[strlen(nome)-3] != 'p' || nome[strlen(nome)-4] != '.') {
            strcat(nome, ".pbm");
        }

        cond = verificar_arquivo_valido(nome);

        if (cond == 0) {
            printf("existe\n");
            char *lista_codigo = verificar_codigo_valido(nome);
            char esquerda[29];
            char direita[29];

            //Caso o código seja inválido
            if (lista_codigo == NULL) {
                printf("Sem código");
                return 1;
            }

            //separa os 28 dígitos da esquerda retirando o marcador inicial
            for(int i = 3, contador = 0; contador < 28; i++, contador++){
            esquerda[contador] = lista_codigo[i];
            }
            esquerda[28] = '\0';

            //separa os 28 dígitos da direita após o marcador central
            for(int i = 36, contador = 0; contador < 28; i++, contador++){
            direita[contador] = lista_codigo[i];
            }
            direita[28] = '\0';

           char *codigo_de_barras = conversorInverso(esquerda, direita);
           if(codigo_de_barras == NULL){
                printf("Código não encontrado");
                return 1;
           }
           char codigoFinal[9];
           
           for(int i = 0; i < 8; i++){
                codigoFinal[i] = codigo_de_barras[i];
           }
            codigoFinal[8] = '\0';

            cond = verificarFinal(codigoFinal);

            if(cond == 1){
                printf("Código não encontrado");
                return 1;
            }

            printf("%s", codigoFinal);
        
    }
}

    return 0;
}
