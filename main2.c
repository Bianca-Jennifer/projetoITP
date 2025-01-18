#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include "verificador.h"

/*As funções "verificar_espacamento","verificar_largura_por_pixel",
"verificar linhas iguais" e "verificar_marcadores" são usadas dentro da função "verificar_codigo_valido".
*/
int verificar_arquivo_valido (char nome[30]) {
    const char *nome_arquivo = nome;
    FILE *file = fopen(nome_arquivo, "r");

    if (file == NULL) {
        printf("O arquivo é inválido\n!");
        return 1;
    } else {
        //----------------------primeira linha----------

        //verifica se tem a primeira linha
        char linha[256];
        if (fgets(linha, sizeof(linha), file) == NULL) {
            printf("O arquivo é inválido\n");
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
        printf("Espaçamento uniforme: %d\n", espaco_cima);
        return espaco_baixo;
    } else {
        printf("Espaçamento desigual:\n");
        printf("Cima = %d, Baixo = %d, Esquerda = %d, Direita = %d\n",
               espaco_cima, espaco_baixo, espaco_esquerda, espaco_direita);
        return -1;       
    }
}



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

    
    printf("Largura do primeiro elemento (1) identificada: %d\n", largura_por_pixel);
    //Caso só tenha 1 na matriz
    if (!encontrado) {
        printf("Erro!\n");
        return -1;
    }


    // Verifica se a largura dos outros elementos segue o mesmo padrão

    int num;
    for (int i = inicio_codigo; i < altura_total - espacamento_lateral; i++) {
        for (int j = inicio_codigo; j < fim_coluna; j+=largura_por_pixel) {
            num = matriz[i][j];
            for (int cont = 1, cont2 = j; cont <= largura_por_pixel; cont++) {

                if (num != matriz[i][cont2]) {
                    printf("Largura por pixel inconsistente:\n");
                    return -1;
                }
                cont2++;

            }

        }
    }   

    // Retorna a largura por pixel se estiver correto
    return largura_por_pixel;
}

//Verifica se as linhas com o código são iguais    
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

//Verifica se há os marcadores
int verificar_marcadores(int **matriz, int largura_total, int altura_total, int espacamento_lateral, int largura_por_pixel) {
    int tamanho_do_codigo = (largura_total - (2 * espacamento_lateral))/largura_por_pixel;
    int inicio_codigo = espacamento_lateral;
    int fim_coluna = largura_total - espacamento_lateral;
    int marcador_inicio_fim[3] = {1,0,1};
    int marcador_meio[5] = {0,1,0,1,0}; 

    //Verifica se o tamanho do código está correto(3+28+5+28+3)
    if (tamanho_do_codigo != 67) {
        printf("Erro\n");
        return 1;
    }
    

    //Verifica se há o marcador inicial
    for (int j = inicio_codigo, cont = 0; cont < 3; j+= largura_por_pixel, cont++) {
        if (matriz[inicio_codigo][j] != marcador_inicio_fim[cont]) {
            printf("Erro\n");
            return 1;
        }
        
    }
    

    //Verifica se há o marcador do meio
    for (int j = inicio_codigo + (31 * largura_por_pixel), cont = 0; cont < 5; j+= largura_por_pixel, cont++) {
        if (matriz[inicio_codigo][j] != marcador_meio[cont]) {
            printf("Erro\n");
            return 1;
        }
        
    }
    
    //Verifica se há o marcador final
    for (int j = fim_coluna - largura_por_pixel, cont = 2; cont >= 0; j -= largura_por_pixel, cont--) {
        if (matriz[inicio_codigo][j] != marcador_inicio_fim[cont]) {
            printf("Erro\n");
            return 1;
        }
        
    }

    return 0;

}   

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
        matriz[i] = (int*) calloc(largura_total, sizeof(int));  // Cada linha é um vetor de inteiros
    }

    //Guarda os valores na matriz
    int valor;
    for (int i = 0; i < altura_total; i++) {
        for (int j = 0; j < largura_total; j++) {
            fscanf(file, "%d", &valor);
            matriz[i][j] = valor;
                   
        }
    }

    
    //Verifica se o espaçamento lateral é uniforme em todos os  lados
    int espacamento_lateral = verificar_espacamento(matriz, largura_total, altura_total);

    if (espacamento_lateral == -1) {
        fclose(file);
        return NULL;
    } 

    int largura_por_pixel = verificar_largura_por_pixel(matriz, espacamento_lateral, largura_total, altura_total);
    
    if (largura_por_pixel == -1) {
        printf("O código não foi encontrado\n");
        fclose(file);
        return NULL;
    }

    //Verifica se todas as linhas com o código de barra são iguais
    int cond = verificar_linhas_iguais(matriz, largura_total, altura_total, espacamento_lateral);
    if (cond == 1) {
        printf("Inválido");
        fclose(file);
        return NULL;
    }

    //Verifica se há marcadores
    cond = verificar_marcadores(matriz, largura_total, altura_total, espacamento_lateral, largura_por_pixel);

    if (cond == 1) {
        printf("Inválido");
        fclose(file);
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

    fclose(file);
    return lista;

}

char *conversorInverso(char esquerda[29], char direita[29]){
    char esquerdaConvertida[5];
    char direitaConvertida[5];

    // Mapeamento dos padrões binários para os dígitos
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
        char temp[8]; // Cria um buffer para armazenar os 8 bits
        for (int j = 0; j < 7; j++) {
            temp[j] = esquerda[i * 7 + j];
        }
        temp[7] = '\0'; // Adiciona o terminador nulo

        // Procura o padrão no array
        int encontrado = 0;
        for (int k = 0; k < 10; k++) {
            if (strcmp(temp, mapaE[k]) == 0) {
                esquerdaConvertida[i] = '0' + k; // Converte índice para char
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("Erro: Padrão %s não encontrado\n", temp);
            esquerdaConvertida[i] = '?'; // Marca erro
            return NULL;
        }
    }
    esquerdaConvertida[4] = '\0'; // Adiciona terminador nulo

    for (int i = 0; i < 4; i++) {
        char temp[8]; // Cria um buffer para armazenar os 8 bits
        for (int j = 0; j < 7; j++) {
            temp[j] = direita[i * 7 + j];
        }
        temp[7] = '\0'; // Adiciona o terminador nulo

        // Procura o padrão no array
        int encontrado = 0;
        for (int k = 0; k < 10; k++) {
            if (strcmp(temp, mapaD[k]) == 0) {
                direitaConvertida[i] = '0' + k; // Converte índice para char
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("Erro: Padrão %s não encontrado\n", temp);
            direitaConvertida[i] = '?'; // Marca erro
            return NULL;
        }
    }
    direitaConvertida[4] = '\0'; // Adiciona terminador nulo

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
