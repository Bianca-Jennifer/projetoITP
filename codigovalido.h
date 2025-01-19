#ifndef CODIGOVALIDO_H_INCLUDED
#define CODIGOVALIDO_H_INCLUDED

int verificar_espacamento(int **matriz, int largura_total, int altura_total);
int verificar_largura_por_pixel(int **matriz, int espacamento_lateral, int largura_total, int altura_total);
int verificar_linhas_iguais(int **matriz, int largura_total, int altura_total, int espacamento_lateral);
int verificar_marcadores(int **matriz, int largura_total, int altura_total, int espacamento_lateral, int largura_por_pixel);
char *verificar_codigo_valido (char nome[30]);

#endif