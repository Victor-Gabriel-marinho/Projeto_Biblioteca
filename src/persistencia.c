#include <stdio.h>
#include <stdlib.h>
#include "../include/persistencia.h"
#include "../include/biblioteca.h"

Usuario *CarregarUsuarios (int *total) {
    Usuario temp;
    int cont = 0;
    Usuario *lista = NULL;

    FILE *arq = fopen("data\\usuarios.dat", "rb");

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo");
        system("pause");
        *total = 0;
        return NULL;
    }

    while (fread(&temp, sizeof(Usuario), 1,arq) == 1) {
        Usuario *novo = realloc(lista, (cont+1) * sizeof(Usuario));
        if (novo == NULL) {
            printf("Erro na alocação de memória\n");
            break;
        }
        lista = novo;
        lista[cont] = temp;
        cont++;
    }    
    fclose(arq);
    *total = cont;
    return lista;
}

void SalvarUsuarios (Usuario *usuarios, int totalusu) { 
    FILE *arq = fopen("data\\usuarios.dat", "wb");

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo\n");
        free(usuarios);
        system("pause");
        return;
    }

    fwrite(usuarios,sizeof(Usuario), totalusu, arq);

    fclose(arq);
    return;
}