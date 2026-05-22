#include "../include/algoritmos.h"
#include <stdio.h>
#include <stdlib.h>

// Função para gerar matricula automaticamente
void gerarID (char *buffer) {
    char caracteres[] = "0123456789";
    for (int i =0; i<MAX_MAT;i++) {
        buffer[i] = caracteres[rand() % (sizeof(caracteres) - 1)];
    }

    buffer[MAX_MAT] = '\0';
}