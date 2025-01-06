#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include "libmat.h"

void liberar_matriz(int** matriz, int altura_total) {
    for (int i = 0; i < altura_total; i++) {
        free(matriz[i]);
    }
    free(matriz);
}