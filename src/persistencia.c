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

Emprestimo *CarregarEmprestimos (int *total) {
    Emprestimo temp;
    int cont = 0;
    Emprestimo *lista = NULL;

    FILE *arquivo = fopen("data\\emprestimos.dat", "rb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        system("pause");
        *total = 0;
        return NULL;
    }

    while (fread(&temp, sizeof(Usuario), 1,arquivo) == 1) {
        Emprestimo *novo1 = realloc(lista, (cont+1) * sizeof(Emprestimo));
        if (novo1 == NULL) {
            printf("Erro na alocação de memória\n");
            break;
        }
        lista = novo1;
        lista[cont] = temp;
        cont++;
    }    
    fclose(arquivo);
    *total = cont;
    return lista;
}

void SalvarEmprestimos (Emprestimo *emprestimos, int totalemp) { 
    FILE *arquivo = fopen("data\\usuarios.dat", "wb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        free(emprestimos);
        system("pause");
        return;
    }

    fwrite(emprestimos,sizeof(Emprestimo), totalemp, arquivo);

    fclose(arquivo);
    return;
}

#include <stdio.h>
#include <stdlib.h>
#include "../include/persistencia.h"
#include "../include/biblioteca.h"

Livro *CarregarLivros (int *total) {
    Livro temp;
    int cont = 0;
    Livro *lista = NULL;

    FILE *arq = fopen("data\\livros.dat", "rb");

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo");
        system("pause");
        *total = 0;
        return NULL;
    }

    while (fread(&temp, sizeof(Livro), 1,arq) == 1) {
        Livro *novo = realloc(lista, (cont+1) * sizeof(Livro));
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

void SalvarLivros (Livro *livros, int totalLivros) { 
    FILE *arq = fopen("data\\livros.dat", "wb");

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo\n");
        free(livros);
        system("pause");
        return;
    }

    fwrite(livros,sizeof(Livro), totalLivros, arq);

    fclose(arq);
    return;
}