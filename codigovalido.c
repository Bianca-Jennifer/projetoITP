#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include "codigovalido.h"

// Função para verificar o espaçamento lateral
int verificar_espacamento(int **matriz, int largura_total, int altura_total) {
    int espaco_cima = 0, espaco_baixo = 0, espaco_esquerda = 0, espaco_direita = 0;
    //----------Verifica se o espaçamento lateral é uniforme, guardando o valor de cada lado e comparando
    // Guarda quantas linhas estão zeradas em cima
    for (int i = 0; i < altura_total; i++) {
        int linha_vazia = 1; 
        for (int j = 0; j < largura_total; j++) {
            if (matriz[i][j] == 1) {
                linha_vazia = 0;
                break;
            }
        }
        if (linha_vazia) {
            espaco_cima++;
        } else {
            break;
        }
    }

    // Guarda quantas linhas estão zeradas na parte de baixo 
    for (int i = altura_total - 1; i >= 0; i--) {
        int linha_vazia = 1;
        for (int j = 0; j < largura_total; j++) {
            if (matriz[i][j] == 1) {
                linha_vazia = 0;
                break;
            }
        }
        if (linha_vazia) {
            espaco_baixo++;
        } else {
            break;
        }
    }

    // Guarda quantas colunas estão zeradas na parte esquerda
    for (int j = 0; j < largura_total; j++) {
        int coluna_vazia = 1;
        for (int i = 0; i < altura_total; i++) {
            if (matriz[i][j] == 1) {
                coluna_vazia = 0;
                break;
            }
        }
        if (coluna_vazia) {
            espaco_esquerda++;
        } else {
            break;
        }
    }

    // Guarda quantas colunas estão zeradas na parte direita 
    for (int j = largura_total - 1; j >= 0; j--) {
        int coluna_vazia = 1;
        for (int i = 0; i < altura_total; i++) {
            if (matriz[i][j] == 1) {
                coluna_vazia = 0;
                break;
            }
        }
        if (coluna_vazia) {
            espaco_direita++;
        } else {
            break;
        }
    }

    // Compara os valores
    if (espaco_cima == espaco_baixo && espaco_cima == espaco_esquerda && espaco_cima == espaco_direita) {
        //Espaçamento uniforme
        return espaco_baixo;
    } else {
        //Espaçamento desigual
        return -1;       
    }
}

// Função para verificar a largura por pixel
int verificar_largura_por_pixel(int **matriz, int espacamento_lateral, int largura_total, int altura_total) {
    int largura_por_pixel = 0;
    int encontrado = 0;

    // Pula o espaçamento lateral
    int inicio_codigo = espacamento_lateral; 
    int fim_coluna = largura_total - espacamento_lateral; 
    int fim_linha = altura_total - espacamento_lateral;
    
    //Precisa começar com 1 por ser marcador
    if (matriz[inicio_codigo][inicio_codigo] != 1) {
        return -1;
    }
    // Verifica quantas vezes o primeiro elemento (1) se repete
    for (int i = inicio_codigo; i < fim_linha; i++) {
        for (int j = inicio_codigo; j < fim_coluna;) {
            if (matriz[i][j] == 1) {  // O primeiro valor é sempre 1
                int largura_atual = 0;

                
                while (j < fim_coluna && matriz[i][j] == 1) {
                    largura_atual++;
                    j++;  
                }

                
                if (!encontrado) {
                    largura_por_pixel = largura_atual;
                    encontrado = 1;
                    break;
                }
            } else {
                j++; 
            }
        }
    }

    
    //Largura do primeiro elemento identificada em largura_por_pixel//
    //Caso só tenha 1 na matriz
    if (!encontrado) {
        //Erro
        return -1;
    }


    // Verifica se a largura dos outros elementos segue o mesmo padrão

    int num;
    for (int i = inicio_codigo; i < altura_total - espacamento_lateral; i++) {
        for (int j = inicio_codigo; j < fim_coluna; j+=largura_por_pixel) {
            num = matriz[i][j];
            for (int cont = 1, cont2 = j; cont <= largura_por_pixel; cont++) {

                if (num != matriz[i][cont2]) {
                    //Largura por pixel inconsistente
                    return -1;
                }
                cont2++;

            }

        }
    }   

    // Retorna a largura por pixel se estiver correto
    return largura_por_pixel;
}

// Função para verificar se as linhas da matriz são iguais
int verificar_linhas_iguais(int **matriz, int largura_total, int altura_total, int espacamento_lateral) {
    int inicio_codigo = espacamento_lateral;
    int fim_linha = altura_total - espacamento_lateral;
    int fim_coluna = largura_total - espacamento_lateral;

    for (int i = inicio_codigo; i < fim_linha; i++) {
        for (int j = inicio_codigo; j < fim_coluna; j++) {
            if (matriz[i][j] != matriz[inicio_codigo][j]) {
                return 1;
            }

        }
    }  
} 

// Função para verificar se há os marcadores
int verificar_marcadores(int **matriz, int largura_total, int altura_total, int espacamento_lateral, int largura_por_pixel) {
    int tamanho_do_codigo = (largura_total - (2 * espacamento_lateral))/largura_por_pixel;
    int inicio_codigo = espacamento_lateral;
    int fim_coluna = largura_total - espacamento_lateral;
    int marcador_inicio_fim[3] = {1,0,1};
    int marcador_meio[5] = {0,1,0,1,0}; 

    //Verifica se o tamanho do código está correto(3+28+5+28+3)
    if (tamanho_do_codigo != 67) {
        //Erro
        return 1;
    }
    

    //Verifica se há o marcador inicial
    for (int j = inicio_codigo, cont = 0; cont < 3; j+= largura_por_pixel, cont++) {
        if (matriz[inicio_codigo][j] != marcador_inicio_fim[cont]) {
            //Erro
            return 1;
        }
        
    }
    

    //Verifica se há o marcador do meio
    for (int j = inicio_codigo + (31 * largura_por_pixel), cont = 0; cont < 5; j+= largura_por_pixel, cont++) {
        if (matriz[inicio_codigo][j] != marcador_meio[cont]) {
            //Erro
            return 1;
        }
        
    }
    
    //Verifica se há o marcador final
    for (int j = fim_coluna - largura_por_pixel, cont = 2; cont >= 0; j -= largura_por_pixel, cont--) {
        if (matriz[inicio_codigo][j] != marcador_inicio_fim[cont]) {
            //Erro
            return 1;
        }
        
    }

    return 0;

}

// Função para verificar a validade do código
char* verificar_codigo_valido (char nome[30]) {
    const char *nome_arquivo = nome;
    int largura_total, altura_total;
    char linha_arq[256];
    FILE *file = fopen(nome_arquivo, "r");

    
    fgets(linha_arq, sizeof(linha_arq), file);
    fgets(linha_arq, sizeof(linha_arq), file);

    

    //Guarda o valor da largura e altura
    sscanf(linha_arq, "%d %d", &largura_total, &altura_total);
    

    // Aloca memória para a matriz
    int** matriz = (int**) calloc(altura_total, sizeof(int*));

    // Aloca memória para cada linha da matriz e inicializa com 0
    for (int i = 0; i < altura_total; i++) {
        matriz[i] = (int*) calloc(largura_total, sizeof(int));
    }

    //Guarda os valores na matriz
    int valor;
    for (int i = 0; i < altura_total; i++) {
        for (int j = 0; j < largura_total; j++) {
            fscanf(file, "%d", &valor);
            matriz[i][j] = valor;
                   
        }
    }

    //Fecha arquivo 
    fclose(file);
    
    //Verifica se o espaçamento lateral é uniforme em todos os  lados
    int espacamento_lateral = verificar_espacamento(matriz, largura_total, altura_total);

    if (espacamento_lateral == -1) {
        fclose(file);
        return NULL;
    } 

    int largura_por_pixel = verificar_largura_por_pixel(matriz, espacamento_lateral, largura_total, altura_total);
    
    if (largura_por_pixel == -1) {
       //Inválido
        return NULL;
    }

    //Verifica se todas as linhas com o código de barra são iguais
    int cond = verificar_linhas_iguais(matriz, largura_total, altura_total, espacamento_lateral);
    if (cond == 1) {
        //Inválido
        return NULL;
    }

    //Verifica se há marcadores
    cond = verificar_marcadores(matriz, largura_total, altura_total, espacamento_lateral, largura_por_pixel);

    if (cond == 1) {
        //Inválido
        return NULL;
    }

    //Prepara lista com o código 
    int inicio_codigo = espacamento_lateral;
    int fim_coluna = largura_total - espacamento_lateral;
    char* lista = (char*) calloc(68, sizeof(char));

    for (int j = inicio_codigo, cont = 0; j < fim_coluna; j+=largura_por_pixel, cont++) {
        lista[cont] = matriz[inicio_codigo][j] + '0';
    }

    

    //Libera a matriz
    for (int i = 0; i < altura_total; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return lista;

}