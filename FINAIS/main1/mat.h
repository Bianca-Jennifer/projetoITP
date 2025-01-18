#ifndef MAT_H_INCLUDED
#define MAT_H_INCLUDED

int** criar_matriz(int largura_total, int altura_total, char* codigodebarras, int espacamento_lateral, int quantidade_pixel);
void liberar_matriz(int** matriz, int altura_total);
void salvar_pbm(const char* nome_arquivo, int** matriz, int largura_total, int altura_total);

#endif